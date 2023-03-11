/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ConnectionHandler.h"

namespace Ramio {

class TcpClient;

class RAMIO_LIB_EXPORT TcpClientHandler : public ConnectionHandler
{
public:
	TcpClientHandler(const QString& hostIp = emptyString, quint16 port = 0, QObject* parent = Q_NULLPTR);
	~TcpClientHandler() Q_DECL_OVERRIDE;

	bool isConnected() const;
	void connectToHost(const QString& hostIp = emptyString, quint16 post = 0);
	void disconnectFromHost();

	qint64 sendQuery(Proto::Queries query, Proto::QueryPacket& packet);

	qint64 sendQuery(Proto::Queries query, Proto::QueryPacket& packet, const ConnectionInfo& to) Q_DECL_OVERRIDE;
	void sendAnswer(Proto::Queries, const Proto::AnswerPacket&, const ConnectionInfo&) Q_DECL_OVERRIDE {Q_ASSERT(0);}
	void sendEvent(Proto::Events, const Proto::EventPacket&, const ConnectionInfo&) Q_DECL_OVERRIDE {Q_ASSERT(0);}
	void sendTicket(Proto::Queries, const Proto::TicketPacket&, const ConnectionInfo&) Q_DECL_OVERRIDE {Q_ASSERT(0);}

	const TcpClient& client() const {return client_;}

private:
	TcpClient& client_;
	PacketBuilder& packetBuilder_;
	ProtocolOperator& protocolOperator_;
};

} // Ramio::
