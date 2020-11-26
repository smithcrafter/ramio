/*
 * Copyright (C) 2016-2020 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MergerItemSet.h"

namespace Ramio {

template<typename STRUCTITEM>
MergerItemSet<STRUCTITEM>::MergerItemSet<STRUCTITEM>(const AbstractSet& set1, const AbstractSet& set2, QObject* parent)
	: Base(reinterpret_cast<QList<Item*>&>(const_cast<QList<STRUCTITEM*>&>(this->items())), parent),
	  set1_(set1),
	  set2_(set2)
{
	connect(&set1_, &AbstractSet::added, this, &FilterItemSet<STRUCTITEM>::onAdded);
	connect(&set1_, &AbstractSet::changed, this, &FilterItemSet<STRUCTITEM>::onChanged);
	connect(&set1_, &AbstractSet::deleted, this, &FilterItemSet<STRUCTITEM>::onRemoved);
	connect(&set1_, &AbstractSet::reloaded, this, &FilterItemSet<STRUCTITEM>::reload);

	connect(&set2_, &AbstractSet::added, this, &FilterItemSet<STRUCTITEM>::onAdded);
	connect(&set2_, &AbstractSet::changed, this, &FilterItemSet<STRUCTITEM>::onChanged);
	connect(&set2_, &AbstractSet::deleted, this, &FilterItemSet<STRUCTITEM>::onRemoved);
	connect(&set2_, &AbstractSet::reloaded, this, &FilterItemSet<STRUCTITEM>::reload);

	reload();
}

template<typename STRUCTITEM>
MergerItemSet<STRUCTITEM>::reload()
{
	this->clear();

	startReload();

	for (const Item* item: set1_.items())
		Base::addItem(*const_cast<Item*>(item));
	for (const Item* item: set2_.items())
		if (!contains(item))
			Base::addItem(*const_cast<Item*>(item));
	finishReload();
}

template<typename STRUCTITEM>
void MergerItemSet<STRUCTITEM>::onAdded(const Item& item)
{
	auto setPtr = static_cast<AbstractSet>(sender());
	Q_ASSERT(setPtr);
	auto set2 = otherSet(*setPtr);

	if (!set2.contains(item))
		Base::addItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void MergerItemSet<STRUCTITEM>::onChanged(const Item& item)
{
	Base::changedItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void MergerItemSet<STRUCTITEM>::onRemoved(const Item& item)
{
	auto setPtr = static_cast<AbstractSet>(sender());
	Q_ASSERT(setPtr);
	auto set2 = otherSet(*setPtr);
	if (!set2.contains(item))
		Base::removeItem(const_cast<Item&>(item));
}

} // Ramio::
