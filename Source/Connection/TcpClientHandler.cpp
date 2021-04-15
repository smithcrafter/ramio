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

#include "TcpClientHandler.h"
#include <RamioProtocol>
#include <RamioNetwork>

namespace Ramio {

TcpClientHandler::TcpClientHandler(const QString& hostIp, quint16 port, QObject* parent)
	: ConnectionHandler(parent),
	  client_(*new TcpClient(QHostAddress(hostIp), port, this)),
	  packetBuilder_(*new PacketBuilder(this)),
	  protocolOperator_(*new ProtocolOperator(this))
{
	QObject::connect(&client_, &TcpClient::bytesReceived, &packetBuilder_, &PacketBuilder::onBytesReceived);
	QObject::connect(&packetBuilder_, &PacketBuilder::packetReceived, &protocolOperator_, &ProtocolOperator::onPacketReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::queryReceived, this, &TcpClientHandler::queryReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::answerReceived, this, &TcpClientHandler::answerReceived);
	QObject::connect(&protocolOperator_, &ProtocolOperator::eventReceived, this, &TcpClientHandler::eventReceived);
	QObject::connect(&client_, &TcpClient::connected, this, &TcpClientHandler::connected);
	QObject::connect(&client_, &TcpClient::disconnected, this, &TcpClientHandler::disconnected);
}

TcpClientHandler::~TcpClientHandler()
{
}

bool TcpClientHandler::isConnected() const
{
	return client_.socketState() == QAbstractSocket::SocketState::ConnectedState;
}

void TcpClientHandler::connectToHost(const QString& host, quint16 post)
{
	client_.connectToHost(QHostAddress(host), post);
}

void TcpClientHandler::disconnectFromHost()
{
	client_.close();
}

qint64 TcpClientHandler::sendQuery(Proto::Queries query, Proto::QueryPacket &packet)
{
	return sendQuery(query, packet, ConnectionInfo());
}

qint64 TcpClientHandler::sendQuery(Proto::Queries, Proto::QueryPacket& packet, const ConnectionInfo&)
{
	Proto::XmlDocument docPacket;
	packet.serialize(docPacket);
	QByteArray data = docPacket.doc.toByteArray();
	return packetBuilder_.write(data, client_);
}

} // Ramio::
