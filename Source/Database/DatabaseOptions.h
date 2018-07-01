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

#include <Global/ResDesc.h>

namespace Ramio {

namespace Meta {struct Description;}
class MetaTable;
class MetaItemData;
class AbstractMetaSet;

struct DataBaseConfig
{
	QString userName;
	QString password;
	QString databaseName;
	QString host;
	quint16 port;
};

enum class SupportedDatabaseType
{
	PostgreSQL,
	SQLite
};

const QString& qtDatabaseName(SupportedDatabaseType type);

} // Ramio::

#define SQL(text) QStringLiteral(text)
