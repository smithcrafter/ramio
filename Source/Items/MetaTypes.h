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

#pragma once

#include <ramio.h>
#include <Global/QtCoreDeclaration.h>
#include <QtCore/QList>
#include <string>

#define DB_NULL 0
#define UNUSEDID 0

#define RMBool bool
#define RMChar char
#define RMShort short int
#define RMUShort unsigned short int
#define RMInt int
#define RMUInt unsigned int
#define RMLong long long
#define RMULong unsigned long long
#define RMFloat float
#define RMDouble double

#define RMStdString std::string

#define RMString QString
#define RMUuid QUuid
#define RMTime QTime
#define RMDate QDate
#define RMDateTime QDateTime
#define RMByteArray QByteArray
#define RMStringList QStringList

#define RMByte quint8
#define RMMoney float

#define RMPKey qint64
#define RMType short int
#define RMState short int
#define RMFlags unsigned int
#define RMPKeyList QList<RMPKey>
#define RMTypeList QList<RMType>

namespace Ramio {
namespace Meta {

enum class Type : quint8
{
	Unset = 0,
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
	StringList,
//
	Byte,
	Money,
// Self
	PKey,
	Type,
	State,
	Flags,
	RecordPrtList,
	PKeyList,
	TypeList
};

QString typeName(Type type);

// experimental

template<Type rtype> struct RMetaType;

template<> struct RMetaType<Type::Bool> {using type = RMBool;};
template<> struct RMetaType<Type::Char> {using type = RMChar;};
template<> struct RMetaType<Type::Short> {using type = RMShort;};
template<> struct RMetaType<Type::UShort> {using type = RMUShort;};
template<> struct RMetaType<Type::Int> {using type = RMInt;};
template<> struct RMetaType<Type::UInt> {using type = RMUInt;};
template<> struct RMetaType<Type::Long> {using type = RMLong;};
template<> struct RMetaType<Type::ULong> {using type = RMULong;};
template<> struct RMetaType<Type::Float> {using type = RMFloat;};
template<> struct RMetaType<Type::Double> {using type = RMDouble;};
template<> struct RMetaType<Type::StdString> {using type = RMStdString;};
template<> struct RMetaType<Type::String> {using type = RMString;};
template<> struct RMetaType<Type::Uuid> {using type = RMUuid;};
template<> struct RMetaType<Type::Time> {using type = RMTime;};
template<> struct RMetaType<Type::Date> {using type = RMDate;};
template<> struct RMetaType<Type::DateTime> {using type = RMDateTime;};
template<> struct RMetaType<Type::ByteArray> {using type = RMByteArray;};
template<> struct RMetaType<Type::StringList> {using type = RMStringList;};
template<> struct RMetaType<Type::Byte> {using type = RMByte;};
template<> struct RMetaType<Type::Money> {using type = RMMoney;};
template<> struct RMetaType<Type::PKey> {using type = RMPKey;};
template<> struct RMetaType<Type::Type> {using type = RMType;};
template<> struct RMetaType<Type::State> {using type = RMState;};
template<> struct RMetaType<Type::Flags> {using type = RMFlags;};
template<> struct RMetaType<Type::PKeyList> {using type = RMPKeyList;};
template<> struct RMetaType<Type::TypeList> {using type = RMTypeList;};


template<Type rtype> QString valueToString(const typename RMetaType<rtype>::type& value);

template<> QString valueToString<Type::Bool>(const RMBool& value);
template<> QString valueToString<Type::Char>(const RMChar& value);
template<> QString valueToString<Type::Short>(const RMShort& value);
template<> QString valueToString<Type::UShort>(const RMUShort& value);
template<> QString valueToString<Type::Int>(const RMInt& value);
template<> QString valueToString<Type::UInt>(const RMUInt& value);
template<> QString valueToString<Type::Long>(const RMLong& value);
template<> QString valueToString<Type::ULong>(const RMULong& value);
template<> QString valueToString<Type::Float>(const RMFloat& value);
template<> QString valueToString<Type::Double>(const RMDouble& value);
template<> QString valueToString<Type::StdString>(const RMStdString& value);
template<> QString valueToString<Type::String>(const RMString& value);
template<> QString valueToString<Type::Uuid>(const RMUuid& value);
template<> QString valueToString<Type::Time>(const RMTime& value);
template<> QString valueToString<Type::Date>(const RMDate& value);
template<> QString valueToString<Type::DateTime>(const RMDateTime& value);
template<> QString valueToString<Type::ByteArray>(const RMByteArray& value);
template<> QString valueToString<Type::Byte>(const RMByte& value);
template<> QString valueToString<Type::Money>(const RMMoney& value);
template<> QString valueToString<Type::PKey>(const RMPKey& value);
template<> QString valueToString<Type::Type>(const RMType& value);
template<> QString valueToString<Type::State>(const RMState& value);
template<> QString valueToString<Type::Flags>(const RMFlags& value);

QString valueToString(Type type, const void* value);

} // Meta::
} // Ramio::

#define moneyToString(value) Ramio::Meta::valueToString<Ramio::Meta::Type::Money>(value)
