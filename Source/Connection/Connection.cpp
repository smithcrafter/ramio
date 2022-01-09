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

#include "Connection.h"
#include <QtCore/QObject>
#include "../Sets/Config.h"

namespace Ramio {

QString connectionStateName(ConnectionStates state)
{
	switch (state) {
		case ConnectionStates::Initial: return QObject::tr("Исходное");
		case ConnectionStates::Connecting: return QObject::tr("Подключение");
		case ConnectionStates::Connected: return QObject::tr("Подключен");
		case ConnectionStates::Logining: return QObject::tr("Авторизация");
		case ConnectionStates::Logined: return QObject::tr("Авторизован");
		case ConnectionStates::Error: return QObject::tr("Ошибка");
		case ConnectionStates::Disconected: return QObject::tr("Разрыв");
	}
	return QObject::tr("Не определён");
}

void ConnectionParameters::loadFromConfig(const QString& targetName)
{
	login = config(targetName).value("Connection/Login");
	password = config(targetName).value("Connection/Password");
	host = config(targetName).value("Connection/Host");
	port = config(targetName).value("Connection/Port").toUShort();
}

void ConnectionParameters::saveToConfig(const QString& targetName) const
{
	changeConfig(targetName).setValue("Connection/Login", login);
	changeConfig(targetName).setValue("Connection/Password", password);
	changeConfig(targetName).setValue("Connection/Host", host);
	changeConfig(targetName).setValue("Connection/Port", port);
}

ConnectionParameters ConnectionParameters::createFromConfig(const QString& targetName)
{
	ConnectionParameters params;
	params.loadFromConfig(targetName);
	return params;
}

} // Ramio::
