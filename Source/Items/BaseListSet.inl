/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "BaseListSet.h"

namespace Ramio {

template<typename ITEM, typename STRUCTDATA> class BaseListSetItemCreator <ITEM, STRUCTDATA, true>
{
public:
	ITEM* createItem() const {return new ITEM;}
	ITEM* createItem(const ItemData& data) const {return new ITEM(static_cast<const STRUCTDATA&>(data));}
	ITEM* createItem(ItemData&& data) const {return new ITEM(static_cast<STRUCTDATA&&>(std::move(data)));}
};

template<typename ITEM, typename STRUCTDATA> class BaseListSetItemCreator <ITEM, STRUCTDATA, false>
{
public:
	ITEM* createItem() const {return Q_NULLPTR;}
	ITEM* createItem(const ItemData& data) const {Q_UNUSED(data); return Q_NULLPTR;}
	ITEM* createItem(ItemData&& data) const {Q_UNUSED(data); return Q_NULLPTR;}
};

} // Ramio::
