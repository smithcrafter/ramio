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

#include "SslClient.h"
#include <Log/Log.h>
// Qt5
#include <QtNetwork/QSslSocket>

namespace Ramio {

SslClient::SslClient(const QHostAddress& address, quint16 port, QObject* parent)
	: TcpCoreClient(*(socket_ = new QSslSocket(parent)), address, port, parent)
{
	socket_->setParent(this);

	//connect(socket_, &QSslSocket::connected, socket_, &QSslSocket::startClientEncryption);
	connect(socket_, &QSslSocket::encrypted, this, &SslClient::encrypted);
	connect(socket_, static_cast<void (QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors), this, &SslClient::onSslErrors);
}

SslClient::~SslClient()
{

}

void SslClient::connectToHostEncripted(const QString& hostName, quint16 port)
{
	isConnecting_ = true;
	socket_->connectToHostEncrypted(hostName, port);
}

void SslClient::onSslErrors(const QList<QSslError>& errors)
{
	for(const QSslError& er: errors)
		WLOG(er.errorString());
	socket_->ignoreSslErrors();
}

} // Ramio::
