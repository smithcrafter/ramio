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

#include "ItemSet.h"
#include "AbstractMetaSet.h"

namespace Ramio {

template<typename TYPE, typename METAITEM, bool> struct MapStruct;
template<typename TYPE, typename METAITEMSET, typename METAITEM, bool> struct FinderStruct;

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID = true, bool CACHEDUUID = false>
class MetaItemSet : public StructItemSet<METASTRUCTDATA>, public AbstractMetaSet
{
	Q_DISABLE_COPY(MetaItemSet)
	using Base = StructItemSet<METASTRUCTDATA>;
public:
	MetaItemSet(QString setName, QString itemName, std::unique_ptr<Meta::TypeDescription> typeDescription =
			std::unique_ptr<Meta::TypeDescription>(), QObject* parent = Q_NULLPTR);
	~MetaItemSet() Q_DECL_OVERRIDE {this->clear();}

	QList<METAITEM*>& items() {return items_;}
	const QList<METAITEM*>& items() const {return items_;}

	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE {return new METASTRUCTDATA();}

	METAITEM* createItem() const Q_DECL_OVERRIDE {return new METAITEM();}
	METAITEM* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return new METAITEM(static_cast<const METASTRUCTDATA&>(data));}
	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem());}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem(data));}

	void addMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {this->addItem(reinterpret_cast<StructItem<METASTRUCTDATA>*>(item));}

	AbstractSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}

	METAITEM* itemById(RMetaPKey id) {return FinderStruct<RMetaPKey, MetaItemSet, METAITEM, CACHEDID>().
				findItem(id, &MetaItemSet::itemByIdBase, idCache_, *this);}
	METAITEM* itemByUuid(const RMetaUuid& uid) {return FinderStruct<const RMetaUuid& , MetaItemSet, METAITEM, CACHEDUUID>().
				findItem(uid, &MetaItemSet::itemByUuidBase, uuidCache_, *this);}

	const METAITEM* itemById(RMetaPKey id) const {return const_cast<MetaItemSet*>(this)->itemById(id);}
	const METAITEM* itemByUuid(const RMetaUuid& uid) const {return const_cast<MetaItemSet*>(this)->itemByUuid(uid);}

protected:
	MetaItemSet<METAITEM, METASTRUCTDATA>* createTemporarySet(QObject* parent) const {
		return new MetaItemSet<METAITEM, METASTRUCTDATA>(meta_.setName, meta_.itemName,
														 meta_.cloneTypeDescription(), parent);}
	METAITEM* itemByIdBase(RMetaPKey id) {return static_cast<METAITEM*>(Base::itemById(id));}
	METAITEM* itemByUuidBase(const RMetaUuid& uid) {return static_cast<METAITEM*>(Base::itemByUuid(uid));}

	void doOnItemAdding(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemAdding(item);
		idCache_.add(item.id(), static_cast<METAITEM*>(&item));
		uuidCache_.add(item.uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemChanging(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);
		idCache_.remove(item.id());
		uuidCache_.remove(item.uuid());}
	void doOnItemChanged(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);
		idCache_.add(item.id(), static_cast<METAITEM*>(&item));
		uuidCache_.add(item.uuid(), static_cast<METAITEM*>(&item));}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemRemoving(item);
		idCache_.remove(item.id());
		uuidCache_.remove(item.uuid());}

private:
	QList<METAITEM*> items_;
	MapStruct<RMetaPKey, METAITEM, CACHEDID> idCache_;
	MapStruct<RMetaUuid, METAITEM, CACHEDUUID> uuidCache_;
};

} // Ramio::

#include "MetaItemSet.inl"
