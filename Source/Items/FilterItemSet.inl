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

#include "FilterItemSet.h"

namespace Ramio {

template<typename STRUCTITEM>
FilterItemSet<STRUCTITEM>::FilterItemSet(const AbstractSet& originalSet, std::function<bool(const STRUCTITEM& t1)> filterFunction,
										QObject* parent)
	: Base(reinterpret_cast<QList<Item*>&>(const_cast<QList<STRUCTITEM*>&>(this->items())), parent),
	  set_(originalSet),
	  function_(filterFunction)
{
	connect(&set_, &AbstractSet::added, this, &FilterItemSet<STRUCTITEM>::onAdded);
	connect(&set_, &AbstractSet::changed, this, &FilterItemSet<STRUCTITEM>::onChanged);
	connect(&set_, &AbstractSet::deleted, this, &FilterItemSet<STRUCTITEM>::onRemoved);
	connect(&set_, &AbstractSet::reloaded, this, &FilterItemSet<STRUCTITEM>::reload);

	reload();
}

template<typename STRUCTITEM>
void FilterItemSet<STRUCTITEM>::reload()
{
	this->clear();

	startReload();
	for (const Item* item: set_.items())
		if (function_(*static_cast<const STRUCTITEM*>(item)))
			this->addItem(*const_cast<Item*>(item));
	finishReload();
}

template<typename STRUCTITEM>
void FilterItemSet<STRUCTITEM>::onAdded(const Item& item)
{
	if (function_(static_cast<const STRUCTITEM&>(item)))
		this->addItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void FilterItemSet<STRUCTITEM>::onChanged(const Item& item)
{
	if (!items_.contains(const_cast<STRUCTITEM*>(static_cast<const STRUCTITEM*>(&item))))
		onAdded(item);
	else if (function_(static_cast<const STRUCTITEM&>(item)) == false)
		onRemoved(item);
	else
		changedItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void FilterItemSet<STRUCTITEM>::onRemoved(const Item& item)
{
	this->removeItem(const_cast<Item&>(item));
}

} // Ramio::
