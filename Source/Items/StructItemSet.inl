/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

template<typename STRUCTDATA> class StructItemSetFindByUUid<STRUCTDATA, false> {
public:
	StructItemSetFindByUUid(QList<StructItem<STRUCTDATA>*>& /*items*/) {}
};

template<typename STRUCTDATA> class StructItemSetFindByUUid <STRUCTDATA, true> {
public:
	StructItemSetFindByUUid(QList<StructItem<STRUCTDATA>*>& items) : items_(items) {}

	StructItem<STRUCTDATA>* itemByUuid(const RMUuid& uid)
	{
		for (auto* item: items_)
			if (item->data().uuid == uid)
				return item;
		return Q_NULLPTR;
	}
private:
	QList<StructItem<STRUCTDATA>*>& items_;
};

template<typename STRUCTDATA>
Item* StructItemSet<STRUCTDATA>::addItem(const STRUCTDATA& data)
{
	return AbstractListSet::addItem(*this->createItem(data));
}

template<typename STRUCTDATA>
Item* StructItemSet<STRUCTDATA>::addItem(STRUCTDATA&& data)
{
	return AbstractListSet::addItem(*this->createItem(std::move(data)));
}

template<typename STRUCTDATA>
QList<Item*> StructItemSet<STRUCTDATA>::addItems(const QList<STRUCTDATA>& datalist)
{
	QList<Item*> reslist;
	startReload();
	for (const auto& data: datalist)
		reslist.append(addItem(data));
	finishReload();
	return reslist;
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::insertItem(StructItem<STRUCTDATA>* item)
{
	Q_ASSERT(item != Q_NULLPTR);
	AbstractListSet::addItem(*item);
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::insertItems(const QList<StructItem<STRUCTDATA>*>& itemslist)
{
	startReload();
	for (auto* data: itemslist)
		insertItem(data);
	finishReload();
}

template<typename STRUCTDATA>
void StructItemSet<STRUCTDATA>::clear()
{
	startReload();
	for (auto* item: items_)
		removeItem(*item);
	finishReload();
}

template<typename STRUCTDATA>
StructItem<STRUCTDATA>* StructItemSet<STRUCTDATA>::itemById(RMPKey id)
{
	for (auto* item: items_)
		if (item->id() == id)
			return item;
	return Q_NULLPTR;
}

} // Ramio::
