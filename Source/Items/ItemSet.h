/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "StructItemSet.h"

#define GENERATE_ITEMSET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::ItemSet<CLASS_NAME, STRUCTDATA> \
{ \
typedef ItemSet<CLASS_NAME, STRUCTDATA> Base;	 \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(parent) {} \
};

namespace Ramio {

template<typename ITEM, typename STRUCTDATA>
class ItemSet : public StructItemSet<STRUCTDATA>
{
	Q_DISABLE_COPY(ItemSet)
	using Base = StructItemSet<STRUCTDATA>;
public:
	ItemSet(QObject* parent = Q_NULLPTR) : Base(reinterpret_cast<QList<StructItem<STRUCTDATA>*>&>(items_), parent) {}
	~ItemSet() Q_DECL_OVERRIDE {this->clear();}

	AbstractListSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return new ItemSet(parent);}

	const QList<ITEM*>& items() { return items_; }
	const QList<const ITEM*>& items() const { return items_; }
	virtual ITEM* createItem() const {return new ITEM;}

private:
	QList<ITEM*> items_;
};

} // Ramio::
