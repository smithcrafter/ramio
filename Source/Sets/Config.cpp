/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

#include "Config.h"
#include <QtCore/QCoreApplication>
#include <QStringBuilder>

namespace Ramio {

QString Config::value(const QString& key) const
{
	if (settings_)
		return settings_->value(key).toString();
	return QString();
}

bool Config::setValue(const QString& key, const QString& value)
{
	if (settings_)
	{
		settings_->value(key, value);
		settings_->sync();
		return true;
	}
	return false;
}

Config::Config(const QString& targetName)
{
	QString name = qApp->applicationDirPath() % QStringLiteral("/Config/") % targetName % QStringLiteral(".ini");
	settings_.reset(new QSettings(name, QSettings::IniFormat));
}

Config::~Config()
{
	settings_->sync();
}

Config& Config::config(const QString& targetName)
{
	static Config result(targetName);
	return result;
}

const Config& config(const QString& targetName)
{
	return Config::config(targetName);
}

} // Ramio::
