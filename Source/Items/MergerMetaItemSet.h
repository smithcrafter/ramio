/*
 * Copyright (C) 2016-2020 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MergerItemSet.h"
#include "AbstractMetaSet.h"

namespace Ramio {

template<typename STRUCTITEM>
class MergerMetaItemSet : public MergerItemSet<STRUCTITEM>, public AbstractMetaSet
{
public:
	MergerMetaItemSet(const AbstractSet& set1, const AbstractSet& set2, QObject* parent = Q_NULLPTR)
		: MergerItemSet<STRUCTITEM>(set1, set2, parent),
		  AbstractMetaSet(reinterpret_cast<const QList<const StructItem<MetaItemData>*>&>(MergerItemSet<STRUCTITEM>::items())) {}

	MergerMetaItemSet(const AbstractMetaSet& set1, const AbstractMetaSet& set2, QObject* parent = Q_NULLPTR)
		: MergerItemSet<STRUCTITEM>(*set1.aSet(), *set2.aSet(), parent),
		  AbstractMetaSet(reinterpret_cast<const QList<const StructItem<MetaItemData>*>&>(MergerItemSet<STRUCTITEM>::items()), set1.meta(), set1.relations()) {}

	STRUCTITEM* createItem() const Q_DECL_OVERRIDE {return new STRUCTITEM();}
	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE  {return Q_NULLPTR;}
	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE  {return Q_NULLPTR;}
	void insertMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {}
	AbstractSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
};

template<typename STRUCTITEM>
class MultiMergerMetaItemSet : public MultiMergerItemSet<STRUCTITEM>, public AbstractMetaSet
{
public:
	MultiMergerMetaItemSet(QList<const AbstractSet*> sets, QObject* parent = Q_NULLPTR)
		: MultiMergerItemSet<STRUCTITEM>(sets, parent),
		  AbstractMetaSet(reinterpret_cast<const QList<const StructItem<MetaItemData>*>&>(MultiMergerItemSet<STRUCTITEM>::items())) {}

/*	MultiMergerMetaItemSet(QList<const AbstractMetaSet*> sets, QObject* parent = Q_NULLPTR)
		: MultiMergerItemSet<STRUCTITEM>(*reinterpret_cast<QList<const AbstractSet*>*>(&sets), parent),
		  AbstractMetaSet(reinterpret_cast<const QList<const StructItem<MetaItemData>*>&>(MultiMergerItemSet<STRUCTITEM>::items()), set1.meta(), set1.relations()) {}
*/
	STRUCTITEM* createItem() const Q_DECL_OVERRIDE {return new STRUCTITEM();}
	StructItem<MetaItemData>* createMetaItem() const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const Q_DECL_OVERRIDE  {return Q_NULLPTR;}
	MetaItemData* createMetaItemData() const Q_DECL_OVERRIDE  {return Q_NULLPTR;}
	void insertMetaItem(StructItem<MetaItemData>* item) Q_DECL_OVERRIDE {}
	AbstractSet* aSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* mSet() Q_DECL_OVERRIDE {return this;}
	AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
};

} // Ramio::

#include "MergerMetaItemSet.inl"
