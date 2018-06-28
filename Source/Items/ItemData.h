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

#pragma once

#include <ramio.h>
#include <QtCore/QUuid>
#include <QtCore/QDateTime>
#include <QtCore/QSet>

#define RMetaPKey quint64
#define RMetaInt int
#define RMetaUuid QUuid
#define RMetaString QString
#define RMetaDouble double
#define RMetaDateTime QDateTime
#define RMetaMoney double

// for cast -> auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
#define CAST_DATAREL_TO_TYPEREL(type) *reinterpret_cast<type*>(reinterpret_cast<char*>(&data)+pr.dif)
#define CAST_CONST_DATAREL_TO_TYPEREL(type) *reinterpret_cast<const type*>(reinterpret_cast<const char*>(&data)+pr.dif)

namespace Ramio {

/**
 * @brief The ItemData struct
 */
struct ItemData
{
	RMetaUuid uuid;
	RMetaPKey id = 0;
	RMetaInt type = 0;

	virtual ~ItemData() = default;
};

} // Ramio::
