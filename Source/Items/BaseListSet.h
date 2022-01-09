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

#include "AbstractListSet.h"

namespace Ramio {

template<typename ITEM, typename STRUCTDATA, bool> class BaseListSetItemCreator;

template<typename ITEM, typename STRUCTDATA>
class BaseListSet : public AbstractListSet, public BaseListSetItemCreator<ITEM, STRUCTDATA, std::is_constructible<ITEM>::value>
{
	typedef BaseListSetItemCreator<ITEM, STRUCTDATA, std::is_constructible<ITEM>::value> BaseCreator;
public:
	BaseListSet(QList<ITEM*>& items, QObject* parent = Q_NULLPTR)
		: AbstractListSet(reinterpret_cast<QList<Item*>&>(items), parent) {}
	~BaseListSet() Q_DECL_OVERRIDE = default;

	const QList<ITEM*>& items() Q_DECL_NOTHROW { return reinterpret_cast<const QList<ITEM*>&>(AbstractListSet::items()); }
	const QList<const ITEM*>& items() const Q_DECL_NOTHROW { return reinterpret_cast<const QList<const ITEM*>&>
				(const_cast<BaseListSet*>(this)->items());}

	inline typename QList<ITEM*>::const_iterator begin() Q_DECL_NOTHROW {return items().begin();}
	inline typename QList<ITEM*>::const_iterator end() Q_DECL_NOTHROW {return items().end();}
	inline typename QList<const ITEM*>::const_iterator begin() const Q_DECL_NOTHROW {return items().begin();}
	inline typename QList<const ITEM*>::const_iterator end() const Q_DECL_NOTHROW {return items().end();}

	ITEM* createItem() const Q_DECL_OVERRIDE {return BaseCreator::createItem();}
	ITEM* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return BaseCreator::createItem(data);}
	ITEM* createItem(ItemData&& data) const Q_DECL_OVERRIDE {return BaseCreator::createItem(data);}

};

} // Ramio::

#include "BaseListSet.inl"
