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

#include "StructItemSet.h"

/**
 * Основной макрос геренерации списка.
 *
 */
#define GENERATE_CLASS_SET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::ItemSet<STRUCTDATA> \
{ \
typedef ItemSet<STRUCTDATA> Base;	 \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(parent) {} \
	const QList<CLASS_NAME*>& items() { return reinterpret_cast<const QList<CLASS_NAME*>& >(Base::items()); } \
	const QList<const CLASS_NAME*>& items() const { return reinterpret_cast<const QList<const CLASS_NAME*>& >(Base::items()); } \
	virtual CLASS_NAME* createItem() const {return new CLASS_NAME;} \
};

namespace Ramio {

template<typename STRUCTDATA>
class ItemSet : public StructItemSet<STRUCTDATA>
{
	Q_DISABLE_COPY(ItemSet)
	using Base = StructItemSet<STRUCTDATA>;
public:
	ItemSet(QObject* parent = Q_NULLPTR) : Base(items_, parent) {}
	~ItemSet() {this->clear();}

	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return new ItemSet(parent);}

private:
	QList<StructItem<STRUCTDATA>*> items_;
};

} // Ramio::
