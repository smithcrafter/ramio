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

#pragma once

#include <ramio.h>
#include <Global/QtCoreDeclaration.h>
#ifdef Q_OS_WIN
#include <string>
#endif

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
#define RMetaStdString std::string
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

enum class Type : quint8
{
	Unset = 0,
	PKey,
// C++
	Bool,
	Char,
	Short,
	UShort,
	Int,
	UInt,
	Long,
	ULong,
	Float,
	Double,
// Std
	StdString,
// Qt
	String,
	Uuid,
	Time,
	Date,
	DateTime,
	ByteArray,
// Self
	Byte,
	Money
};

QString typeName(Type type);

// experimental

template<Type rtype> struct RMetaType;
template<> struct RMetaType<Type::PKey> {using type = RMetaPKey;};
template<> struct RMetaType<Type::Bool> {using type = RMetaBool;};
template<> struct RMetaType<Type::Char> {using type = RMetaChar;};
template<> struct RMetaType<Type::Short> {using type = RMetaShort;};
template<> struct RMetaType<Type::UShort> {using type = RMetaUShort;};
template<> struct RMetaType<Type::Int> {using type = RMetaInt;};
template<> struct RMetaType<Type::UInt> {using type = RMetaUInt;};
template<> struct RMetaType<Type::Long> {using type = RMetaLong;};
template<> struct RMetaType<Type::ULong> {using type = RMetaULong;};
template<> struct RMetaType<Type::Float> {using type = RMetaFloat;};
template<> struct RMetaType<Type::Double> {using type = RMetaDouble;};
template<> struct RMetaType<Type::StdString> {using type = RMetaStdString;};
template<> struct RMetaType<Type::String> {using type = RMetaString;};
template<> struct RMetaType<Type::Uuid> {using type = RMetaUuid;};
template<> struct RMetaType<Type::Time> {using type = RMetaTime;};
template<> struct RMetaType<Type::Date> {using type = RMetaDate;};
template<> struct RMetaType<Type::DateTime> {using type = RMetaDateTime;};
template<> struct RMetaType<Type::ByteArray> {using type = RMetaByteArray;};
template<> struct RMetaType<Type::Byte> {using type = RMetaByte;};
template<> struct RMetaType<Type::Money> {using type = RMetaMoney;};

template<Type rtype> QString valueToString(const typename RMetaType<rtype>::type& value);
template<> QString valueToString<Type::PKey>(const RMetaPKey& value);
template<> QString valueToString<Type::Bool>(const RMetaBool& value);
template<> QString valueToString<Type::Char>(const RMetaChar& value);
template<> QString valueToString<Type::Short>(const RMetaShort& value);
template<> QString valueToString<Type::UShort>(const RMetaUShort& value);
template<> QString valueToString<Type::Int>(const RMetaInt& value);
template<> QString valueToString<Type::UInt>(const RMetaUInt& value);
template<> QString valueToString<Type::Long>(const RMetaLong& value);
template<> QString valueToString<Type::ULong>(const RMetaULong& value);
template<> QString valueToString<Type::Float>(const RMetaFloat& value);
template<> QString valueToString<Type::Double>(const RMetaDouble& value);
template<> QString valueToString<Type::StdString>(const RMetaStdString& value);
template<> QString valueToString<Type::String>(const RMetaString& value);
template<> QString valueToString<Type::Uuid>(const RMetaUuid& value);
template<> QString valueToString<Type::Time>(const RMetaTime& value);
template<> QString valueToString<Type::Date>(const RMetaDate& value);
template<> QString valueToString<Type::DateTime>(const RMetaDateTime& value);
template<> QString valueToString<Type::ByteArray>(const RMetaByteArray& value);
template<> QString valueToString<Type::Byte>(const RMetaByte& value);
template<> QString valueToString<Type::Money>(const RMetaMoney& value);

} // Meta::
} // Ramio::
