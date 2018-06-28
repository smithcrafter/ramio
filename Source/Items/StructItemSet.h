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

#pragma once

#include "AbstarctSet.h"
#include "StructItem.h"
// c++
#include <functional>

namespace Ramio {

template<typename STRUCTDATA>
class StructItemSet : public AbstarctSet
{
	Q_DISABLE_COPY(StructItemSet)
public:
	StructItemSet(QList<StructItem<STRUCTDATA>*>& items, QObject* parent = Q_NULLPTR)
		: AbstarctSet(reinterpret_cast<QList<Item*>&>(items), parent), items_(items) {}

	const QList<StructItem<STRUCTDATA>*>& items() { return items_; }
	const QList<const StructItem<STRUCTDATA>*>& items() const;

	void addItem(Item& item) {AbstarctSet::addItem(item);}
	void addItem(StructItem<STRUCTDATA>* item);
	void addItem(const STRUCTDATA& data);
	void clear() Q_DECL_OVERRIDE;

	//template < typename... Atr>
	//void addItem(Atr... art){	items_.append(new StructItem<STRUCTDATA>(STRUCTDATA(art...) , this));}

	StructItem<STRUCTDATA>* createItem() const Q_DECL_OVERRIDE {return new StructItem<STRUCTDATA>;}

	using SortFunction = bool (*)(const StructItem<STRUCTDATA>*, const StructItem<STRUCTDATA>*);
	void sort(SortFunction function){
		std::sort(items_.begin(), items_.end(), function);}
	void sort(std::function<bool(const StructItem<STRUCTDATA>* t1, const StructItem<STRUCTDATA>* t2)>* function) {
		std::sort(items_.begin(), items_.end(), function);}

	StructItem<STRUCTDATA>* itemById(RMetaPKey id);
	StructItem<STRUCTDATA>* itemByUuid(const QUuid& uid);

private:
	QList<StructItem<STRUCTDATA>*>& items_;
};

} // Ramio::

#include "StructItemSet.inl"
