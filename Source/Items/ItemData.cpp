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

#include "ItemData.h"
// Qt5
#include <QtCore/QObject>
#include <QtCore/QDateTime>

namespace Ramio {

bool less(Meta::Type fieldtype, const ItemData& left, const ItemData& right, ptrdiff_t diff)
{
	switch (fieldtype) {
		case Ramio::Meta::Type::PKey: return Ramio::less<RMetaPKey>(left, right, diff);
		case Ramio::Meta::Type::Bool: return Ramio::less<RMetaBool>(left, right, diff);
		case Ramio::Meta::Type::Char: return Ramio::less<RMetaChar>(left, right, diff);
		case Ramio::Meta::Type::Short: return Ramio::less<RMetaShort>(left, right, diff);
		case Ramio::Meta::Type::UShort: return Ramio::less<RMetaUShort>(left, right, diff);
		case Ramio::Meta::Type::Int: return Ramio::less<RMetaInt>(left, right, diff);
		case Ramio::Meta::Type::UInt: return Ramio::less<RMetaUInt>(left, right, diff);
		case Ramio::Meta::Type::Long: return Ramio::less<RMetaLong>(left, right, diff);
		case Ramio::Meta::Type::ULong: return Ramio::less<RMetaULong>(left, right, diff);
		case Ramio::Meta::Type::Float: return Ramio::less<RMetaFloat>(left, right, diff);
		case Ramio::Meta::Type::Double: return Ramio::less<RMetaDouble>(left, right, diff);
		case Ramio::Meta::Type::String: return Ramio::less<RMetaString>(left, right, diff);
		case Ramio::Meta::Type::Uuid: return Ramio::less<RMetaUuid>(left, right, diff);
		case Ramio::Meta::Type::Date: return Ramio::less<RMetaDate>(left, right, diff);
		case Ramio::Meta::Type::Time: return Ramio::less<RMetaTime>(left, right, diff);
		case Ramio::Meta::Type::DateTime: return Ramio::less<RMetaDateTime>(left, right, diff);
		case Ramio::Meta::Type::Byte: return Ramio::less<RMetaByte>(left, right, diff);
		case Ramio::Meta::Type::Money: return Ramio::less<RMetaMoney>(left, right, diff);
		default: return false;
	}
}

} // Ramio::
