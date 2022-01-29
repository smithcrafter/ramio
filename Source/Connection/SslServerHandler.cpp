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

#include "SslServerHandler.h"
#include <RamioProtocol>
#include <Network/SslServer.h>
#include <Network/PacketBuilder.h>

namespace Ramio {

SslServerHandler::SslServerHandler(const QHostAddress& address, quint16 port, QObject* parent)
	: ConnectionHandler(parent),
	  server_(*new SslServer(address, port, this, 0)),
	  packetBuilder_(*new PacketBuilder(PacketBuilderOptions({true}), this)),
	  protocolOperator_(*new ProtocolOperator(this))
{
	QObject::connect(&server_, &SslServer::bytesReceived, &packetBuilder_, &PacketBuilder::onBytesReceived);
	QObject::connect(&packetBuilder_, &PacketBuilder::packetReceived, &protocolOperator_, &ProtocolOperator::onPacketReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::queryReceived, this, &SslServerHandler::queryReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::answerReceived, this, &SslServerHandler::answerReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::eventReceived, this, &SslServerHandler::eventReceived);
	QObject::connect(&server_, &SslServer::clientDisconnected, this, &SslServerHandler::clientDisconnected);
}

SslServerHandler::~SslServerHandler()
{
}

bool SslServerHandler::startListen(const QSslConfiguration& conf)
{
	server_.setConfiguration(conf);
	return server_.start();
}

qint64 SslServerHandler::sendQuery(Proto::Queries, Proto::QueryPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
	return 0;
}


void SslServerHandler::sendAnswer(Proto::Queries, const Proto::AnswerPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void SslServerHandler::sendEvent(Proto::Events, const Proto::EventPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

void SslServerHandler::sendTicket(Proto::Queries, const Proto::TicketPacket& packet, const ConnectionInfo& to)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	packetBuilder_.write(to.connectionId, docPacket.doc.toString().toUtf8(), server_);
}

} // Ramio::
