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

#include "PacketBuilder.h"
#include "TcpClient.h"
#include "TcpServer.h"
#include <Log/Log.h>
#include <QtEndian>

namespace Ramio {

/* TODO переделать порядок пакетов
 * QByteArray sizeData = data_.mid(0, 4);
	if (sizeData.size() < 4) return;
	auto size = qFromBigEndian<qint32>(sizeData.data());
	if (data_.size() < size + 4 )
		return;
	QByteArray data = data_.mid(4, size);
	data_.remove(0, size+4);

QByteArray dataSize(4, char(0));
	qint32 dsize = answerData.size();
	qToBigEndian(dsize, dataSize.data());
	socket_->write(dataSize);*/

PacketBuilder::PacketBuilder(QObject* parent)
	: QObject(parent)
{
}

qint64 PacketBuilder::write(const QByteArray& data, TcpCoreClient &client)
{
	QByteArray sizeba(4, 0);
	qint32 dsize = data.size();
	qToBigEndian(dsize, sizeba.data());
	//*((qint32*)sizeba.data()) = qint32(data.size());
	return client.write(sizeba.append(data));
}

ResDesc PacketBuilder::write(quint16 connectionId, const QByteArray& data, TcpCoreServer& server)
{
	QByteArray sizeba(4, char(0));
	auto dsize = quint32(data.size());//ba.mid(0,4).toHex().toInt(&ok, 16);
	//*reinterpret_cast<quint32*>(sizeba.data()) = size;
	qToBigEndian(dsize, sizeba.data());
	return server.write(connectionId, sizeba.append(data));
}

void PacketBuilder::onBytesReceived(const QByteArray& data, const ConnectionInfo& from)
{
	QByteArray& buffer = buffer_[from.connectionId];
	buffer.append(data);
	//quint32 basize = buffer.size() >=4 ? *reinterpret_cast<quint32*>(buffer.mid(0,4).data()) : 0;
	qint32 basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;

	while (basize > 0 && buffer.size() >= int(basize)+4)
	{
		QByteArray ba = buffer.mid(0, int(basize)+4);
		buffer.remove(0, int(basize)+4);
		DLOG("[PacketBuilder]" % tr(" получен пакет %1+4 байт от [%2]").arg(basize).arg(from.connectionId));
		emit packetReceived(ba.mid(4), from);
		basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;
	}
}

} // Ramio::
