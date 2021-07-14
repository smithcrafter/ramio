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

#pragma once

#include <Global/ResDesc.h>
#include <QtXml/QDomDocument>
#include <QtCore/QList>

#include <Items/MetaItemSerialization.h>

/**
	Package format example (XmlDocument)
	Message types: Query Event Answer Ticket

	<Message Type="Query" Command="GetData" ID="1" Session="uuid" Proto="1.0.0">
		<Parameters value1="1" value2="2" />
		<Options>
			<Name type="1" option="2">
		</Options>
		<Data Parameter="p1">
			<Content>
				Value
			</Content>
		</Data>
	</Message>
*/

namespace Ramio {
namespace Proto {

extern const QString MessageTag;
extern const QString OptionsTag;
extern const QString ParametersTag;
extern const QString DataTag;
extern const QString CommandStr;
extern const QString TypeStr;

struct RAMIO_LIB_EXPORT XmlDocument
{
	QDomDocument doc;
	QDomElement deMessage;
	QDomElement deOptions;
	QDomElement deParameters;
	QDomElement deData;

	XmlDocument();
	XmlDocument(const QByteArray& data);

	QByteArray data() const;
};

enum class PacketType
{
	Unset = 0,
	Query,
	Event,
	Answer,
	Ticket
};

RAMIO_LIB_EXPORT const QString& packetTypename(PacketType type);


enum class Queries
{
	Unknow = -1,
	Unset = 0,
	Login,
	StartSession,
	Logout,
	GetData,
	GetDataObject,
	GetDataSet,
	CreateDataObject,
	SaveDataObject,
	DeleteDataObject,
	RunAction,
	StartOperation,
	CancelOperation,
	EnumCount
};

RAMIO_LIB_EXPORT const QString& queryName(Queries query);
RAMIO_LIB_EXPORT Queries queryByName(const QString& name);

enum class Events
{
	Unknow = -1,
	Unset = 0,
	Disconnect,
	DataObjectCreated,
	DataObjectChanged,
	DataObjectDeleted,
	EnumCount
};

RAMIO_LIB_EXPORT const QString& eventName(Events event);
RAMIO_LIB_EXPORT Events eventByName(const QString& name);

struct RAMIO_LIB_EXPORT Packet
{
	QString sessionKey;
	qint64 pid;
	qint32 cmd;
	Ramio::Serialization::Options options;

	Packet(qint32 v_cmd, qint64 v_pid = 0);
	virtual ~Packet();

	virtual const QString& cmdName() const = 0;
	virtual void serialize(XmlDocument& msg) const = 0;
	virtual void deserialize(const XmlDocument& msg) = 0;
};

struct RAMIO_LIB_EXPORT QueryPacket : public Packet
{
	QueryPacket(Queries query, qint64 pid = 0) : Packet(qint32(query), pid) {}

	Queries query() const {return Queries(cmd);}
	const QString& cmdName() const Q_DECL_OVERRIDE {return queryName(query());}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT EventPacket : public Packet
{
	EventPacket(Events event, qint64 pid = 0) : Packet(qint32(event), pid) {}

	Events event() const {return Events(cmd);}
	const QString& cmdName() const Q_DECL_OVERRIDE { return eventName(event());}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT AnswerPacket : public Packet, ResDesc
{
	PacketType requestType;

	AnswerPacket(PacketType v_type, qint32 cmd, qint64 pid = 0) : Packet(cmd, pid), requestType(v_type) {}

	const QString& cmdName() const Q_DECL_OVERRIDE { return requestType == PacketType::Query ? queryName(Queries(cmd)) : eventName(Events(cmd));}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT TicketPacket : public Packet, ResDesc
{
	PacketType requestType;

	TicketPacket(qint32 cmd, qint64 pid = 0) : Packet(cmd, pid) {}

	Queries query() const {return Queries(cmd);}
	const QString& cmdName() const Q_DECL_OVERRIDE {return queryName(query());}

};

} // Proto::
} // Ramio::
