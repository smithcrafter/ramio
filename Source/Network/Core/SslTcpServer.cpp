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

#include "SslTcpServer.h"
#include <Log/Log.h>

namespace Ramio {

SslTcpServer::SslTcpServer(QObject* parent)
	: QTcpServer(parent)
{
}

void SslTcpServer::incomingConnection(qintptr handle)
{
	auto* socket = new QSslSocket(this);
	if (!socket ->setSocketDescriptor(handle))
	{
		delete socket;
		return;
	}

	connect(socket, &QSslSocket::encrypted, this, &SslTcpServer::onEncrypted);
	connect(socket, static_cast<void (QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors), this, &SslTcpServer::onSslErrors);
	connect(socket, &QSslSocket::peerVerifyError, this, &SslTcpServer::onPeerVerifyError);

	socket->setSslConfiguration(configuration_);
	socket->startServerEncryption();
}

void SslTcpServer::onEncrypted()
{
	auto* socket = static_cast<QSslSocket*>(sender());
	pendingConnections_.append(socket);
	emit newConnection();
}

void SslTcpServer::onSslErrors(const QList<QSslError>& errors)
{
	if (auto* socket = static_cast<QSslSocket*>(sender()))
		for (const auto & error : errors)
			DLOG(QStringLiteral("%1 SslError[%2]: %3").arg(socket->peerAddress().toString()).arg(error.error()).arg(error.errorString()));
}

void SslTcpServer::onPeerVerifyError(const QSslError& error)
{
	if (auto* socket = static_cast<QSslSocket*>(sender()))
		DLOG(QStringLiteral("%1 PeerVerifyError[%2]: %3").arg(socket->peerAddress().toString()).arg(error.error()).arg(error.errorString()));
}

} // Ramio::
