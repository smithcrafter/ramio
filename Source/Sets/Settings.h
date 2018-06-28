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

#pragma once

#include <QtCore/QSettings>

namespace Ramio {

class Settings : public QObject
{
	friend int main(int argc, char *argv[]);
public:
	static Settings& instance() { return self; }

	QVariant get(const QString& key, const QVariant& defaultValue = QVariant()) const;
	bool set(const QString& key, const QString& value, bool sync = false);

private:
	Settings();
	~Settings() Q_DECL_OVERRIDE;

	void init(QString comp, QString app);

public:
	QString comp_; QString app_;

private:
	QScopedPointer<QSettings> settings_;
	static Settings self;
};

#define Sets Settings::instance()

} // Ramio::
