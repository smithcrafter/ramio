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

#pragma once

#include <ramio.h>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QSslConfiguration>

namespace Ramio {

class SslTcpServer : public QTcpServer
{
public:
	SslTcpServer(QObject* parent = Q_NULLPTR);

	void setConfiguration(const QSslConfiguration& conf) {configuration_ = conf;}

	bool hasPendingConnections() const Q_DECL_OVERRIDE {return !pendingConnections_.isEmpty();}
	QTcpSocket* nextPendingConnection() Q_DECL_OVERRIDE {return pendingConnections_.isEmpty() ? Q_NULLPTR : pendingConnections_.takeFirst();}

protected:
	void incomingConnection(qintptr handle) Q_DECL_OVERRIDE;

	void onEncrypted();
	void onSslErrors(const QList<QSslError>& errors);
	void onPeerVerifyError(const QSslError& error);

private:
	QList<QSslSocket*> pendingConnections_;
	QSslConfiguration configuration_;
};

} // Ramio::
