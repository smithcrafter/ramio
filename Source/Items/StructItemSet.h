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

#pragma once

#include "AbstractSet.h"
#include "StructItem.h"
// c++
#include <functional>

namespace Ramio {

template<typename STRUCTDATA>
class StructItemSet : public AbstractSet
{
	Q_DISABLE_COPY(StructItemSet)
public:
	StructItemSet(QList<StructItem<STRUCTDATA>*>& items, QObject* parent = Q_NULLPTR)
		: AbstractSet(reinterpret_cast<QList<Item*>&>(items), parent), items_(items) {}

	const QList<StructItem<STRUCTDATA>*>& items() { return items_; }
	const QList<const StructItem<STRUCTDATA>*>& items() const;

	void addItem(Item& item) {AbstractSet::addItem(item);}
	void addItem(StructItem<STRUCTDATA>* item);
	void addItem(const STRUCTDATA& data);
	void addItems(const QList<STRUCTDATA>& datalist);
	void addItems(const QList<const STRUCTDATA*>& datalist);
	void addItems(const QList<StructItem<STRUCTDATA>*>& itemslist);
	void clear() Q_DECL_OVERRIDE;

	//template < typename... Atr>
	//void addItem(Atr... art){	items_.append(new StructItem<STRUCTDATA>(STRUCTDATA(art...) , this));}
	//void addItem(Atr... art) {this->addItem(STRUCTDATA(art...));}

	StructItem<STRUCTDATA>* createItem() const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>;}
	StructItem<STRUCTDATA>* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>(static_cast<const STRUCTDATA&>(data));}

	using SortFunction = bool (*)(const StructItem<STRUCTDATA>*, const StructItem<STRUCTDATA>*);
	void sort(SortFunction function) { bool r = startReload(); std::sort(items_.begin(), items_.end(), function); if (r) finishReload();}
	void sort(std::function<bool(const StructItem<STRUCTDATA>* t1, const StructItem<STRUCTDATA>* t2)>* function) {
		bool r = startReload(); std::sort(items_.begin(), items_.end(), function); if (r) finishReload();}

	StructItem<STRUCTDATA>* itemById(RMetaPKey id);
	StructItem<STRUCTDATA>* itemByUuid(const RMetaUuid& uid);

private:
	QList<StructItem<STRUCTDATA>*>& items_;
};

} // Ramio::

#include "StructItemSet.inl"
