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

#include "FilterItemSet.h"

namespace Ramio {

template<typename STRUCITEM>
FilterItemSet<STRUCITEM>::FilterItemSet(const AbstarctSet& originalSet, std::function<bool(const STRUCITEM& t1)> filterFunction)
	: Base(reinterpret_cast<QList<Item*>&>(items())),
	  set_(originalSet),
	  function_(filterFunction)
{
	connect(&set_, &AbstarctSet::added, this, &FilterItemSet<STRUCITEM>::onAdded);
	connect(&set_, &AbstarctSet::changed, this, &FilterItemSet<STRUCITEM>::onChanged);
	connect(&set_, &AbstarctSet::deleted, this, &FilterItemSet<STRUCITEM>::onRemoved);
	connect(&set_, &AbstarctSet::reloaded, this, &FilterItemSet<STRUCITEM>::reload);

	reload();
}

template<typename STRUCITEM>
void FilterItemSet<STRUCITEM>::reload()
{
	this->clear();

	emit reloading();
	for (const Item* item: set_.items())
		if (function_(*static_cast<const STRUCITEM*>(item)))
			this->addItem(*const_cast<Item*>(item));
	emit reloaded();
}

template<typename STRUCITEM>
void FilterItemSet<STRUCITEM>::onAdded(const Item& item)
{
	if (function_(static_cast<const STRUCITEM&>(item)))
		this->addItem(const_cast<Item&>(item));
}

template<typename STRUCITEM>
void FilterItemSet<STRUCITEM>::onChanged(const Item& item)
{
	if (!items_.contains(const_cast<STRUCITEM*>(static_cast<const STRUCITEM*>(&item))))
		onAdded(item);
	else if (function_(static_cast<const STRUCITEM&>(item)) == false)
		onRemoved(item);
}

template<typename STRUCITEM>
void FilterItemSet<STRUCITEM>::onRemoved(const Item& item)
{
	this->removeItem(const_cast<Item&>(item));
}

} // Ramio::
