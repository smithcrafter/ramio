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


#include "Item.h"
#include "ItemObserver.h"

namespace Ramio {

Item::Item(RMetaPKey& id, RMetaInt& type, RMetaUuid& uid, ItemObserver* watcher)
	:
	  id_(id),
	  type_(type),
	  uuid_(uid)
{
	if (watcher)
		this->addItemWatcher(*watcher);
}

Item::~Item()
{
	QList<ItemObserver*> watchers = watchers_.toList();
	Q_FOREACH(ItemObserver* watcher, watchers)
	{
		watchers_.remove(watcher);
		watcher->removeItem(*this);
	}
}

bool Item::addItemWatcher(ItemObserver& watcher)
{
	if (watchers_.contains(&watcher))
		return false;
	watchers_.insert(&watcher);
	return true;
}

bool Item::removeItemWatcher(ItemObserver& watcher)
{
	if (watchers_.contains(&watcher))
	{
		watchers_.remove(&watcher);
		return true;
	}
	return false;
}

void Item::beforeChanging()
{
	for (ItemObserver* watcher :  watchers_)
		watcher->changingItem(*this);
}

void Item::afterChanging()
{
	for (ItemObserver* watcher :  watchers_)
		watcher->changedItem(*this);
	doAfterChanging();
}

void Item::beforeDeleted()
{
}

} // Ramio::
