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

#include "ItemSetClient.h"
#include "MainWidget.h"
#include "TasksSimpleWidget.h"
#include "LoginWidget.h"
#include <Protocol/AnswerPackets.h>
#include <Protocol/EventPackets.h>
#include <Protocol/QueryPackets.h>
#include <Log/Log.h>

ItemSetClient::ItemSetClient()
	: client_(QHostAddress::LocalHost, 40404),
	  arhiveTasks_(tasks_, [](const Task& task)->bool{return task.isArhived();})
{
	ULOG(tr("Начало работы программы"));
	QObject::connect(&client_, &Ramio::TcpClient::bytesReceived, &packetBuilder_, &Ramio::PacketBuilder::onBytesReceived);
	QObject::connect(&packetBuilder_, &Ramio::PacketBuilder::packetReceived, &protocolOperator_, &Ramio::ProtocolOperator::onPacketReceived);
	QObject::connect(&protocolOperator_, &Ramio::ProtocolOperator::answerReceived, this, &ItemSetClient::onAnswerReceived);
	QObject::connect(&protocolOperator_, &Ramio::ProtocolOperator::eventReceived, this, &ItemSetClient::onEventReceived);
	QObject::connect(&client_, &Ramio::TcpClient::disconnected, this, &ItemSetClient::showLoginForm);

	client_.connectToHost();
}

ItemSetClient::~ItemSetClient()
{
	loginWidget_.reset();
	mainWidget_.reset();
	ULOG(tr("Завершение работы программы"));
}

void ItemSetClient::showLoginForm()
{
	if (mainWidget_)
		mainWidget_.reset();

	if (loginWidget_ && loginWidget_->isVisible())
		return;

	loginWidget_.reset(new LoginWidget(tr("Авторизация"), Q_NULLPTR));
	connect(&*loginWidget_, &LoginWidget::accepted, this, &ItemSetClient::onLoginAccepted);
	loginWidget_->show();
}

void ItemSetClient::autoLogin()
{
	if (loginWidget_)
	{
		loginWidget_->autoLogin();
		ULOG(tr("Автоматическое подключение"));
	}
}

void ItemSetClient::requestCreate(QString text, QColor color)
{
	TaskRecord task;
	task.text = std::move(text);
	task.color = color.name();
	task.time = QDateTime::currentDateTime();
	Ramio::Proto::QPCreateDataObject createDataObject(tasks_.meta().setName, tasks_.meta().itemName, pid_++);
	createDataObject.createFromData(tasks_.meta(), task);

	Ramio::ResDesc rd = sendQuery(createDataObject);
	if (rd.noCriticalError() && mainWidget_ && mainWidget_->tasksSimpleWidget())
		mainWidget_->tasksSimpleWidget()->onErrorCreate(rd.desc);

}

void ItemSetClient::requestChangeCompleteStatus(const Task& task)
{
	Task copytask(task.data());
	copytask.changeFinished();
	Ramio::Proto::QPSaveDataObject saveDataObject(tasks_.meta().setName, tasks_.meta().itemName, pid_++);
	saveDataObject.createFromData(tasks_.meta(), copytask.data());
	sendQuery(saveDataObject);
}

void ItemSetClient::requestChangeArhiveStatus(const Task& task)
{
	Task copytask(task.data());
	copytask.setArhived();
	Ramio::Proto::QPSaveDataObject saveDataObject(tasks_.meta().setName, tasks_.meta().itemName, pid_++);
	saveDataObject.createFromData(tasks_.meta(), copytask.data());
	sendQuery(saveDataObject);
}

void ItemSetClient::requestDelete(const Task& task)
{
	Ramio::Proto::QPDeleteDataObject deleteDataObject(tasks_.meta().setName, tasks_.meta().itemName,
									 QString::number(task.id()), QString(), pid_++);
	sendQuery(deleteDataObject);
}

void ItemSetClient::onLoginAccepted(const QString &login, const QString& password)
{
	Ramio::Proto::QPLogin loginPacket(pid_++);
	loginPacket.username = login;
	loginPacket.password = password;
	sendQuery(loginPacket);
}

void ItemSetClient::showMainWindow()
{
	mainWidget_.reset(new MainWidget(*this));
	mainWidget_->show();
}

qint64 ItemSetClient::sendQuery(Ramio::Proto::QueryPacket& packet)
{
	Ramio::Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	QByteArray data = docPacket.doc.toByteArray();
	return packetBuilder_.write(data, client_);
}

void ItemSetClient::onAnswerReceived(Ramio::Proto::Queries query, const Ramio::Proto::AnswerPacket& packet,
									 const Ramio::Proto::XmlDocument& doc, const Ramio::ConnectionInfo& from)
{
	if (packet.res == 0)
	{
		if (query == Ramio::Proto::Queries::Login)
		{
			showMainWindow();
			loginWidget_.reset();
			Ramio::Proto::QPGetDataSet getDataSetPacket(pid_++, tasks_.meta().setName);
			sendQuery(getDataSetPacket);

			ULOG(tr("Успешное подключение"));
		}
		else if (query == Ramio::Proto::Queries::GetDataSet)
		{
			auto& answerPacket  = reinterpret_cast<const Ramio::Proto::APGetDataSet&>(packet);
			tasks_.clear();
			tasks_.deserialize(doc.deData.firstChildElement(answerPacket.dataSetName));
			ULOG(tr("Успешное получение списка задач"));
		}
		else if (query == Ramio::Proto::Queries::CreateDataObject)
			ULOG(tr("Успешное создание задачи"));
		else if (query == Ramio::Proto::Queries::SaveDataObject)
			ULOG(tr("Успешное изменение задачи"));
		else if (query == Ramio::Proto::Queries::DeleteDataObject)
			ULOG(tr("Успешное удаление задачи"));

	}
	else
	{
		if (query == Ramio::Proto::Queries::CreateDataObject  && mainWidget_ && mainWidget_->tasksSimpleWidget())
			mainWidget_->tasksSimpleWidget()->onErrorCreate(packet.desc);

		ULOG(tr("Сбой команды [%1]: %2").arg(Ramio::Proto::queryName(query)).arg(packet.desc));
	}
}

void ItemSetClient::onEventReceived(Ramio::Proto::Events event, const Ramio::Proto::EventPacket& packet, const Ramio::Proto::XmlDocument &doc, const Ramio::ConnectionInfo &from)
{
	if (event == Ramio::Proto::Events::DataObjectCreated)
	{
		auto& eventPacket = reinterpret_cast<const Ramio::Proto::EPDataObjectCreated&>(packet);
		TaskRecord task;
		eventPacket.updateData(tasks_.meta(), task);
		tasks_.addItem(task);
		ULOG(tr("Событие об создании задачи"));
	}
	else if (event == Ramio::Proto::Events::DataObjectChanged)
	{
		auto& eventPacket = reinterpret_cast<const Ramio::Proto::EPDataObjectChanged&>(packet);
		TaskRecord taskData;
		eventPacket.updateData(tasks_.meta(), taskData);
		if (Task* task = tasks_.itemById(taskData.id))
			task->updateData(taskData);
		ULOG(tr("Событие об изменение задачи"));
	}
	else if (event == Ramio::Proto::Events::DataObjectDeleted)
	{
		auto& eventPacket = reinterpret_cast<const Ramio::Proto::EPDataObjectDeleted&>(packet);
		if (Task* task = tasks_.itemById(eventPacket.itemId.toInt()))
			tasks_.removeItem(*task);
		ULOG(tr("Событие об удалении задачи"));
	}
}
