/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick development of a prototype application.
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

#include "ProtocolOperator.h"
#include "AnswerPackets.h"
#include "EventPackets.h"
#include "QueryPackets.h"

namespace Ramio {

ProtocolOperator::ProtocolOperator(QObject* parent)
	: QObject(parent)
{
}

void ProtocolOperator::onPacketReceived(const QByteArray& data, const ConnectionInfo& from)
{
	Proto::XmlDocument docPacket(data);
	QString TypeStr = docPacket.deMessage.attribute(Proto::TypeStr);
	QString CommandStr = docPacket.deMessage.attribute(Proto::CommandStr);

	if (TypeStr == Proto::packetTypename(Proto::PacketType::Query))
	{
		QScopedPointer<Proto::QueryPacket> packet;
		Proto::Queries query = Proto::queryByName(CommandStr);
		if (query == Proto::Queries::Login)
			packet.reset(new Proto::QPLogin);
		else if (query == Proto::Queries::GetDataSet)
			packet.reset(new Proto::QPGetDataSet);
		else if (query == Proto::Queries::CreateDataObject)
			packet.reset(new Proto::QPCreateDataObject);
		else if (query == Proto::Queries::SaveDataObject)
			packet.reset(new Proto::QPSaveDataObject);
		else if (query == Proto::Queries::DeleteDataObject)
			packet.reset(new Proto::QPDeleteDataObject);
		else
			Q_ASSERT(0);

		if (packet)
		{
			packet->deserialize(docPacket);
			emit queryReceived(query, *packet, from);
		}
	}
	else if (TypeStr == Proto::packetTypename(Proto::PacketType::Answer))
	{
		QScopedPointer<Proto::AnswerPacket> packet;
		Proto::Queries query = Proto::queryByName(CommandStr);

		if (query == Proto::Queries::Login)
			packet.reset(new Proto::APLogin);
		else if (query == Proto::Queries::GetDataSet)
			packet.reset(new Proto::APGetDataSet);
		else if (query == Proto::Queries::CreateDataObject)
			packet.reset(new Proto::APCreateDataObject);
		else if (query == Proto::Queries::SaveDataObject)
			packet.reset(new Proto::APSaveDataObject);
		else if (query == Proto::Queries::DeleteDataObject)
			packet.reset(new Proto::APDeleteDataObject);
		else
			Q_ASSERT(0);

		if (packet)
		{
			packet->deserialize(docPacket);
			emit answerReceived(query, *packet, docPacket, from);
		}
	}
	else if (TypeStr == Proto::packetTypename(Proto::PacketType::Event))
	{
		QScopedPointer<Proto::EventPacket> packet;
		Proto::Events event = Proto::eventByName(CommandStr);
		if (event == Proto::Events::DataObjectCreated)
			packet.reset(new Proto::EPDataObjectCreated);
		else if (event == Proto::Events::DataObjectChanged)
			packet.reset(new Proto::EPDataObjectChanged);
		else if (event == Proto::Events::DataObjectDeleted)
			packet.reset(new Proto::EPDataObjectDeleted);
		else
			Q_ASSERT(0);

		if (packet)
		{
			packet->deserialize(docPacket);
			emit eventReceived(event, *packet, docPacket, from);
		}
	}
}

} // Ramio::
