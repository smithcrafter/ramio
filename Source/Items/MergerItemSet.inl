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
MergerItemSet<STRUCTITEM>::MergerItemSet(const AbstractListSet& set1, const AbstractListSet& set2, QObject* parent)
	: Base(reinterpret_cast<QList<Item*>&>(const_cast<QList<STRUCTITEM*>&>(this->items())), parent),
	  set1_(set1),
	  set2_(set2)
{
	connect(&set1_, &AbstractListSet::added, this, &MergerItemSet<STRUCTITEM>::onAdded);
	connect(&set1_, &AbstractListSet::changed, this, &MergerItemSet<STRUCTITEM>::onChanged);
	connect(&set1_, &AbstractListSet::deleted, this, &MergerItemSet<STRUCTITEM>::onRemoved);
	connect(&set1_, &AbstractListSet::reloaded, this, &MergerItemSet<STRUCTITEM>::reload);

	connect(&set2_, &AbstractListSet::added, this, &MergerItemSet<STRUCTITEM>::onAdded);
	connect(&set2_, &AbstractListSet::changed, this, &MergerItemSet<STRUCTITEM>::onChanged);
	connect(&set2_, &AbstractListSet::deleted, this, &MergerItemSet<STRUCTITEM>::onRemoved);
	connect(&set2_, &AbstractListSet::reloaded, this, &MergerItemSet<STRUCTITEM>::reload);

	reload();
}

template<typename STRUCTITEM>
void MergerItemSet<STRUCTITEM>::reload()
{
	this->clear();

	startReload();

	for (const Item* item: set1_.items())
		Base::addItem(*const_cast<Item*>(item));
	for (const Item* item: set2_.items())
		if (!contains(*item))
			Base::addItem(*const_cast<Item*>(item));
	finishReload();
}

template<typename STRUCTITEM>
void MergerItemSet<STRUCTITEM>::onAdded(const Item& item)
{
	auto setPtr = static_cast<AbstractListSet*>(sender());
	Q_ASSERT(setPtr);
	auto& set2 = otherSet(*setPtr);

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
	auto setPtr = static_cast<AbstractListSet*>(sender());
	Q_ASSERT(setPtr);
	auto& set2 = otherSet(*setPtr);
	if (!set2.contains(item))
		Base::removeItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
MultiMergerItemSet<STRUCTITEM>::MultiMergerItemSet(QList<const AbstractListSet*> sets, QObject* parent)
	: Base(reinterpret_cast<QList<Item*>&>(const_cast<QList<STRUCTITEM*>&>(this->items())), parent)
{
	for(auto set: sets)
		this->addSet(*set);
	reload();
}

template<typename STRUCTITEM>
void MultiMergerItemSet<STRUCTITEM>::addSet(const AbstractListSet& set)
{
	connect(&set, &AbstractListSet::added, this, &MultiMergerItemSet<STRUCTITEM>::onAdded);
	connect(&set, &AbstractListSet::changed, this, &MultiMergerItemSet<STRUCTITEM>::onChanged);
	connect(&set, &AbstractListSet::deleted, this, &MultiMergerItemSet<STRUCTITEM>::onRemoved);
	connect(&set, &AbstractListSet::reloaded, this, &MultiMergerItemSet<STRUCTITEM>::reload);
	connect(&set, &AbstractListSet::destroyed, this, [this](QObject* obj){this->sets_.removeOne(static_cast<AbstractListSet*>(obj));});
	sets_.append(&set);
}

template<typename STRUCTITEM>
void MultiMergerItemSet<STRUCTITEM>::reload()
{
	this->clear();

	startReload();
	for (auto set: sets_)
		for (const Item* item: set->items())
			if (!contains(*item))
				Base::addItem(*const_cast<Item*>(item));
	finishReload();
}

template<typename STRUCTITEM>
void MultiMergerItemSet<STRUCTITEM>::onAdded(const Item& item)
{
	if (!contains(item))
		Base::addItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void MultiMergerItemSet<STRUCTITEM>::onChanged(const Item& item)
{
	Base::changedItem(const_cast<Item&>(item));
}

template<typename STRUCTITEM>
void MultiMergerItemSet<STRUCTITEM>::onRemoved(const Item& item)
{
	auto setPtr = static_cast<AbstractListSet*>(sender());
	Q_ASSERT(setPtr);
	bool inOther = false;
	for (auto set: sets_)
		if (set != setPtr)
			if (set->contains(item))
			{
				inOther = true;
				break;
			}
	if (!inOther)
		Base::removeItem(const_cast<Item&>(item));
}


} // Ramio::
