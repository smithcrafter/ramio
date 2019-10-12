#pragma once

/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "../NetGlobal.h"
#include <Ramio/ResDesc>
#include <QtCore/QObject>

#define R_LOG_FLAG 1

namespace Ramio {

class DLL_EXPORT TcpCoreServer : public QObject
{
	Q_OBJECT
public:
	TcpCoreServer(QTcpServer& server, const QHostAddress& address, quint16 port, QObject* parent = Q_NULLPTR, quint64 flags = 0);
	~TcpCoreServer() Q_DECL_OVERRIDE;

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
	QTcpServer& server_;
	QHostAddress address_;
	quint16 port_;
	quint64 flags_;
	quint16 connectionId_ = 0;
	QMap<QTcpSocket*, quint16> connections_;
};

} // Ramio::
