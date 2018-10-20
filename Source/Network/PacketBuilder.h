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

#include <Network/NetGlobal.h>
#include <Ramio/ResDesc>

namespace Ramio {

class DLL_EXPORT PacketBuilder : public QObject
{
	Q_OBJECT
public:
	PacketBuilder(QObject* parent = Q_NULLPTR);

	virtual qint64 write(const QByteArray& data, TcpClient& client);
	virtual ResDesc write(quint16 connectionId, const QByteArray& data, TcpServer& server);

public slots:
	void onBytesReceived(const QByteArray& data, const ConnectionInfo& from);

signals:
	void packetReceived(const QByteArray& data, const ConnectionInfo& from);

private:
	QMap<quint32, QByteArray> buffer_;
};

} // Ramio::
