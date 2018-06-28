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

#include "TcpServer.h"
#include <Log/Log.h>
// Qt
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

namespace Ramio {

TcpServer::TcpServer(const QHostAddress& address, quint16 port, QObject* parent)
	: QObject(parent),
	  address_(address),
	  port_(port),
	  server_(*(new QTcpServer(this)))
{
	connect(&server_, &QTcpServer::newConnection, this, &TcpServer::onServerNewConnection);
	connect(&server_, &QTcpServer::acceptError, this, &TcpServer::onServerAcceptError);
}

TcpServer::~TcpServer()
{
	this->close();
}

ResDesc TcpServer::listen(quint16 port, const QHostAddress& host)
{
	if (server_.isListening())
		return RD_NOT_CRITICAL_ERROR;
	if (port_!= port && port != 0)
		port_ = port;
	if (address_ != host && host != QHostAddress::AnyIPv4)
		address_ = host;
	if (!server_.listen(address_, port_))
		return RD_DEVICE_ERROR;
	PLOG(tr("[Сервер] прослушивание на порту %1").arg(server_.serverPort()));
	return RD_NO_ERROR;
}

ResDesc TcpServer::close()
{
	if (server_.isListening())
		return RD_NOT_CURENT_ACTION_ERROR;
	PLOG(tr("[Сервер] освобожден с порта %1").arg(server_.serverPort()));
	server_.close();
	return RD_NO_ERROR;
}

ResDesc TcpServer::write(quint16 connectionId, const QByteArray& data)
{
	if (auto* socket = connections_.key(connectionId, Q_NULLPTR))
	{
		auto size = quint32(data.size());//ba.mid(0,4).toHex().toInt(&ok, 16);
		QByteArray sizeba(4, char(0));
		*reinterpret_cast<quint32*>(sizeba.data()) = size;
		socket->write(sizeba.append(data));
		PLOG(tr("[Сервер-Сокет] отправлен пакет %1+4 байт на  %3:%4 %2") //.replace("<", "&lt;").replace("\n", "<br>")
			 .arg(size).arg(QString(data), socket->peerAddress().toString()).arg(socket->peerPort()));
		return RD_NO_ERROR;
	}
	return RD_DEVICE_ERROR;
}

void TcpServer::onServerNewConnection()
{
	if (QTcpSocket* socket = server_.nextPendingConnection())
	{
		if (++connectionId_ == 0) connectionId_++;
		connect(socket, &QTcpSocket::stateChanged, this, &TcpServer::onSocketStateChanged);
		connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onSocketReadyRead);
		connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
		connect(socket, &QTcpSocket::destroyed, this, &TcpServer::onSocketDestroyed);
		connections_.insert(socket, connectionId_);
		emit clientConnected(ConnectionInfo(connections_.value(socket), *socket));
		PLOG(tr("[Сервер] новое подключение - %1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort()));
	}
}

void TcpServer::onServerAcceptError(QAbstractSocket::SocketError socketError)
{
	PLOG(tr("[Сервер] ошибка %1").arg(socketError));
}

void TcpServer::onSocketStateChanged(QAbstractSocket::SocketState state)
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
		PLOG(tr("[Сервер-Сокет] изменилось состояние %2:%3 - %1")
			 .arg(socketStateName(state), socket->peerAddress().toString()).arg(socket->peerPort()));
}

void TcpServer::onSocketReadyRead()
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
	{
		QByteArray ba = socket->readAll();
		PLOG(tr("[Сервер-Сокет] получен пакет %1 байт от  %2:%3 [%4]")
			 .arg(ba.size()).arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(connections_.value(socket)));

		emit bytesReceived(ba, ConnectionInfo(connections_.value(socket), *socket));
	}
}

void TcpServer::onSocketDestroyed()
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
	{
		emit clientDisconnected(ConnectionInfo(connections_.value(socket), *socket));
		connections_.remove(socket);
	}
}

} // Ramio::
