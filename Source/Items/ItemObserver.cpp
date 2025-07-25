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

#include "ItemObserver.h"

namespace Ramio {

QString containerStateName(ContainerState state)
{
	switch (state) {
		case ContainerState::Empty: return QObject::tr("Empty");
		case ContainerState::Loading: return QObject::tr("Loading");
		case ContainerState::Loaded: return QObject::tr("Loaded");
		case ContainerState::Error: return QObject::tr("Error");
	}
	return QString();
}

ItemObserver::ItemObserver(QObject* parent)
	: QObject(parent)
{
}

ItemObserver::~ItemObserver()
{
}

Item* ItemObserver::addItem(Item& item)
{
#ifdef FULL_ASSERTS
	Q_ASSERT(!contains(item));
#endif
	emit adding(item);
	this->doOnItemAdding(item);
	item.addItemWatcher(*this);
	emit added(item);
	return &item;
}

void ItemObserver::changingItem(Item& item)
{
#ifdef FULL_ASSERTS
	if (!contains(item))
		return;
#endif
	this->doOnItemChanging(item);
	emit changing(item);
}

void ItemObserver::changedItem(Item& item)
{
#ifdef FULL_ASSERTS
	if (!contains(item))
		return;
#endif
	this->doOnItemChanged(item);
	emit changed(item);
}

void ItemObserver::stateChangedItem(Item& item)
{
#ifdef FULL_ASSERTS
	if (!contains(item))
		return;
#endif
	emit stateChanged(item);
}

void ItemObserver::removeItem(const Item& item)
{
#ifdef FULL_ASSERTS
	if (!contains(item))
		return;
#endif
	emit deleting(item);
	this->doOnItemRemoving(const_cast<Item&>(item));
	emit deleted(item);
	this->dropItem(item);
}

void ItemObserver::dropItem(const Item& item)
{
	if (const_cast<Item&>(item).removeItemWatcher(*this))
	{
		for (auto* watcher: item.watchers())
			if (watcher->owner_)
				return;
		delete &item;
	}
}

} // Ramio::
