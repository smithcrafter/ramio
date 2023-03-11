/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <ramio/network/global.h>
#include <ramio/resdesc.h>

namespace Ramio {

struct RAMIO_LIB_EXPORT PacketBuilderOptions
{
	bool compress = false;
};

class RAMIO_LIB_EXPORT PacketBuilder : public QObject
{
	Q_OBJECT
public:
	PacketBuilder(PacketBuilderOptions options = PacketBuilderOptions(), QObject* parent = Q_NULLPTR);
	~PacketBuilder() Q_DECL_OVERRIDE;

	virtual qint64 write(const QByteArray& data, TcpCoreClient& client);
	virtual ResDesc write(quint16 connectionId, const QByteArray& data, TcpCoreServer& server);

	void setPlogOn() {plog_ = true;}
	void setDlogOn() {dlog_ = true;}

public slots:
	void onBytesReceived(const QByteArray& data, const ConnectionInfo& from);

signals:
	void packetReceived(const QByteArray& data, const ConnectionInfo& from);

private:
	PacketBuilderOptions options_;
	QMap<quint32, QByteArray> buffer_;
	bool plog_ = false;
	bool dlog_ = false;
};

} // Ramio::
