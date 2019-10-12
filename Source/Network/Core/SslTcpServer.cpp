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
