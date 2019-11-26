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

#include "TcpServerHandler.h"
#include <Ramio/Protocol>
#include <Ramio/Network>

namespace Ramio {

TcpServerHandler::TcpServerHandler(const QHostAddress& address, quint16 port, QObject* parent)
	: ConnectionHandler(parent),
	  server_(*new TcpServer(address, port, this, 0)),
	  packetBuilder_(*new PacketBuilder(this)),
	  protocolOperator_(*new ProtocolOperator(this))
{
	QObject::connect(&server_, &TcpServer::bytesReceived, &packetBuilder_, &PacketBuilder::onBytesReceived);
	QObject::connect(&packetBuilder_, &PacketBuilder::packetReceived, &protocolOperator_, &ProtocolOperator::onPacketReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::queryReceived, this, &TcpServerHandler::queryReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::answerReceived, this, &TcpServerHandler::answerReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::eventReceived, this, &TcpServerHandler::eventReceived);
	QObject::connect(&server_, &TcpServer::clientDisconnected, this, &TcpServerHandler::clientDisconnected);
}

void TcpServerHandler::startListen()
{
	server_.start();
}

TcpServerHandler::~TcpServerHandler() = default;

void TcpServerHandler::sendAnswer(Proto::Queries query, const Proto::AnswerPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void TcpServerHandler::sendEvent(Proto::Events query, const Proto::EventPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void TcpServerHandler::sendTicket(Proto::Queries query, const Proto::TicketPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

} // Ramio::
