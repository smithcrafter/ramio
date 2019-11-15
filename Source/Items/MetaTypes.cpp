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

#include "MetaTypes.h"
#include <QtCore/QUuid>
#include <QtCore/QDateTime>

namespace Ramio {
namespace Meta {

QString typeName(Type type)
{
	switch (type) {
		case Type::Unset : return "Unset";
		case Type::PKey : return "PKey";
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
		case Type::Uuid : return "Uuid";
		case Type::Time : return "Time";
		case Type::Date : return "Date";
		case Type::DateTime : return "DateTime";
		case Type::ByteArray : return "ByteArray";
		case Type::Byte : return "Byte";
		case Type::Money : return "Money";
	}
	Q_ASSERT_X(0, "Ramio::Meta::typeName", qPrintable(QString("Type \"%1\" not supported").arg(quint8(type))));
	return emptyString;
}

template<>
QString typeToString<RMetaPKey, Type::PKey>(const RMetaPKey& value)
{
	return QString::number(value);
}

} // Meta::
} // Ramio::
