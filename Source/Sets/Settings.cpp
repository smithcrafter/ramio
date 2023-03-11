/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "Settings.h"

namespace Ramio {

QVariant Settings::get(const QString& key, const QVariant& defaultValue) const
{
	if (settings_)
		return settings_->value(key, defaultValue);
	return defaultValue;
}

bool Settings::set(const QString& key, const QString& value, bool sync)
{
	if (!settings_)
		return false;
	settings_->setValue(key, value);
	if (sync)
		settings_->sync();
	return true;
}

Settings::Settings()
{
}

Settings::~Settings()
{
	if (settings_)
		settings_->sync();
}

void Settings::init(QString comp, QString app)
{
	comp_ = comp;
	app_ = app;
	settings_.reset(new QSettings(comp, app));
}

Settings Settings::self;

} // Ramio::
