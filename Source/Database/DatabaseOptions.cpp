/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "DatabaseOptions.h"

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

} // Ramio::
