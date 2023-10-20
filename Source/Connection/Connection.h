/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ramio.h"
#include <QtCore/QString>

namespace Ramio {

enum class ConnectionStates : quint8
{
	Initial = 0,
	Connecting,
	Connected,
	Logining,
	Logined,
	Error,
	Disconected
};

QString connectionStateName(ConnectionStates state);

struct ConnectionParameters
{
	QString login;
	QString password;
	QString host;
	quint16 port = 0;

	void loadFromConfig(const QString& targetName = TARGET_NAME);
	void saveToConfig(const QString& targetName = TARGET_NAME) const;

	static ConnectionParameters createFromConfig(const QString& targetName = TARGET_NAME);
};

struct ConnectionState
{
	ConnectionParameters parameters;
	ConnectionStates state = ConnectionStates::Initial;
	QString stateName() const {return connectionStateName(state);}
};

} // Ramio::
