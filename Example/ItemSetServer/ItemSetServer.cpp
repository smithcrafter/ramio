/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Examples, a Qt-based casual C++ classes for quick application writing.
 *
 * Ramio is free software; you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation;
 * either version 3 of the License, or (at your option) any later version.
 *
 * Ramio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Ramio; see the file LICENSE. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ItemSetServer.h"
#include <Protocol/AnswerPackets.h>
#include <Protocol/QueryPackets.h>
#include <Protocol/EventPackets.h>

ItemSetServer::ItemSetServer()
	: database_(Ramio::SupportedDatabaseType::SQLite, QStringLiteral("ServerDB")),
	  server_(QHostAddress::LocalHost, 40404)
{
	tasks_.setRelationSet("userId", &users_);
	QObject::connect(&server_, &Ramio::TcpServer::bytesReceived, &packetBuilder_, &Ramio::PacketBuilder::onBytesReceived);
	QObject::connect(&packetBuilder_, &Ramio::PacketBuilder::packetReceived, &protocolOperator_, &Ramio::ProtocolOperator::onPacketReceived);
	QObject::connect(&server_, &Ramio::TcpServer::clientDisconnected, this, &ItemSetServer::onClientDisconnected);
	QObject::connect(&protocolOperator_, &Ramio::ProtocolOperator::queryReceived, this, &ItemSetServer::onQueryReceived);
}

bool ItemSetServer::openDatabase()
{
	Ramio::DatabaseConfig dbconfig;
	dbconfig.dbname = "ItemSetServer.db";

	if (database_.open(dbconfig) == false)
		return false;

	database_.initTable(users_.meta());
	database_.initTable(tasks_.meta());

	database_.selectMetaItemDataSet(users_);
	if (users_.isEmpty())
	{
		UserRecord userRecord;
		userRecord.login = "user1";
		userRecord.password = "1";
		if (database_.insertMetaItemData(userRecord, users_.meta()).noCriticalError())
			users_.addItem(userRecord);
		else
			return false;
	}
	return true;
}

bool ItemSetServer::startListening()
{
	return server_.listen().noCriticalError();
}

void ItemSetServer::addUser(User &user)
{
	database_.insertMetaItemData(user.data(), users_.meta());
	users_.insertItem(user);
}

