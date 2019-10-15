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

#include "MetaTypes.h"
#include <QtCore/QUuid>

// for cast -> auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
#define CAST_FIELDREL_BASE(datarel, type, diff, needconst) \
	(*reinterpret_cast<needconst type*>(reinterpret_cast<needconst std::byte*>(&datarel)+diff))
#define CAST_DATAREL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data, type, pr.dif, )
#define CAST_CONST_DATAREL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data, type, pr.dif, const)

namespace Ramio {

/**
 * @brief The ItemData struct
 */
struct ItemData
{
	RMetaUuid uuid;
	RMetaPKey id = 0;
	RMetaInt type = 0;

	template<typename FIELDTYPE>
	FIELDTYPE& field(ptrdiff_t diff) {return CAST_FIELDREL_BASE(*this, FIELDTYPE, diff,);}

	template<typename FIELDTYPE>
	const FIELDTYPE& field(ptrdiff_t diff) const {return CAST_FIELDREL_BASE(*this, FIELDTYPE, diff, const);}

	virtual ~ItemData() = default;
};

} // Ramio::
