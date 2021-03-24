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

#include "PacketBuilder.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include <Log/Log.h>
// Qt5
#include <QtEndian>

namespace Ramio {

PacketBuilder::PacketBuilder(QObject* parent)
	: QObject(parent)
{
}

PacketBuilder::~PacketBuilder()
{
}

qint64 PacketBuilder::write(const QByteArray& data, TcpCoreClient& client)
{
	QByteArray sizeba(4, char(0));
	qint32 dsize = data.size();
	qToBigEndian(dsize, sizeba.data());
	return client.write(sizeba.append(data));
}

ResDesc PacketBuilder::write(quint16 connectionId, const QByteArray& data, TcpCoreServer& server)
{
	QByteArray sizeba(4, char(0));
	qint32 dsize = data.size();
	qToBigEndian(dsize, sizeba.data());
	return server.write(connectionId, sizeba.append(data));
}

void PacketBuilder::onBytesReceived(const QByteArray& data, const ConnectionInfo& from)
{
	QByteArray& buffer = buffer_[from.connectionId];
	buffer.append(data);
	qint32 basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;

	while (basize > 0 && buffer.size() >= (basize+4))
	{
		QByteArray ba = buffer.mid(0, int(basize)+4);
		buffer.remove(0, int(basize)+4);
		DLOG("[PacketBuilder]" % tr(" получен пакет %1+4 байт от %2:%3[%4]")
			 .arg(basize).arg(from.address.toString()).arg(from.port).arg(from.connectionId));
		emit packetReceived(ba.mid(4), from);
		basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;
	}
}

} // Ramio::
