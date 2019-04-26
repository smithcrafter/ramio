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
			std::unique_ptr<Meta::TypeDescription>(), QObject* parent = Q_NULLPTR)
		: Base(reinterpret_cast<QList<StructItem<METASTRUCTDATA>*>&>(this->items()), parent),
		  AbstractMetaSet(reinterpret_cast<QList<StructItem<MetaItemData>*>&>(this->items()))
	{
		meta_.itemName = std::move(itemName);
		meta_.setName = std::move(setName);
		meta_.size = sizeof(METASTRUCTDATA);
		meta_.typeDescription = std::move(typeDescription);
		meta_.properties = METASTRUCTDATA().registerMetaFields();
	}
	~MetaItemSet() Q_DECL_OVERRIDE {this->clear();}

	QList<METAITEM*>& items() {return items_;}
	const QList<METAITEM*>& items() const {return items_;}

	METAITEM* createItem() const Q_DECL_OVERRIDE {return new METAITEM();}
	METAITEM* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return new METAITEM(static_cast<const METASTRUCTDATA&>(data));}
	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem());}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(createItem(data));}

	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE {return new METASTRUCTDATA();}

	void addMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {this->addItem(reinterpret_cast<StructItem<METASTRUCTDATA>*>(item));}

	AbstractSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {
		return new MetaItemSet<METAITEM, METASTRUCTDATA>(meta_.setName, meta_.itemName,
														 meta_.cloneTypeDescription(), parent);}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {
		return new MetaItemSet<METAITEM, METASTRUCTDATA>(meta_.setName, meta_.itemName,
														 meta_.cloneTypeDescription(), parent);}

	METAITEM* itemById(RMetaPKey id) {return FinderStruct<RMetaPKey, MetaItemSet, METAITEM, CACHEDID>().
				findItem(id, &MetaItemSet::itemByIdBase, idCache_, *this);}
	METAITEM* itemByUuid(const RMetaUuid& uid)  {return FinderStruct<const RMetaUuid& , MetaItemSet, METAITEM, CACHEDUUID>().
				findItem(uid, &MetaItemSet::itemByUuidBase, uuidCache_, *this);}

protected:
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

template<typename TYPE, typename METAITEM> struct MapStruct<TYPE, METAITEM, false> {
	inline void add(TYPE, METAITEM*) {}
	inline void remove(TYPE){}
};
template<typename TYPE, typename METAITEM> struct MapStruct<TYPE, METAITEM, true> {
	QMap<TYPE, METAITEM*> map;
	void add(TYPE id, METAITEM* item) {map.insert(id, item);}
	void remove(TYPE id){map.remove(id);}
};

template<typename TYPE, typename METAITEMSET, typename METAITEM> struct FinderStruct<TYPE, METAITEMSET, METAITEM, false> {
	typedef METAITEM* (METAITEMSET::* func)(TYPE id);
	inline METAITEM* findItem(TYPE id, func f, MapStruct<remove_const_reference_t(TYPE), METAITEM, false>&, METAITEMSET& set) {
		return (set.*f)(id);}
};
template<typename TYPE, typename METAITEMSET, typename METAITEM> struct FinderStruct<TYPE, METAITEMSET, METAITEM, true> {
	typedef METAITEM* (METAITEMSET::* func)(TYPE id);
	inline METAITEM* findItem(TYPE id, func, MapStruct<remove_const_reference_t(TYPE), METAITEM, true>& map, METAITEMSET&) {
		return map.map[id];}
};

} // Ramio::
