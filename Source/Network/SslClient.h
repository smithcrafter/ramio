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

#pragma once

#include "Core/TcpCoreClient.h"
#include <QSslError>
class QSslSocket;

namespace Ramio {

class RAMIO_LIB_EXPORT SslClient : public TcpCoreClient
{
	Q_OBJECT
public:
	SslClient(const QHostAddress& address = QHostAddress::AnyIPv4, quint16 port = 0, QObject* parent = Q_NULLPTR);
	~SslClient() Q_DECL_OVERRIDE;

	void connectToHostEncripted(const QString &hostName, quint16 port);

signals:
	void encrypted();

private:
	void onSslErrors(const QList<QSslError>& errors);

private:
	QSslSocket* socket_;
};

} // Ramio::
