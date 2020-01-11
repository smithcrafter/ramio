/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ramio.h"
#include <QtCore/QObject>
class QHostAddress;

namespace Ramio {


struct ConnectionInfo;
class PacketBuilder;
class ProtocolOperator;
namespace Proto {
struct QueryPacket;
struct AnswerPacket;
struct EventPacket;
struct TicketPacket;
struct XmlDocument;
enum class Queries;
enum class Events;
}

class RAMIO_LIB_EXPORT ConnectionHandler : public QObject
{
	Q_OBJECT
public:
	ConnectionHandler(QObject* parent = Q_NULLPTR) : QObject(parent) {}
	~ConnectionHandler() Q_DECL_OVERRIDE = default;

	virtual qint64 sendQuery(Proto::Queries query, Proto::QueryPacket& packet,  const ConnectionInfo& to) = 0;
	virtual void sendAnswer(Proto::Queries query, const Proto::AnswerPacket& packet, const ConnectionInfo& to) = 0;
	virtual void sendEvent(Proto::Events query, const Proto::EventPacket& packet, const ConnectionInfo& to) = 0;
	virtual void sendTicket(Proto::Queries query, const Proto::TicketPacket& packet, const ConnectionInfo& to) = 0;

signals:
	void queryReceived(Proto::Queries query, const Proto::QueryPacket& packet, const ConnectionInfo& from);
	void answerReceived(Proto::Queries query, const Proto::AnswerPacket& packet,
						const Proto::XmlDocument& doc, const ConnectionInfo& from);
	void eventReceived(Proto::Events event, const Proto::EventPacket& packet,
						const Proto::XmlDocument& doc, const ConnectionInfo& from);
};

} // Ramio::
