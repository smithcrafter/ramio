/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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


#include "Item.h"
#include "ItemObserver.h"
// Qt
#include <QStringBuilder>

namespace Ramio {

Item::Item(ItemData& data, ItemObserver* watcher)
	: data_(data)
{
	if (watcher)
		this->addItemWatcher(*watcher);
}

Item::~Item()
{
	this->beforeDeleted();
}

QString Item::shortDesc() const
{
	return QStringLiteral("id:") % QString::number(data_.id);
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
	for (ItemObserver* watcher : watchers_)
		watcher->changingItem(*this);
}

void Item::afterChanging()
{
	for (ItemObserver* watcher : watchers_)
		watcher->changedItem(*this);
	doAfterChanging();
}

void Item::beforeDeleted()
{
	if (watchers_.isEmpty())
		return;
	QList<ItemObserver*> watchers = watchers_.values();
	watchers_.clear();
	for (ItemObserver* watcher: watchers)
		watcher->removeItem(*this);
}

} // Ramio::
