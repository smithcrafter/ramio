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
// Qt5
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

namespace Ramio {

TcpServer::TcpServer(const QHostAddress& address, quint16 port, QObject* parent, quint64 flags)
	: QObject(parent),
	  address_(address),
	  port_(port),
	  flags_(flags),
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
	if (flags_ & (1<<R_LOG_FLAG))
		PLOG(tr("[Сервер] прослушивание на порту %1").arg(server_.serverPort()));
	return RD_NO_ERROR;
}

ResDesc TcpServer::close()
{
	if (server_.isListening())
		return RD_NOT_CURENT_ACTION_ERROR;
	if (flags_ & (1<<R_LOG_FLAG))
		PLOG(tr("[Сервер] освобожден с порта %1").arg(server_.serverPort()));
	server_.close();
	return RD_NO_ERROR;
}

ResDesc TcpServer::write(quint16 connectionId, const QByteArray& data)
{
	if (auto* socket = connections_.key(connectionId, Q_NULLPTR))
	{
		socket->write(data);
		if (flags_ & (1<<R_LOG_FLAG))
			PLOG(tr("[Сервер-Сокет][%1] отправлен пакет %2 байт на  %4:%5 %3").arg(connectionId)
				 .arg(data.size()).arg(QString(data), socket->peerAddress().toString()).arg(socket->peerPort()));
		return RD_NO_ERROR;
	}
	if (flags_ & (1<<R_LOG_FLAG))
		DLOG(tr("[Сервер-Сокет][%1] Не найдено соединение").arg(connectionId));
	return RD_DEVICE_ERROR;
}

void TcpServer::onServerNewConnection()
{
	if (QTcpSocket* socket = server_.nextPendingConnection())
	{
		if (++connectionId_ == 0) connectionId_++;
		connect(socket, &QTcpSocket::stateChanged, this, &TcpServer::onSocketStateChanged);
		connect(socket, &QTcpSocket::readyRead, this, &TcpServer::onSocketReadyRead);
		connect(socket, &QTcpSocket::disconnected, this, &TcpServer::onSocketDisconnected);
		//connections_.insert(socket, connectionId_);
		connections_[socket]=connectionId_;
		emit clientConnected(ConnectionInfo(connections_.value(socket), *socket));
		if (flags_ & (1<<R_LOG_FLAG))
			PLOG(tr("[Сервер][%1] новое подключение %2:%3").arg(connections_.value(socket))
				 .arg(socket->peerAddress().toString()).arg(socket->peerPort()));
	}
}

void TcpServer::onServerAcceptError(QAbstractSocket::SocketError socketError)
{
	if (flags_ & (1<<R_LOG_FLAG))
		PLOG(tr("[Сервер] ошибка %1").arg(socketError));
}

void TcpServer::onSocketStateChanged(QAbstractSocket::SocketState state)
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
		if (flags_ & (1<<R_LOG_FLAG))
			PLOG(tr("[Сервер-Сокет] изменилось состояние %2:%3 - %1")
				 .arg(socketStateName(state), socket->peerAddress().toString()).arg(socket->peerPort()));
}

void TcpServer::onSocketReadyRead()
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
	{
		QByteArray ba = socket->readAll();
		if (flags_ & (1<<R_LOG_FLAG))
			PLOG(tr("[Сервер-Сокет] получен пакет %1 байт от  %2:%3 [%4]")
				 .arg(ba.size()).arg(socket->peerAddress().toString()).arg(socket->peerPort()).arg(connections_.value(socket)));
		emit bytesReceived(ba, ConnectionInfo(connections_.value(socket), *socket));
	}
}

void TcpServer::onSocketDisconnected()
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
	{
		quint16 connId = connections_.value(socket);
		emit clientDisconnected(ConnectionInfo(connId, *socket));
		connections_.remove(socket);
		if (flags_ & (1<<R_LOG_FLAG))
			PLOG(tr("[Сервер] отключение [%1] - %2:%3").arg(connId).arg(socket->peerAddress().toString()).arg(socket->peerPort()));
		socket->deleteLater();
	}
}

} // Ramio::
