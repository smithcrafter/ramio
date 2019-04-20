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

template<typename METAITEM,  typename METASTRUCTDATA>
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

// TODO replace Q_NULLPTR on copy current Type

	METAITEM* itemById(RMetaPKey id) {return static_cast<METAITEM*>(Base::itemById(id));}
	METAITEM* itemByUuid(const RMetaUuid& uid)  {return static_cast<METAITEM*>(Base::itemByUuid(uid));}

private:
	QList<METAITEM*> items_;
};

} // Ramio::
