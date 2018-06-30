/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

ProtocolOperator::ProtocolOperator() = default;

void ProtocolOperator::onPacketReceived(const QByteArray& data, const ConnectionInfo& from)
{
	Ramio::Proto::XmlDocument docPacket(data);
	QString TypeStr = docPacket.deMessage.attribute(Ramio::Proto::TypeStr);
	QString CommandStr = docPacket.deMessage.attribute(Ramio::Proto::CommandStr);

	if (TypeStr == Ramio::Proto::packetTypename(Ramio::Proto::PacketType::Query))
	{
		QScopedPointer<Ramio::Proto::QueryPacket> packet;
		Ramio::Proto::Queries query = Ramio::Proto::queryByName(CommandStr);
		if (query == Ramio::Proto::Queries::Login)
			packet.reset(new Ramio::Proto::QPLogin);
		else if (query == Ramio::Proto::Queries::GetDataSet)
			packet.reset(new Ramio::Proto::QPGetDataSet);
		else if (query == Ramio::Proto::Queries::CreateDataObject)
			packet.reset(new Ramio::Proto::QPCreateDataObject);
		else if (query == Ramio::Proto::Queries::SaveDataObject)
			packet.reset(new Ramio::Proto::QPSaveDataObject);
		else if (query == Ramio::Proto::Queries::DeleteDataObject)
			packet.reset(new Ramio::Proto::QPDeleteDataObject);
		else
			Q_ASSERT(0);

		if (packet)
		{
			packet->deserialize(docPacket);
			emit queryReceived(query, *packet, from);
		}
	}
	else if (TypeStr == Ramio::Proto::packetTypename(Ramio::Proto::PacketType::Answer))
	{
		QScopedPointer<Ramio::Proto::AnswerPacket> packet;
		Ramio::Proto::Queries query = Ramio::Proto::queryByName(CommandStr);

		if (query == Ramio::Proto::Queries::Login)
			packet.reset(new Ramio::Proto::APLogin);
		else if (query == Ramio::Proto::Queries::GetDataSet)
			packet.reset(new Ramio::Proto::APGetDataSet);
		else if (query == Ramio::Proto::Queries::CreateDataObject)
			packet.reset(new Ramio::Proto::APCreateDataObject);
		else if (query == Ramio::Proto::Queries::SaveDataObject)
			packet.reset(new Ramio::Proto::APSaveDataObject);
		else if (query == Ramio::Proto::Queries::DeleteDataObject)
			packet.reset(new Ramio::Proto::APDeleteDataObject);
		else
			Q_ASSERT(0);

		if (packet)
		{
			packet->deserialize(docPacket);
			emit answerReceived(query, *packet, docPacket, from);
		}
	}
	else if (TypeStr == Ramio::Proto::packetTypename(Ramio::Proto::PacketType::Event))
	{
		QScopedPointer<Ramio::Proto::EventPacket> packet;
		Ramio::Proto::Events event = Ramio::Proto::eventByName(CommandStr);
		if (event == Ramio::Proto::Events::DataObjectCreated)
			packet.reset(new Ramio::Proto::EPDataObjectCreated);
		else if (event == Ramio::Proto::Events::DataObjectChanged)
			packet.reset(new Ramio::Proto::EPDataObjectChanged);
		else if (event == Ramio::Proto::Events::DataObjectDeleted)
			packet.reset(new Ramio::Proto::EPDataObjectDeleted);
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
