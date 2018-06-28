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

#include "TcpClient.h"
#include <Log/Log.h>
// Qt
#include <QtNetwork/QTcpSocket>

namespace Ramio {

TcpClient::TcpClient(const QHostAddress& address, quint16 port, QObject* parent)
	: QObject(parent),
	  address_(address),
	  port_(port),
	  socket_(*(new QTcpSocket(this)))

{
	connect(&socket_, &QTcpSocket::stateChanged, this, &TcpClient::onSocketStateChanged);
	connect(&socket_, &QTcpSocket::readyRead, this, &TcpClient::onSocketReadyRead);
}

ResDesc TcpClient::connectToHost(const QHostAddress& host, quint16 port)
{
	if (socket_.state() == QAbstractSocket::ConnectedState)
		return RD_NOT_CRITICAL_ERROR;
	if (port_!= port && port != 0)
		port_ = port;
	if (address_ != host && host != QHostAddress::AnyIPv4)
		address_ = host;

	connectionId_++;
	socket_.connectToHost(address_, port_);
	socket_.waitForConnected(20);

	PLOG(tr("[Клиент] подключение к адресу %1 на порт %2").arg(address_.toString()).arg(port_));
	return RD_NO_ERROR;
}

qint64 TcpClient::write(const QByteArray& data)
{
	data_.append(Packet{++pid_, data});
#ifdef Q_OS_WIN32
	QMetaObject::invokeMethod(this, &TcpClient::writeNextBlock, Qt::QueuedConnection);
#else
	QMetaObject::invokeMethod(this, "writeNextBlock", Qt::QueuedConnection);
#endif
	return pid_;
}

ResDesc TcpClient::close()
{
	if (socket_.state() == QAbstractSocket::UnconnectedState)
		return RD_NOT_CRITICAL_ERROR;

	socket_.disconnectFromHost();
	return RD_NO_ERROR;
}

void TcpClient::onSocketStateChanged(QAbstractSocket::SocketState state)
{
	if (auto* socket = reinterpret_cast<QTcpSocket*>(sender()))
		PLOG(tr("[Клиент] изменилось состояние %2:%3 - %1")
			 .arg(socketStateName(state), socket->peerAddress().toString()).arg(socket->peerPort()));

	if (state == QAbstractSocket::ConnectedState)
	{
		emit connected();
		writeNextBlock();
	}
	else if (state != QAbstractSocket::ConnectingState && state != QAbstractSocket::HostLookupState)
	{
		emit disconnected();
		while (!data_.isEmpty())
		{
			emit dataSendResult(data_.constFirst().id, ResDesc());
			data_.removeFirst();
		}
	}
}

void TcpClient::onSocketReadyRead()
{
	QByteArray data = socket_.readAll();

	PLOG(tr("[Клиент] получен пакет %1 байт от  %2:%3 [%4]")
		 .arg(data.size()).arg(socket_.peerAddress().toString()).arg(socket_.peerPort()).arg(connectionId_));

	emit bytesReceived(data, ConnectionInfo(connectionId_, socket_));
}

void TcpClient::writeNextBlock()
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

void TcpClient::realWrite(const QByteArray& data)
{
	socket_.write(data);
	PLOG(tr("[Клиент] отправлен пакет %1+4 байт от  %3:%4 %2")
		 .arg(data.size()-4).arg(QString(data.mid(4)), socket_.peerAddress().toString()).arg(socket_.peerPort()));
}

} // Ramio::
