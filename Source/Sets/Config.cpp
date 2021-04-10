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

#include "Config.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QStringBuilder>
#ifdef Q_OS_ANDROID
#include <QStandardPaths>
#endif

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
		settings_->setValue(key, value);
		settings_->sync();
		return true;
	}
	return false;
}

QString Config::filename() const
{
#ifdef Q_OS_ANDROID
	auto list = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
	if (!list.isEmpty())
		return list.first();
#endif
	return qApp->applicationDirPath() % QStringLiteral("/Config/") % targetName_ % QStringLiteral(".ini");
}

Config::Config(QString targetName)
	: targetName_(std::move(targetName))
{
	QDir().mkpath(QFileInfo(filename()).dir().path());
	settings_.reset(new QSettings(filename(), QSettings::IniFormat));
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

Config& changeConfig(const QString& targetName)
{
	return const_cast<Config&>(config(targetName));
}

} // Ramio::
