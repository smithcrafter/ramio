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

#include "MetaTypes.h"

namespace Ramio {
namespace Meta {

template<>
QString typeToString<RMetaPKey>(const RMetaPKey& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaInt>(const RMetaInt& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaUuid>(const RMetaUuid& value)
{
	return value.toString();
}

template<>
QString typeToString<RMetaString>(const RMetaString& value)
{
	return value;
}

template<>
QString typeToString<RMetaDouble>(const RMetaDouble& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaTime>(const RMetaTime& value)
{
	return value.toString(Qt::ISODate);
}

template<>
QString typeToString<RMetaDate>(const RMetaDate& value)
{
	return value.toString(Qt::ISODate);
}

template<>
QString typeToString<RMetaDateTime>(const RMetaDateTime& value)
{
	return value.toString(Qt::ISODate);
}

} // Meta::
} // Ramio::
