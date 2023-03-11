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

#pragma once

#include "Item.h"

#define FIELD_DETECTOR(FieldDetetorName, FType, FName) \
template<typename T> struct FieldDetetorName \
{ \
private: \
	template<typename U> static decltype(std::declval<U>().FName) detect(const U&); \
	static void detect(...); \
public: \
	static constexpr bool value = std::is_same<FType, decltype(detect(std::declval<T>()))>::value; \
};

namespace Ramio {

FIELD_DETECTOR(has_uuid, QUuid, uuid)

template<typename ITEM, typename STRUCTDATA, bool> class StructUUidItem;

template<typename ITEM, typename STRUCTDATA>
class StructItemCheckUUid : public StructUUidItem<ITEM, STRUCTDATA, has_uuid<STRUCTDATA>::value> {};



template<typename ITEM, typename STRUCTDATA> class StructUUidItem<ITEM, STRUCTDATA, false>
{
};

template<typename ITEM, typename STRUCTDATA> class StructUUidItem<ITEM, STRUCTDATA, true>
{
public:
	const RMUuid& uuid() const {return static_cast<const STRUCTDATA&>(static_cast<const ITEM*>(this)->data()).uuid;}
	RMString uuidStr() const {return uuid().toString();}
	void createUuidIfNull() {if (uuid().isNull()) static_cast<STRUCTDATA&>(static_cast<ITEM*>(this)->data()).uuid = QUuid::createUuid();}
};

} // Ramio::