void ItemSetServer::onQueryReceived(Ramio::Proto::Queries query, const Ramio::Proto::QueryPacket& packet, const Ramio::ConnectionInfo& client)
{
	if (!currentUser_.item())
	{
		if (query == Ramio::Proto::Queries::Login)
		{
			auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPLogin&>(packet);
			Ramio::Proto::APLogin answer(packet.pid);

			for (auto* user: users_.items())
				if (queryPacket.username == user->data().login && queryPacket.password == user->data().password)
				{
					currentUser_.setItem(user);
					currentConnection_ = client;
					answer.res = 0;
					doOnLogin();
				}
			if (!currentUser_.item())
			{
				answer.res = 1;
				answer.desc = "Сбой авторизации";
			}
			sendAnswer(query, answer, client);
			return;
		}
		return;
	}
	else if (client.connectionId != currentConnection_.connectionId)
		return;

	if (query == Ramio::Proto::Queries::GetDataSet)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPGetDataSet&>(packet);
		Ramio::Proto::APGetDataSet answer(packet.pid);
		if (queryPacket.dataSetName == tasks_.meta().setName)
		{
			answer.dataSetName = tasks_.meta().setName;
			answer.set = &tasks_;
		}
		else
			answer.setResDesc(1, tr("Данные не найдены"));
		sendAnswer(query, answer, client);
	}
	else if (query == Ramio::Proto::Queries::CreateDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPCreateDataObject&>(packet);
		TaskRecord taskData;
		queryPacket.updateData(tasks_.meta(), taskData);
		taskData.userId = currentUser_.item()->id();

		Ramio::Proto::APCreateDataObject answer(packet.pid);
		answer.dataSetName = queryPacket.dataSetName;
		answer.itemName = queryPacket.itemName;

		Ramio::ResDesc rd = database_.insertMetaItemData(taskData, tasks_.meta());
		if (rd.noCriticalError())
		{
			tasks_.addItem(taskData);
			answer.itemId = QString::number(taskData.id);

			Ramio::Proto::EPDataObjectCreated eventPacket(tasks_.meta().setName, tasks_.meta().itemName, epid_++);
			eventPacket.createFromData(tasks_.meta(), taskData);
			sendEvent(Ramio::Proto::Events::DataObjectCreated, eventPacket, client);
		}
		else
			answer.setResDesc(rd.res, rd.desc);
		sendAnswer(query, answer, client);
	}
	else if (query == Ramio::Proto::Queries::SaveDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPSaveDataObject&>(packet);
		TaskRecord taskData;
		queryPacket.updateData(tasks_.meta(), taskData);

		Ramio::Proto::APSaveDataObject answer(packet.pid);
		answer.dataSetName = queryPacket.dataSetName;
		answer.itemName = queryPacket.itemName;
		answer.itemId = QString::number(taskData.id);

		if (Task* task = tasks_.itemById(taskData.id))
		{
			Ramio::ResDesc rd = database_.updateMetaItemData(taskData, tasks_.meta());
			if (rd.noCriticalError())
			{
				task->updateData(taskData);

				Ramio::Proto::EPDataObjectChanged eventPacket(tasks_.meta().setName, tasks_.meta().itemName, epid_++);
				eventPacket.createFromData(tasks_.meta(), taskData);
				sendEvent(Ramio::Proto::Events::DataObjectChanged, eventPacket, client);
			}
			else
				answer.setResDesc(rd.res, rd.desc);
		}
		else
			answer.setResDesc(1, tr("Данные не найдены"));
		sendAnswer(query, answer, client);
	}
	else if (query == Ramio::Proto::Queries::DeleteDataObject)
	{
		auto& queryPacket = reinterpret_cast<const Ramio::Proto::QPDeleteDataObject&>(packet);
		Ramio::Proto::APDeleteDataObject answer(packet.pid);
		answer.dataSetName = queryPacket.dataSetName;
		answer.itemName = queryPacket.itemName;
		answer.itemId = queryPacket.itemId;
		answer.itemUuid = queryPacket.itemUuid;

		if (Task* task = tasks_.itemById(queryPacket.itemId.toULongLong()))
		{
			Ramio::Proto::EPDataObjectDeleted eventPacket(tasks_.meta().setName, tasks_.meta().itemName,
														  QString::number(task->id()), QString(), epid_++);
			Ramio::ResDesc rd = database_.deleteMetaItemData(task->data(), tasks_.meta());
			if (rd.noCriticalError())
			{
				sendEvent(Ramio::Proto::Events::DataObjectDeleted, eventPacket, client);
				tasks_.removeItem(*task);
			}
			else
				answer.setResDesc(rd.res, rd.desc);
		}
		else
			answer.setResDesc(1, tr("Данные не найдены"));
		sendAnswer(query, answer, client);
	}
}

void ItemSetServer::onClientDisconnected(const Ramio::ConnectionInfo& client)
{
	if (!currentUser_.isEmpty() && client.connectionId == currentConnection_.connectionId)
		doOnLogout();
}

void ItemSetServer::sendAnswer(Ramio::Proto::Queries, const Ramio::Proto::AnswerPacket& packet, const Ramio::ConnectionInfo& to)
{
	Ramio::Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void ItemSetServer::sendEvent(Ramio::Proto::Events, const Ramio::Proto::EventPacket& packet, const Ramio::ConnectionInfo& to)
{
	Ramio::Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void ItemSetServer::doOnLogin()
{
	database_.selectMetaItemDataSet(tasks_, QStringLiteral("userId=%1").arg(currentUser_.item()->id()));
}

void ItemSetServer::doOnLogout()
{
	currentUser_.clear();
	tasks_.clear();
}
