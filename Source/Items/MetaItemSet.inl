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

#include "MetaItemSet.h"

namespace Ramio {

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID>
MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID>::MetaItemSet
		(QString setName, QString itemName, std::unique_ptr<Meta::TypeDescription> typeDescription, QObject* parent)
	: Base(reinterpret_cast<QList<StructItem<METASTRUCTDATA>*>&>(const_cast<QList<METAITEM*>&>(this->items())), parent),
	  AbstractMetaSet(reinterpret_cast<const QList<const StructItem<MetaItemData>*>&>(this->asConst().items()))
{
	meta_.itemName = std::move(itemName);
	meta_.setName = std::move(setName);
	meta_.size = sizeof(METASTRUCTDATA);
	meta_.typeDescription = std::move(typeDescription);
	meta_.properties = METASTRUCTDATA().registerMetaFields();
}

template<typename TYPE, typename METAITEMSET, typename METAITEM> struct CacheMapStruct<TYPE, METAITEMSET, METAITEM, false>
{
	typedef METAITEM* (METAITEMSET::* findfunc)(TYPE id);
	inline void add(TYPE, METAITEM*) {}
	inline void remove(TYPE){}
	inline METAITEM* findItem(TYPE id, findfunc f, METAITEMSET& set) {return (set.*f)(id);}
};

template<typename TYPE, typename METAITEMSET, typename METAITEM> struct CacheMapStruct<TYPE, METAITEMSET, METAITEM, true>
{
	QMap<remove_const_reference_t(TYPE), METAITEM*> map;
	typedef METAITEM* (METAITEMSET::* findfunc)(TYPE id);
	inline void add(TYPE id, METAITEM* item) {map.insert(id, item);}
	inline void remove(TYPE id) {map.remove(id);}
	inline METAITEM* findItem(TYPE id, findfunc, METAITEMSET&) {return map[id];}
};

} // Ramio::
