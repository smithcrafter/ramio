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

#include "MetaTypes.h"
#include <QtCore/QUuid>
#include <QtCore/QDateTime>
#include <QStringBuilder>

namespace Ramio {
namespace Meta {

QString typeName(Type type)
{
	switch (type) {
		case Type::Unset : return "Unset";
		case Type::Bool : return "Bool";
		case Type::Char : return "Char";
		case Type::Short : return "Short";
		case Type::UShort : return "UShort";
		case Type::Int : return "Int";
		case Type::UInt : return "UInt";
		case Type::Long : return "Long";
		case Type::ULong : return "ULong";
		case Type::Float : return "Float";
		case Type::Double : return "Double";
		case Type::StdString : return "StdString";
		case Type::String : return "String";
		case Type::StringList : return "StringList";
		case Type::Uuid : return "Uuid";
		case Type::Time : return "Time";
		case Type::Date : return "Date";
		case Type::DateTime : return "DateTime";
		case Type::ByteArray : return "ByteArray";
		case Type::Byte : return "Byte";
		case Type::Money : return "Money";
		case Type::PKey : return "PKey";
		case Type::Type : return "Type";
		case Type::State : return "State";
		case Type::Flags : return "Flags";
		case Type::RecordPrtList : return "RecordPrtList";
		case Type::PKeyList : return "PKeyList";
		case Type::TypeList : return "TypeList";
	}
	Q_ASSERT_X(0, "Ramio::Meta::typeName", qPrintable(QString("Type \"%1\" not supported").arg(quint8(type))));
	return emptyString;
}

template<> QString valueToString<Type::Bool>(const RMBool& value) { return value ? "true" : "false"; }
template<> QString valueToString<Type::Char>(const RMChar& value) { return QString(value); }
template<> QString valueToString<Type::Short>(const RMShort& value) { return QString::number(value); }
template<> QString valueToString<Type::UShort>(const RMUShort& value) { return QString::number(value); }
template<> QString valueToString<Type::Int>(const RMInt& value) { return QString::number(value); }
template<> QString valueToString<Type::UInt>(const RMUInt& value) { return QString::number(value); }
template<> QString valueToString<Type::Long>(const RMLong& value) { return QString::number(value); }
template<> QString valueToString<Type::ULong>(const RMULong& value) { return QString::number(value); }
template<> QString valueToString<Type::Float>(const RMFloat& value) { return QString::number(value); } // TODO precision
template<> QString valueToString<Type::Double>(const RMDouble& value) { return QString::number(value); } // TODO precision
template<> QString valueToString<Type::StdString>(const RMStdString& value)  { return QString::fromStdString(value); }
template<> QString valueToString<Type::String>(const RMString& value)  { return value; }
template<> QString valueToString<Type::Uuid>(const RMUuid& value)  { return value.toString(); }
template<> QString valueToString<Type::Time>(const RMTime& value) { return value.toString(Qt::ISODate); }
template<> QString valueToString<Type::Date>(const RMDate& value)  { return value.toString(Qt::ISODate); }
template<> QString valueToString<Type::DateTime>(const RMDateTime& value)  { return value.toString(Qt::ISODateWithMs); }
template<> QString valueToString<Type::ByteArray>(const RMByteArray& value)  { return QString(value.toHex()); }
template<> QString valueToString<Type::StringList>(const RMStringList& value)  { return "{" % value.join(",") % "}"; }
template<> QString valueToString<Type::Byte>(const RMByte& value) { return QString::number(value); }
template<> QString valueToString<Type::Money>(const RMMoney& value)  {
	return QString::number((value+(value > 0 ? 1 : -1)*0.000001), 'f', 2);}
template<> QString valueToString<Type::PKey>(const RMPKey& value) { return QString::number(value); }
template<> QString valueToString<Type::Type>(const RMType& value)  { return QString::number(value); }
template<> QString valueToString<Type::State>(const RMState& value)  { return QString::number(value); }
template<> QString valueToString<Type::Flags>(const RMFlags& value)  { return QString::number(value); }

#define V2STR_CASE(TYPE) \
	case Type::TYPE: return valueToString<Type::TYPE>(*static_cast<const RMetaType<Type::TYPE>::type*>(value));
QString valueToString(Type type, const void* value)
{
	switch (type) {
		V2STR_CASE(Bool)
		V2STR_CASE(Char)
		V2STR_CASE(Short)
		V2STR_CASE(UShort)
		V2STR_CASE(Int)
		V2STR_CASE(UInt)
		V2STR_CASE(Long)
		V2STR_CASE(ULong)
		V2STR_CASE(Float)
		V2STR_CASE(Double)
		V2STR_CASE(StdString)
		V2STR_CASE(String)
		V2STR_CASE(Uuid)
		V2STR_CASE(Time)
		V2STR_CASE(Date)
		V2STR_CASE(DateTime)
		V2STR_CASE(ByteArray)
		V2STR_CASE(StringList)
		V2STR_CASE(Byte)
		V2STR_CASE(Money)
		V2STR_CASE(PKey)
		V2STR_CASE(Type)
		V2STR_CASE(State)
		V2STR_CASE(Flags)
// TODO
		case Type::RecordPrtList:
		case Type::PKeyList:
		case Type::TypeList:
		case Type::Unset: return emptyString;
	}
	Q_ASSERT_X(0, "Ramio::Meta::valueToString", qPrintable(QString("Type \"%1\" not supported").arg(quint8(type))));
	return emptyString;
}

} // Meta::
} // Ramio::
