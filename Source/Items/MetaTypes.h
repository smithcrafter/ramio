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
#include <QtCore/QUuid>
#include <QtCore/QDateTime>

#define DB_NULL 0
#define UNUSEDID 0

#define RMetaPKey quint64
#define RMetaInt int
#define RMetaLong long long
#define RMetaUuid QUuid
#define RMetaString QString
#define RMetaDouble double
#define RMetaTime QTime
#define RMetaDate QDate
#define RMetaDateTime QDateTime
#define RMetaMoney double

namespace Ramio {
namespace Meta {

enum class Type
{
	Unset = 0,
	PKey,
	Int,
	Long,
	Double,
	Uuid,
	String,
	Time,
	Date,
	DateTime,
	Money
};

template<typename TYPE>
QString typeToString(const TYPE& t);


template<> QString typeToString<RMetaPKey>(const RMetaPKey& value);
template<> QString typeToString<RMetaInt>(const RMetaInt& value);
template<> QString typeToString<RMetaUuid>(const RMetaUuid& value);
template<> QString typeToString<RMetaString>(const RMetaString& value);
template<> QString typeToString<RMetaDouble>(const RMetaDouble& value);
template<> QString typeToString<RMetaTime>(const RMetaTime& value);
template<> QString typeToString<RMetaDate>(const RMetaDate& value);
template<> QString typeToString<RMetaDateTime>(const RMetaDateTime& value);

} // Meta::
} // Ramio::
