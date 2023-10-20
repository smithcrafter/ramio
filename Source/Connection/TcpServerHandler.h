/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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

class TcpServer;

class RAMIO_LIB_EXPORT TcpServerHandler : public ConnectionHandler
{
public:
	TcpServerHandler(const QHostAddress& address, quint16 port, QObject* parent = Q_NULLPTR);
	~TcpServerHandler() Q_DECL_OVERRIDE;

	bool startListen();

	qint64 sendQuery(Proto::Queries query, Ramio::Proto::QueryPacket& packet, const ConnectionInfo& to) Q_DECL_OVERRIDE;
	void sendAnswer(Proto::Queries query, const Proto::AnswerPacket& packet, const ConnectionInfo& to) Q_DECL_OVERRIDE;
	void sendEvent(Proto::Events query, const Proto::EventPacket& packet, const ConnectionInfo& to) Q_DECL_OVERRIDE;
	void sendTicket(Proto::Queries query, const Proto::TicketPacket& packet, const ConnectionInfo& to) Q_DECL_OVERRIDE;

private:
	TcpServer& server_;
	PacketBuilder& packetBuilder_;
	ProtocolOperator& protocolOperator_;
};

} // Ramio::
