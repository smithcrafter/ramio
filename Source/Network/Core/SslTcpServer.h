#pragma once

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
