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

#include <Global/ResDesc.h>
#include <Network/NetGlobal.h>
#include <QtCore/QObject>

namespace Ramio {

class DLL_EXPORT TcpClient : public QObject
{
	Q_OBJECT
public:
	TcpClient(const QHostAddress& address, quint16 port, QObject* parent = Q_NULLPTR);
	~TcpClient() Q_DECL_OVERRIDE = default;

	ResDesc connectToHost(const QHostAddress& host = QHostAddress::AnyIPv4, quint16 port = 0);
	ResDesc reconnect() {return connectToHost();}
	ResDesc close();

	qint64 write(const QByteArray& data);


public slots:
	void start() {connectToHost();}
	void stop() {close();}

signals:
	void connected();
	void disconnected();
	void dataSendResult(qint64 pId, ResDesc rd);
	void bytesReceived(const QByteArray& data, const ConnectionInfo& from);

private slots:
	void writeNextBlock();

private:
	void onSocketStateChanged(QAbstractSocket::SocketState state);
	void onSocketReadyRead();
	void realWrite(const QByteArray& data);

	struct Packet
	{
		qint64 id;
		QByteArray data;
	};

private:
	QHostAddress address_;
	quint16 port_;
	class QTcpSocket& socket_;
	quint16 connectionId_ = 0;
	QList<Packet> data_;
	qint64 pid_ = 0;
};

} // Ramio::
