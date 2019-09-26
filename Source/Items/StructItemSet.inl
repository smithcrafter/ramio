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

#include "StructItemSet.h"

namespace Ramio {

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::addItem(StructItem<STRUCTDATA>* item)
{
	Q_ASSERT(item != Q_NULLPTR);
	AbstractSet::addItem(*item);
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::addItem(const STRUCTDATA& data)
{
	AbstractSet::addItem(*this->createItem(data));
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::addItems(const QList<STRUCTDATA>& datalist)
{
	startReload();
	for (const auto& data: datalist)
		addItem(data);
	finishReload();
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::addItems(const QList<const STRUCTDATA*>& datalist)
{
	startReload();
	for (const auto data: datalist)
		addItem(*data);
	finishReload();
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::addItems(const QList<StructItem<STRUCTDATA>*>& itemslist)
{
	startReload();
	for (auto* data: itemslist)
		addItem(data);
	finishReload();
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::clear()
{
	startReload();
	Q_FOREACH(StructItem<STRUCTDATA>* item, items_)
		dropItem(*item);
	items_.clear();
	finishReload();
}

template<typename STRUCTDATA>
StructItem<STRUCTDATA>* StructItemSet<STRUCTDATA>::itemById(RMetaPKey id)
{
	for (StructItem<STRUCTDATA>* item: items_)
		if (item->id() == id)
			return item;
	return Q_NULLPTR;
}

template<typename STRUCTDATA>
StructItem<STRUCTDATA>* StructItemSet<STRUCTDATA>::itemByUuid(const RMetaUuid& uid)
{
	for (StructItem<STRUCTDATA>* item: items_)
		if (item->uuid() == uid)
			return item;
	return Q_NULLPTR;
}

template<typename STRUCTDATA>
const QList<const StructItem<STRUCTDATA>*>& StructItemSet<STRUCTDATA>::items() const
{
	return reinterpret_cast<const QList<const StructItem<STRUCTDATA>*>&>(const_cast<StructItemSet*>(this)->items());
}

} // Ramio::
