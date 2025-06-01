/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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

#include "MetaTypes.h"
#include <QtCore/QUuid>

// for cast -> auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
#define CAST_FIELDREL_BASE(datarel, type, diff, constancy) \
	(*reinterpret_cast<constancy type*>(reinterpret_cast<constancy std::byte*>(&datarel)+diff))
#define CAST_DATAREL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data, type, pr.diff, )
#define CAST_CONST_DATAREL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data, type, pr.diff, const)

namespace Ramio {

struct RAMIO_LIB_EXPORT Data
{
	template<typename FIELDTYPE>
	FIELDTYPE& field(ptrdiff_t diff) {return CAST_FIELDREL_BASE(*this, FIELDTYPE, diff,);}

	template<typename FIELDTYPE>
	const FIELDTYPE& field(ptrdiff_t diff) const {return CAST_FIELDREL_BASE(*this, FIELDTYPE, diff, const);}
};

struct RAMIO_LIB_EXPORT ItemData : Data
{
	RMPKey id = 0;

	QString valueToString(Meta::Type type, ptrdiff_t diff) const {return Meta::valueToString(type, &field<RMByte>(diff));}
};

struct RAMIO_LIB_EXPORT BaseItemData : ItemData
{
	BaseItemData() = default;
	BaseItemData(const BaseItemData&) = default;
	BaseItemData(BaseItemData&&) = default;
	BaseItemData& operator = (const BaseItemData&) = default;
	BaseItemData& operator = (BaseItemData&&) = default;
	virtual ~BaseItemData() = default;
};

using BaseItemDataPtr = BaseItemData*;

} // Ramio::
