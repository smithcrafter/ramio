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

#include "Components.h"

namespace Ramio {

Components::Components(QObject* parent)
	: QObject(parent)
{
}

AbstractMetaSet* Components::findSet(const QString& setName)
{
	for (AbstractMetaSet* set: sets_)
		if (set->meta().setName == setName)
			return set;
	return Q_NULLPTR;
}

AbstractMetaSet* Components::findSetByItemName(const QString& itemName)
{
	for (AbstractMetaSet* set: sets_)
		if (set->meta().itemName == itemName)
			return set;
	return Q_NULLPTR;
}

void Components::addSet(AbstractMetaSet& set)
{
	sets_.append(&set);
	connect(set.aSet(), &AbstractListSet::added, this, [this, &set](const Item& item) {this->itemCreated(set, item);});
	connect(set.aSet(), &AbstractListSet::changed, this, [this, &set](const Item& item) {this->itemChanged(set, item);});
	connect(set.aSet(), &AbstractListSet::deleted, this, [this, &set](const Item& item) {this->itemDeleted(set, item);});
}

void Components::initSubComponents(Components& other)
{
	for (auto set: other.sets())
		this->addSet(*set);
}

} // Ramio::
