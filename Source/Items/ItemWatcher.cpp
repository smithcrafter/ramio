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

#include "ItemWatcher.h"

namespace Ramio {

ItemWatcher::ItemWatcher(Item* item, bool owner, QObject* parent)
	: ItemObserver(parent),
	  item_(Q_NULLPTR)
{
	this->owner_ = owner;
	setItem(item);
}

ItemWatcher::~ItemWatcher()
{
	setItem(Q_NULLPTR);
}

void ItemWatcher::setItem(Item* item)
{
	Item* lastItem = item_;

	if (item && !lastItem)
		emit adding(*item);
	else if (lastItem && !item)
		emit deleting(*lastItem);
	else if (lastItem && item)
		emit changing(*lastItem);

	if (item_)
		ItemObserver::dropItem(*item_);
	item_ = item;
	if (item_)
		item_->addItemWatcher(*this);

	if (item && !lastItem)
		emit added(*item);
	else if (lastItem && !item)
		emit deleted(*lastItem);
	else if (lastItem && item)
		emit changed(*item);
}

void ItemWatcher::doOnItemRemoving(Item& item)
{
	if (&item == item_)
		item_ = Q_NULLPTR;
}

} // Ramio::
