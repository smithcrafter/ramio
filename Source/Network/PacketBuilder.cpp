/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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
#include <zstd.h>

namespace Ramio {

PacketBuilder::PacketBuilder(PacketBuilderOptions options, QObject* parent)
	: QObject(parent),
	  options_(std::move(options))
{
}

PacketBuilder::~PacketBuilder()
{
}

qint64 PacketBuilder::write(const QByteArray& data, TcpCoreClient& client)
{
	QByteArray sizeba(4, char(0));
	qint32 dsize = data.size();
	if (options_.compress)
	{
		QByteArray cdata;
		cdata.resize(data.size()*2);
		size_t size = ZSTD_compress(cdata.data(), cdata.size(), data.data(), data.size(), 19);
		if (ZSTD_isError(size))
		{
			ELOG(QString("[PacketBuilder] write ZSTD_isError %1 %2 data.size=%3").arg(size).arg(ZSTD_getErrorName(size)).arg(data.size()));
			return -1;
		}
		dsize = size;
		qToBigEndian(dsize, sizeba.data());
		sizeba.append(cdata.data(), dsize);
		if (plog_)
			PLOG("[PacketBuilder]" % tr(" отправляем пакет %1[%2]+4 байт").arg(dsize).arg(data.size()));
	}
	else
	{
		qToBigEndian(dsize, sizeba.data());
		sizeba.append(data);
		if (plog_)
			PLOG("[PacketBuilder]" % tr(" отправляем пакет %1+4 байт").arg(dsize));
	}

	if (dlog_)
		qDebug().noquote().nospace()<<RC_TERM_GRAY(data);
	return client.write(sizeba);
}

ResDesc PacketBuilder::write(quint16 connectionId, const QByteArray& data, TcpCoreServer& server)
{
	QByteArray sizeba(4, char(0));
	qint32 dsize = data.size();
	if (options_.compress)
	{
		QByteArray cdata;
		cdata.resize(data.size()*2);
		size_t size = ZSTD_compress(cdata.data(), cdata.size(), data.data(), data.size(), 19);
		if (ZSTD_isError(size))
		{
			ELOG(QString("[PacketBuilder] write ZSTD_isError %1 %2 data.size=%3").arg(size).arg(ZSTD_getErrorName(size)).arg(data.size()));
			return ResDesc(RD_DATA_ERROR);
		}
		dsize = size;
		qToBigEndian(dsize, sizeba.data());
		sizeba.append(cdata.data(), dsize);
		if (plog_)
			PLOG("[PacketBuilder]" % tr(" отправляем пакет %1[%2]+4 байт для [%3]").arg(dsize).arg(data.size()).arg(connectionId));
	}
	else
	{
		qToBigEndian(dsize, sizeba.data());
		sizeba.append(data);
		if (plog_)
			PLOG("[PacketBuilder]" % tr(" отправляем пакет %1+4 байт для [%2]").arg(dsize).arg(connectionId));
	}

	if (dlog_)
		qDebug().noquote().nospace()<<RC_TERM_GRAY(data);
	return server.write(connectionId, sizeba);
}

void PacketBuilder::onBytesReceived(const QByteArray& data, const ConnectionInfo& from)
{
	QByteArray& buffer = buffer_[from.connectionId];
	buffer.append(data);
	int basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;

	while (basize > 0 && buffer.size() >= (basize+4))
	{
		QByteArray packetData = buffer.mid(4, basize);
		buffer.remove(0, int(basize)+4);
		if (plog_)
			PLOG("[PacketBuilder]" % tr(" получен пакет %1+4 байт от %2:%3[%4]")
				 .arg(basize).arg(from.address.toString()).arg(from.port).arg(from.connectionId));
		if (options_.compress)
		{
			QByteArray cdata;
			cdata.resize(10*basize);
			size_t size = ZSTD_decompress(cdata.data(), cdata.size(), packetData.data(), packetData.size());
			if (ZSTD_isError(size))
			{
				ELOG(QString("[PacketBuilder] ZSTD_isError %1 %2 buffer.size=%3").arg(size).arg(ZSTD_getErrorName(size)).arg(basize));
				packetData.clear();
			}
			else
			{
				if (plog_)
					PLOG("[PacketBuilder]" % tr(" %1 распакован в %2").arg(packetData.size()).arg(size));
				packetData = QByteArray(cdata.data(), size);
			}
		}

		if (dlog_)
			qDebug().noquote().nospace()<<RC_TERM_GRAY(packetData);
		emit packetReceived(packetData, from);
		basize = buffer.size() >= 4 ? qFromBigEndian<qint32>(buffer.mid(0, 4).data()) : 0;
	}
}

} // Ramio::
