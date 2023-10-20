/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#pragma once

#include "BaseListSet.h"

#include "StructItemSet.h"

#define GENERATE_ITEMSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::ItemSet<CLASS_NAME, STRUCTDATA> \
{ \
typedef ItemSet<CLASS_NAME, STRUCTDATA> Base;	 \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(parent) {}

#define GENERATE_ITEMSET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_ITEMSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
};

namespace Ramio {

template<typename ITEM, typename STRUCTDATA>
class ItemSet : public BaseListSet<ITEM, STRUCTDATA> , public StructItemSetFindByUUid<STRUCTDATA, has_uuid<STRUCTDATA>::value>
{
	Q_DISABLE_COPY(ItemSet)
	using Base = BaseListSet<ITEM, STRUCTDATA>;
public:
	ItemSet(QObject* parent = Q_NULLPTR) : Base(reinterpret_cast<QList<ITEM*>&>(items_), parent),
	StructItemSetFindByUUid<STRUCTDATA, has_uuid<STRUCTDATA>::value>(reinterpret_cast<QList<StructItem<STRUCTDATA>*>&>(items_)) {}
	~ItemSet() Q_DECL_OVERRIDE {this->clear();}

	AbstractListSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return new ItemSet(parent);}

	using SortFunction = bool (*)(const ITEM*, const ITEM*);
	void sort(SortFunction function) { bool r = ItemObserver::startReload(); std::sort(items_.begin(), items_.end(), function); if (r) ItemObserver::finishReload();}
	void sort(std::function<bool(const ITEM* t1, const ITEM* t2)>* function){
		bool r = ItemObserver::startReload(); std::sort(items_.begin(), items_.end(), function); if (r) ItemObserver::finishReload();}

	ITEM* addItem(const STRUCTDATA& data) {return static_cast<ITEM*>(AbstractListSet::addItem(*this->createItem(data)));}
	ITEM* addItem(STRUCTDATA&& data) {return static_cast<ITEM*>(AbstractListSet::addItem(*this->createItem(std::move(data))));}
	template < typename... Atr>	void addItem(Atr... art) {this->addItem(STRUCTDATA(art...));}
	void addItems(const QList<STRUCTDATA>& datalist);
	void addItems(const QList<const STRUCTDATA*>& datalist);

	void insertItem(ITEM& item) {AbstractListSet::insertItem(item);}
	void insertItem(ITEM* item) {Q_ASSERT(item != Q_NULLPTR); AbstractListSet::addItem(*item);}
	void insertItems(const QList<ITEM*>& itemslist);

	void clear() Q_DECL_OVERRIDE;

protected:
	QList<ITEM*> items_;
};

} // Ramio::

#include "ItemSet.inl"
