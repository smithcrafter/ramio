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

#pragma once

#include "AbstractListSet.h"
#include "StructItem.h"
// c++
#include <functional>

namespace Ramio {

template<typename STRUCTDATA, bool> class StructItemSetFindByUUid;

template<typename STRUCTDATA>
class StructItemSet : public AbstractListSet, public StructItemSetFindByUUid<STRUCTDATA, has_uuid<STRUCTDATA>::value>
{
	Q_DISABLE_COPY(StructItemSet)
public:
	StructItemSet(QList<StructItem<STRUCTDATA>*>& items, QObject* parent = Q_NULLPTR)
		: AbstractListSet(reinterpret_cast<QList<Item*>&>(items), parent),
		  StructItemSetFindByUUid<STRUCTDATA, has_uuid<STRUCTDATA>::value>(items),
		  items_(items) {}

	const QList<StructItem<STRUCTDATA>*>& items() Q_DECL_NOTHROW { return items_; }
	const QList<const StructItem<STRUCTDATA>*>& items() const Q_DECL_NOTHROW {
		return reinterpret_cast<const QList<const StructItem<STRUCTDATA>*>&>(const_cast<StructItemSet*>(this)->items());}

	inline typename QList<StructItem<STRUCTDATA>*>::iterator begin() Q_DECL_NOTHROW {return items_.begin();}
	inline typename QList<StructItem<STRUCTDATA>*>::iterator end() Q_DECL_NOTHROW {return items_.end();}
	inline typename QList<const StructItem<STRUCTDATA>*>::const_iterator begin() const Q_DECL_NOTHROW {return items().begin();}
	inline typename QList<const StructItem<STRUCTDATA>*>::const_iterator end() const Q_DECL_NOTHROW {return items().end();}

	Item* addItem(const STRUCTDATA& data);
	Item* addItem(STRUCTDATA&& data);
	template < typename... Atr>
	Item* addItem(Atr... art) {return this->addItem(STRUCTDATA(art...));}
	QList<Item*> addItems(const QList<STRUCTDATA>& datalist);
	QList<Item*> addItems(const QList<const STRUCTDATA*>& datalist) {return reinterpret_cast<const QList<STRUCTDATA>&>(datalist);}

	void insertItem(Item& item) {AbstractListSet::insertItem(item);}
	void insertItem(StructItem<STRUCTDATA>* item);
	void insertItems(const QList<StructItem<STRUCTDATA>*>& itemslist);

	void clear() Q_DECL_OVERRIDE;

	StructItem<STRUCTDATA>* createItem() const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>;}
	StructItem<STRUCTDATA>* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>(static_cast<const STRUCTDATA&>(data));}
	StructItem<STRUCTDATA>* createItem(ItemData&& data) const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>(static_cast<STRUCTDATA&&>(std::move(data)));}

	using SortFunction = bool (*)(const StructItem<STRUCTDATA>*, const StructItem<STRUCTDATA>*);
	void sort(SortFunction function) { bool r = startReload(); std::sort(items_.begin(), items_.end(), function); if (r) finishReload();}
	void sort(std::function<bool(const StructItem<STRUCTDATA>* t1, const StructItem<STRUCTDATA>* t2)>* function) {
		bool r = startReload(); std::sort(items_.begin(), items_.end(), function); if (r) finishReload();}

	StructItem<STRUCTDATA>* itemById(RMPKey id) Q_DECL_OVERRIDE;

private:
	QList<StructItem<STRUCTDATA>*>& items_;
};

} // Ramio::

#include "StructItemSet.inl"
