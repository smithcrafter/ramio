/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "Protocol.h"

namespace Ramio {
namespace Proto {

const QString MessageTag = "Message";
const QString OptionsTag = "Options";
const QString ParametersTag = "Parameters";
const QString DataTag = "Data";

const QString LoginStr = "Login";
const QString PrepareSessionStr = "PrepareSession";
const QString StartSessionStr = "StartSession";
const QString RestoreSessionStr = "RestoreSession";
const QString FinishSessionStr = "FinishSession";
const QString LogoutStr = "Logout";
const QString GetDataStr = "GetData";
const QString GetDataSetStr = "GetDataSet";
const QString CreateDataObjectStr = "CreateDataObject";
const QString SaveDataObjectStr = "SaveDataObject";
const QString DeleteDataObjectStr = "DeleteDataObject";

const QString DisconnectStr = "Disconnect";
const QString DataObjectCreatedStr = "DataObjectCreated";
const QString DataObjectChangedStr = "DataObjectChanged";
const QString DataObjectDeletedStr = "DataObjectDeleted";

const QString ResStr = "Res";
const QString DescSrt = "Desc";
const QString CommandStr = "Command";
const QString TypeStr = "Type";
const QString QueryStr = "Query";
const QString EventStr = "Event";
const QString AnswerStr = "Answer";
const QString TicketStr = "Ticket";
const QString SessionStr = "Session";
const QString PacketIDStr = "ID";

const QString& packetTypename(PacketType type)
{
	if (type == PacketType::Query)
		return QueryStr;
	if (type == PacketType::Event)
		return EventStr;
	if (type == PacketType::Answer)
		return AnswerStr;
	if (type == PacketType::Ticket)
		return TicketStr;
	return Ramio::emptyString;
}

const QString& queryName(Queries query)
{
	if (Queries::Login == query)
		return LoginStr;
//	if (Queries::PrepareSession == query)
//		return PrepareSessionStr;
	if (Queries::StartSession == query)
		return StartSessionStr;
//	if (Queries::RestoreSession == query)
//		return RestoreSessionStr;
//	if (Queries::FinishSession == query)
//		return FinishSessionStr;
	if (Queries::Logout == query)
		return LogoutStr;
	if (Queries::GetData == query)
		return GetDataStr;
	if (Queries::GetDataSet == query)
		return GetDataSetStr;
	if (Queries::CreateDataObject == query)
		return CreateDataObjectStr;
	if (Queries::SaveDataObject == query)
		return SaveDataObjectStr;
	if (Queries::DeleteDataObject == query)
		return DeleteDataObjectStr;

	Q_ASSERT(0);
	return Ramio::emptyString;
}

Queries queryByName(const QString& name)
{
	if (LoginStr == name)
		return Queries::Login;
//	if (PrepareSessionStr == name)
//		return Queries::PrepareSession;
	if (StartSessionStr == name)
		return Queries::StartSession;
//	if (RestoreSessionStr == name)
//		return Queries::RestoreSession;
//	if (FinishSessionStr == name)
//		return Queries::FinishSession;
	if (LogoutStr == name)
		return Queries::Logout;
	if (GetDataStr == name)
		return Queries::GetData;
	if (GetDataSetStr == name)
		return Queries::GetDataSet;
	if (CreateDataObjectStr == name)
		return Queries::CreateDataObject;
	if (SaveDataObjectStr == name)
		return Queries::SaveDataObject;
	if (DeleteDataObjectStr == name)
		return Queries::DeleteDataObject;

	Q_ASSERT(0);
	return Queries::Unset;
}

const QString& eventName(Events event)
{
	if (Events::Disconnect == event)
		return DisconnectStr;
	if (Events::DataObjectCreated == event)
		return DataObjectCreatedStr;
	if (Events::DataObjectChanged == event)
		return DataObjectChangedStr;
	if (Events::DataObjectDeleted == event)
		return DataObjectDeletedStr;
	return Ramio::emptyString;
}

Events eventByName(const QString &name)
{
	if (DisconnectStr == name)
		return Events::Disconnect;
	if (DataObjectCreatedStr == name)
		return Events::DataObjectCreated;
	if (DataObjectChangedStr == name)
		return Events::DataObjectChanged;
	if (DataObjectDeletedStr == name)
		return Events::DataObjectDeleted;

	Q_ASSERT(0);
	return Events::Unset;
}

XmlDocument::XmlDocument()
{
	deMessage = doc.createElement(Proto::MessageTag);
	doc.appendChild(deMessage);
	deOptions = doc.createElement(Proto::OptionsTag);
	deMessage.appendChild(deOptions);
	deParameters = doc.createElement(Proto::ParametersTag);
	deMessage.appendChild(deParameters);
	deData = doc.createElement(Proto::DataTag);
	deMessage.appendChild(deData);
}

XmlDocument::XmlDocument(const QByteArray& data)
{
	doc.setContent(data);
	deMessage = doc.firstChildElement(Proto::MessageTag);
	deOptions = deMessage.firstChildElement(Proto::OptionsTag);
	deParameters = deMessage.firstChildElement(Proto::ParametersTag);
	deData = deMessage.firstChildElement(Proto::DataTag);
}

QByteArray XmlDocument::data() const
{
	return doc.toByteArray();
}

Packet::Packet(qint32 v_cmd, qint64 v_pid)
	: pid(v_pid), cmd(v_cmd)
{}

Packet::~Packet() = default;


void QueryPacket::serialize(XmlDocument& msg) const
{
	msg.deMessage.setAttribute(TypeStr, packetTypename(PacketType::Query));
	msg.deMessage.setAttribute(CommandStr, cmdName());
	if (!sessionKey.isEmpty())
		msg.deMessage.setAttribute(SessionStr, sessionKey);
	msg.deMessage.setAttribute(PacketIDStr, QString::number(pid));
	options.serialize(msg.deOptions);
}

void QueryPacket::deserialize(const XmlDocument& msg)
{
	sessionKey = msg.deMessage.attribute(SessionStr);
	pid = msg.deMessage.attribute(PacketIDStr).toLong();
	options.deserialize(msg.deOptions);
}

void EventPacket::serialize(XmlDocument& msg) const
{
	msg.deMessage.setAttribute(TypeStr, packetTypename(PacketType::Event));
	msg.deMessage.setAttribute(CommandStr, cmdName());
	if (!sessionKey.isEmpty())
		msg.deMessage.setAttribute(SessionStr, sessionKey);
	if (pid)
		msg.deMessage.setAttribute(PacketIDStr, QString::number(pid));
	options.serialize(msg.deOptions);
}

void EventPacket::deserialize(const XmlDocument& msg)
{
	sessionKey = msg.deMessage.attribute(SessionStr);
	pid = msg.deMessage.attribute(PacketIDStr).toLong();
	options.deserialize(msg.deOptions);
}

void AnswerPacket::serialize(XmlDocument& msg) const
{
	msg.deMessage.setAttribute(TypeStr, packetTypename(PacketType::Answer));
	msg.deMessage.setAttribute(CommandStr, cmdName());
	if (!sessionKey.isEmpty())
		msg.deMessage.setAttribute(SessionStr, sessionKey);
	msg.deMessage.setAttribute(PacketIDStr, QString::number(pid));
	msg.deMessage.setAttribute(ResStr, res);
	msg.deMessage.setAttribute(DescSrt, desc);
	options.serialize(msg.deOptions);
}

void AnswerPacket::deserialize(const XmlDocument& msg)
{
	sessionKey = msg.deMessage.attribute(SessionStr);
	pid = msg.deMessage.attribute(PacketIDStr).toLong();
	res = msg.deMessage.attribute(ResStr).toInt();
	desc = msg.deMessage.attribute(DescSrt);
	options.deserialize(msg.deOptions);
}

} // Proto::
} // Ramio::
