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
#include <Global/QtCoreDeclaration.h>


#define DB_NULL 0
#define UNUSEDID 0

#define RMetaPKey quint64
#define RMetaBool bool
#define RMetaChar char
#define RMetaShort short int
#define RMetaUShort unsigned short int
#define RMetaInt int
#define RMetaUInt unsigned int
#define RMetaLong long long
#define RMetaULong unsigned long long
#define RMetaFloat float
#define RMetaDouble double
#define RMetaString QString
#define RMetaUuid QUuid
#define RMetaTime QTime
#define RMetaDate QDate
#define RMetaDateTime QDateTime
#define RMetaByteArray QByteArray
#define RMetaByte quint8
#define RMetaMoney float

namespace Ramio {
namespace Meta {

enum class Type
{
	Unset = 0,
	PKey,
// C++
	Bool,
	Char, // TODO
	Short,
	UShort,
	Int,
	UInt,
	Long,
	ULong,
	Float,
	Double,
// Std
	StdString, // TODO
// Qt
	String,
	Uuid,
	Time,
	Date,
	DateTime,
	ByteArray, // TODO
// Self
	Byte,
	Money
};

template<typename TYPE, Type rtype>
QString typeToString(const TYPE& t);

// experimental
template<> QString typeToString<RMetaPKey, Type::PKey>(const RMetaPKey& value);

} // Meta::
} // Ramio::
