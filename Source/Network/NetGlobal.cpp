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

#include "NetGlobal.h"
// Qt5
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpSocket>

namespace Ramio {

QString socketStateName(QAbstractSocket::SocketState state)
{
	if (state == QAbstractSocket::UnconnectedState) return "The socket is not connected.";
	if (state == QAbstractSocket::HostLookupState) return "The socket is performing a host name lookup.";
	if (state == QAbstractSocket::ConnectingState) return "The socket has started establishing a connection.";
	if (state == QAbstractSocket::ConnectedState) return "A connection is established.";
	if (state == QAbstractSocket::BoundState) return "The socket is bound to an address and port.";
	if (state == QAbstractSocket::ClosingState) return "The socket is about to close (data may still be waiting to be written).";
	if (state == QAbstractSocket::ListeningState) return "For internal use only.";
	return QString();
}

QStringList localIPv4List()
{
	QStringList result;
	Q_FOREACH (const QHostAddress& ha, QNetworkInterface::allAddresses())
		if (ha.isInSubnet(QHostAddress::LocalHost, 24) && ha.protocol() == QAbstractSocket::IPv4Protocol)
			result.append(ha.toString());
	return result;
}

ConnectionInfo::ConnectionInfo(quint16 p_connectionId, const QTcpSocket& p_socket)
	: address(std::move(p_socket.peerAddress())),
	  port(p_socket.peerPort()),
	  connectionId(p_connectionId)
{
}

} // Ramio::
