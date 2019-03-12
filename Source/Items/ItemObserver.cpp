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

#include "ItemObserver.h"

namespace Ramio {

ItemObserver::ItemObserver(QObject* parent)
	: QObject(parent)
{
}

ItemObserver::~ItemObserver()
{
}

void ItemObserver::addItem(Item& item)
{
	if (contains(item))
		return;
	emit adding(item);
	this->doOnItemAdding(item);
	item.addItemWatcher(*this);
	emit added(item);
}

void ItemObserver::changingItem(Item& item)
{
	if (!contains(item))
		return;
	this->doOnItemChanging(item);
	emit changing(item);
}

void ItemObserver::changedItem(Item& item)
{
	if (!contains(item))
		return;
	this->doOnItemChanged(item);
	emit changed(item);
}

void ItemObserver::removeItem(Item& item)
{
	if (!contains(item))
		return;

	emit deleting(item);
	this->doOnItemRemoving(item);
	emit deleted(item);
	this->dropItem(item);
}

void ItemObserver::dropItem(Item& item)
{
	if (item.removeItemWatcher(*this))
		if (item.watchers().isEmpty())
			delete &item;
}

} // Ramio::
