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

#include "ItemSet.h"
#include "AbstractMetaSet.h"

namespace Ramio {

template<typename TYPE, typename METAITEMSET, typename METAITEM, bool> struct CacheMapStruct;

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID = true>
class RAMIO_LIB_EXPORT MetaItemSet : public ItemSet<METAITEM, METASTRUCTDATA>, public AbstractMetaSet
{
	Q_DISABLE_COPY(MetaItemSet)
	using Base = ItemSet<METAITEM, METASTRUCTDATA>;
	inline METAITEM* itemByIdBase(RMPKey id) {return static_cast<METAITEM*>(Base::itemById(id));}
public:
	MetaItemSet(QObject* parent = Q_NULLPTR); // do not init meta
	MetaItemSet(QString setName, QString itemName, QObject* parent = Q_NULLPTR);
	MetaItemSet(const Meta::Description& meta, QObject* parent = Q_NULLPTR);
	~MetaItemSet() Q_DECL_OVERRIDE {this->clear();}


//TODO
//FIXME	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE {return new METASTRUCTDATA();}
	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE {return Q_NULLPTR;}

	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(Base::createItem());}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE {return reinterpret_cast<StructItem<MetaItemData>*>(Base::createItem(data));}

	void insertMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {this->insertItem(reinterpret_cast<METAITEM*>(item));}

	AbstractListSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractListSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return createTemporarySet(parent);}


	inline const MetaItemSet& asConst() Q_DECL_NOTHROW {return *const_cast<const MetaItemSet*>(this);}

	METAITEM* itemById(RMPKey id) Q_DECL_OVERRIDE {return idCache_.findItem(id, &MetaItemSet::itemByIdBase, *this);}
	const METAITEM* itemById(RMPKey id) const {return const_cast<MetaItemSet*>(this)->itemById(id);}

	void insertItems(const QList<METAITEM*>& itemslist) {Base::insertItems(reinterpret_cast<const QList<StructItem<METASTRUCTDATA>*>&>(itemslist));}

protected:
	void doOnItemAdding(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemAdding(item);idCache_.add(item.id(), static_cast<METAITEM*>(&item));}
	void doOnItemChanging(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);idCache_.remove(item.id());}
	void doOnItemChanged(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemChanged(item);idCache_.add(item.id(), static_cast<METAITEM*>(&item));}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE {
		Base::doOnItemRemoving(item);idCache_.remove(item.id());}
private:
	MetaItemSet<METAITEM, METASTRUCTDATA>* createTemporarySet(QObject* parent) const {
		return new MetaItemSet<METAITEM, METASTRUCTDATA>(meta_, parent);}
private: // qdoc bug fix
	CacheMapStruct<RMPKey, MetaItemSet, METAITEM, CACHEDID> idCache_;
};

} // Ramio::

#include "MetaItemSet.inl"
