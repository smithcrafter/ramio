/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "StructItem.h"
#include "AbstractListSet.h"
#include "MetaDescription.h"

namespace Ramio {

template<int SIZE>
struct ReflData : public ItemData
{
	RMByte subdata[SIZE];
};

template<int SIZE>
class ReflItem : public StructItem<ReflData<SIZE>>
{
	typedef ReflData<SIZE> Data;
	typedef StructItem<ReflData<SIZE>> Base;
public:
	ReflItem() : Base() {}
	ReflItem(const Data& data) : Base(data) {}
};

class ReflSet : public AbstractListSet
{
public:
	ReflSet(const Meta::Description& meta, QObject* parent = Q_NULLPTR);

	const Meta::Description& meta() const {return meta_;}

	virtual Item* createItem() const;
	virtual Item* createItem(const ItemData& data) const {Q_UNUSED(data); return Q_NULLPTR;}
	virtual Item* createItem(ItemData&& data) const {Q_UNUSED(data); return Q_NULLPTR;}
	virtual AbstractListSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const {Q_UNUSED(parent); return Q_NULLPTR;}

private:
	QList<Item*> items_;
	Meta::Description meta_;
};

} // Ramio::
