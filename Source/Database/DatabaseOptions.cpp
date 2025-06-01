/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "DatabaseOptions.h"
#include <ramio/settings/config.h>

namespace Ramio {

const QString SQLite_BDType = QStringLiteral("QSQLITE");
const QString PostgresSQL_BDType = QStringLiteral("QPSQL");
const QString MySQL_BDType = QStringLiteral("QMYSQL");


const QString& qtDatabaseName(SupportedDatabaseType type)
{
	switch (type)
	{
		case SupportedDatabaseType::SQLite : return SQLite_BDType;
		case SupportedDatabaseType::PostgreSQL : return PostgresSQL_BDType;
		case SupportedDatabaseType::MySQL : return MySQL_BDType;
		default: return emptyString;
	}
}

void DatabaseConfig::loadFromConfig(const QString& section, const QString& targetName)
{
    dbname = config(targetName).value(section+"/Name");
    username = config(targetName).value(section+"/Username");
    password = config(targetName).value(section+"/Password");
    host = config(targetName).value(section+"/Host");
    port = config(targetName).value(section+"/Port").toUShort();
}

void DatabaseConfig::saveToConfig(const QString& section, const QString& targetName) const
{
    changeConfig(targetName).setValue(section+"/Name", dbname);
    changeConfig(targetName).setValue(section+"/Username", username);
    changeConfig(targetName).setValue(section+"/Password", password);
    changeConfig(targetName).setValue(section+"/Host", host);
    changeConfig(targetName).setValue(section+"/Port", port);
}

DatabaseConfig DatabaseConfig::createFromConfig(const QString& section, const QString& targetName)
{
    DatabaseConfig config;
    config.loadFromConfig(section, targetName);
    return config;
}

} // Ramio::
