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

#include "AbstractSet.h"

namespace Ramio {

AbstractSet::AbstractSet(QList<Item*>& items, QObject* parent)
	: ItemObserver(parent),
	  items_(items)
{
}

AbstractSet::~AbstractSet() = default;

void AbstractSet::clear()
{
	startReload();
	items_.clear();
	finishReload();
}

const QList<const Item*>& AbstractSet::items() const
{
	return reinterpret_cast<const QList<const Item*>&>(const_cast<AbstractSet*>(this)->items());
}

Item* AbstractSet::itemByUuid(const RMetaUuid& uid)
{
	for (Item* item: items_)
		if (item->uuid() == uid)
			return item;
	return Q_NULLPTR;
}

Item* AbstractSet::itemById(RMetaPKey id)
{
	for (Item* item: items_)
		if (item->id() == id)
			return item;
	return Q_NULLPTR;
}

void AbstractSet::doOnItemAdding(Item& item)
{
#ifdef FULL_ASSERTS
	Q_ASSERT(!items_.contains(&item));
#endif
	items_.append(&item);
}

void AbstractSet::doOnItemChanging(Item&)
{
}

void AbstractSet::doOnItemChanged(Item&)
{
}

void AbstractSet::doOnItemRemoving(Item& item)
{
#ifdef FULL_ASSERTS
	Q_ASSERT(items_.contains(&item));
#endif
	items_.removeOne(&item);
}

} // Ramio::
