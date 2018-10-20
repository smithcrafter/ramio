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

#pragma once

#include "NetGlobal.h"
#include <Ramio/ResDesc>
#include <QtCore/QObject>

namespace Ramio {

class DLL_EXPORT TcpServer : public QObject
{
	Q_OBJECT
public:
	TcpServer(const QHostAddress& address, quint16 port, QObject* parent = Q_NULLPTR);
	~TcpServer() Q_DECL_OVERRIDE;

	ResDesc listen(quint16 port = 0, const QHostAddress& host = QHostAddress::AnyIPv4);
	ResDesc close();

	ResDesc write(quint16 connectionId, const QByteArray& data);

public slots:
	void start() {listen();}
	void stop() {close();}

signals:
	void clientConnected(const ConnectionInfo& client);
	void bytesReceived(const QByteArray& data, const ConnectionInfo& client);
	void clientDisconnected(const ConnectionInfo& client);


private:
	void onServerNewConnection();
	void onServerAcceptError(QAbstractSocket::SocketError socketError);
	void onSocketStateChanged(QAbstractSocket::SocketState state);
	void onSocketReadyRead();
	void onSocketDisconnected();

private:
	QHostAddress address_;
	quint16 port_;
	QTcpServer& server_;
	quint16 connectionId_ = 0;
	QMap<QTcpSocket*, quint16> connections_;
};

} // Ramio::
