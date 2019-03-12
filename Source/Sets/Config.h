/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
#include <QtCore/QSettings>

namespace Ramio {

class DLL_EXPORT Config
{
	friend const Config& config(const QString& targetName);
public:
	QString value(const QString& key) const;
	qint32 valueInt32(const QString& key) const {return value(key).toInt();}

	bool setValue(const QString& key, const QString& value);
	bool setValue(const QString& key, qint32 value) {return setValue(key, QString::number(value));}

private:
	Config(const QString& targetName);
	~Config();

	static Config& config(const QString& targetName);

private:
	QScopedPointer<QSettings> settings_;

};

DLL_EXPORT const Config& config(const QString& targetName = TARGET_NAME);

} // Ramio::
