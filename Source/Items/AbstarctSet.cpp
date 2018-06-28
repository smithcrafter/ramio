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

#include "AbstarctSet.h"

namespace Ramio {

AbstarctSet::AbstarctSet(QList<Item*>& items, QObject* parent)
	: ItemObserver(parent),
	  items_(items)
{
}

AbstarctSet::~AbstarctSet() = default;

void AbstarctSet::clear()
{
	emit reloading();
	items_.clear();
	emit reloaded();
}

const QList<const Item*>& AbstarctSet::items() const
{
	return reinterpret_cast<const QList<const Item*>&>(const_cast<AbstarctSet*>(this)->items());
}

Item* AbstarctSet::itemByUuid(const QUuid& uid)
{
	for (Item* item: items_)
		if (item->uuid() == uid)
			return item;
	return Q_NULLPTR;
}

Item* AbstarctSet::itemById(quint64 id)
{
	for (Item* item: items_)
		if (item->id() == id)
			return item;
	return Q_NULLPTR;
}

void AbstarctSet::doOnItemAdding(Item& item)
{
	if (!items_.contains(&item))
		items_.append(&item);
}

void AbstarctSet::doOnItemChanging(Item& item)
{
}

void AbstarctSet::doOnItemChanged(Item& item)
{
}

void AbstarctSet::doOnItemRemoving(Item& item)
{
	if (items_.contains(&item))
		items_.removeAll(&item);
}

} // Ramio::
