/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <QtCore/QObject>
#include "Protocol.h"

namespace Ramio {

struct ConnectionInfo;

class RAMIO_LIB_EXPORT ProtocolOperator : public QObject
{
	Q_OBJECT
public:
	ProtocolOperator(QObject* parent = Q_NULLPTR);

public slots:
	void onPacketReceived(const QByteArray& data, const ConnectionInfo& from);

signals:
	void queryReceived(Proto::Queries query, const Proto::QueryPacket& packet, const ConnectionInfo& from);
	void answerReceived(Proto::Queries query, const Proto::AnswerPacket& packet,
						const Proto::XmlDocument& doc, const ConnectionInfo& from);
	void eventReceived(Proto::Events event, const Proto::EventPacket& packet,
						const Proto::XmlDocument& doc, const ConnectionInfo& from);
};

} // Ramio::
