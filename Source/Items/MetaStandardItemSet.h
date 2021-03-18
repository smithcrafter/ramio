/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MetaItemSet.h"

namespace Ramio {

template<typename METASTRUCTDATA>
class RAMIO_LIB_EXPORT StandardItem : public StructItem<METASTRUCTDATA>
{
	using Base = StructItem<METASTRUCTDATA>;
public:
	explicit StandardItem(ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {}
	StandardItem(const METASTRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher){}
	StandardItem(METASTRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR) : Base(std::move(data), watcher) {}
	~StandardItem() Q_DECL_OVERRIDE { if (!Item::watchers_.isEmpty()) this->beforeDeleted(); }

	const RMType& type() const {return Base::data().type;}
	const RMState& state() const {return Base::data().state;}
	const RMFlags& flags() const {return Base::data().flags;}
};


template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID = true, bool CACHEDUUID = false>
class RAMIO_LIB_EXPORT MetaStandardItemSet : public MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>
{
	using Base = MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>;
	METAITEM* itemByUuidBase(const RMUuid& uid) {for (auto* item: Base::items()) if (item->uuid() == uid) return item; return Q_NULLPTR;}
public:
	MetaStandardItemSet(QString setName, QString itemName, std::shared_ptr<Meta::TypeDescription> typeDescription =
			std::shared_ptr<Meta::TypeDescription>(), QObject* parent = Q_NULLPTR);
	MetaStandardItemSet(QString setName, QString itemName, QObject* parent = Q_NULLPTR)
		: MetaStandardItemSet(setName, itemName, std::shared_ptr<Meta::TypeDescription>(), parent) {}

	METAITEM* itemByUuid(const RMUuid& uid) {return uuidCache_.findItem(uid, &MetaStandardItemSet::itemByUuidBase, *this);}
	const METAITEM* itemByUuid(const RMUuid& uid) const {return const_cast<MetaStandardItemSet*>(this)->itemByUuid(uid);}

protected:
	void doOnItemAdding(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemAdding(item); uuidCache_.add(static_cast<StandardItem<METASTRUCTDATA>&>(item).uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemChanging(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item); uuidCache_.remove(static_cast<StandardItem<METASTRUCTDATA>&>(item).uuid());}
	void doOnItemChanged(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item); uuidCache_.add(static_cast<StandardItem<METASTRUCTDATA>&>(item).uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemRemoving(item); uuidCache_.remove(static_cast<StandardItem<METASTRUCTDATA>&>(item).uuid());}

protected:
	CacheMapStruct<const RMUuid&, MetaStandardItemSet, METAITEM, CACHEDUUID> uuidCache_;
};

} // Ramio::

#include "MetaStandardItemSet.inl"
