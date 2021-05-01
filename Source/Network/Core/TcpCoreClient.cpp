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
#include "TcpCoreClient.h"
#include <Log/Log.h>
// Qt5
#include <QtNetwork/QTcpSocket>

namespace Ramio {

TcpCoreClient::TcpCoreClient(QTcpSocket& socket, const QHostAddress& address, quint16 port, QObject* parent)
	: QObject(parent),
	  socket_(socket),
	  address_(address),
	  port_(port)
{
	connect(&socket_, &QTcpSocket::stateChanged, this, &TcpCoreClient::onSocketStateChanged);
	connect(&socket_, &QTcpSocket::readyRead, this, &TcpCoreClient::onSocketReadyRead);
}

QAbstractSocket::SocketState TcpCoreClient::socketState() const
{
	return socket_.state();
}

ResDesc TcpCoreClient::connectToHost(const QHostAddress& host, quint16 port)
{
	if (socket_.state() == QAbstractSocket::ConnectedState)
		return RD_NOT_CRITICAL_ERROR;
	if (port_!= port && port != 0)
		port_ = port;
	if (address_ != host && host != QHostAddress::Null)
		address_ = host;
	if (socket_.state() == QAbstractSocket::HostLookupState || socket_.state() == QAbstractSocket::ConnectingState)
		return RD_NO_ERROR;

	connectionId_++;
	socket_.connectToHost(address_, port_);
	//socket_.waitForConnected(10);

	PLOG(tr("[Клиент] подключение к адресу %1 на порт %2").arg(address_.toString()).arg(port_));
	return RD_OK;
}

qint64 TcpCoreClient::write(const QByteArray& data)
{
	data_.append(Packet{++pid_, data});
#ifdef Q_OS_WIN32
	QMetaObject::invokeMethod(this, &TcpCoreClient::writeNextBlock, Qt::QueuedConnection);
#else
	QMetaObject::invokeMethod(this, "writeNextBlock", Qt::QueuedConnection);
#endif
	return pid_;
}

void TcpCoreClient::restart()
{
	stop();
	socket_.waitForDisconnected();
	start();
}

ResDesc TcpCoreClient::close()
{
	if (socket_.state() == QAbstractSocket::UnconnectedState || socket_.state() == QAbstractSocket::ClosingState)
		return RD_NOT_CRITICAL_ERROR;

	socket_.disconnectFromHost();
	return RD_NO_ERROR;
}

void TcpCoreClient::onSocketStateChanged(QAbstractSocket::SocketState state)
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
		PLOG(tr("[Клиент] изменилось состояние %2:%3 - %1")
			 .arg(socketStateName(state), socket->peerAddress().toString()).arg(socket->peerPort()));

	if (state == QAbstractSocket::ConnectedState)
	{
		if (!isConnected_)
			emit connected();
		isConnected_ = true;
		writeNextBlock();
	}
	else if (state != QAbstractSocket::ConnectingState && state != QAbstractSocket::HostLookupState)
	{
		if (isConnected_)
			emit disconnected();
		isConnected_ = false;
		while (!data_.isEmpty())
		{
			emit dataSendResult(data_.constFirst().id, ResDesc());
			data_.removeFirst();
		}
	}
	emit socketStateChanged(state);
}

void TcpCoreClient::onSocketReadyRead()
{
	QByteArray data = socket_.readAll();

	if (plog_)
		PLOG(tr("[Клиент] получен пакет %1 байт от  %2:%3 [%4]")
			 .arg(data.size()).arg(socket_.peerAddress().toString()).arg(socket_.peerPort())
			 .arg(connectionId_));

	emit bytesReceived(data, ConnectionInfo(connectionId_, socket_));
}

void TcpCoreClient::writeNextBlock()
{
	if (socket_.state() != QAbstractSocket::ConnectedState && socket_.state() != QAbstractSocket::ConnectingState && QAbstractSocket::HostLookupState)
	{
		ResDesc rd = reconnect();
		if (!rd.noCriticalError())
			while (!data_.isEmpty())
			{
				emit dataSendResult(data_.constFirst().id, rd);
				data_.removeFirst();
			}
	}
	else
	{
		while (!data_.isEmpty())
		{
			realWrite(data_.constFirst().data);
			emit dataSendResult(data_.constFirst().id, RD_NO_ERROR);
			data_.removeFirst();
		}
	}
}

void TcpCoreClient::realWrite(const QByteArray& data)
{
	socket_.write(data);
	if (plog_)
		PLOG(tr("[Клиент] отправлен пакет %1+4 байт от  %2:%3")
			 .arg(data.size()-4).arg( socket_.peerAddress().toString()).arg(socket_.peerPort()));
}

} // Ramio::
