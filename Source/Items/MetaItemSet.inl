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

#include "MetaItemSet.h"

namespace Ramio {

template<typename METAITEM, typename METASTRUCTDATA, bool CACHEDID, bool CACHEDUUID>
MetaItemSet<METAITEM, METASTRUCTDATA, CACHEDID, CACHEDUUID>::MetaItemSet
		(QString setName, QString itemName, std::unique_ptr<Meta::TypeDescription> typeDescription, QObject* parent)
	: Base(reinterpret_cast<QList<StructItem<METASTRUCTDATA>*>&>(this->items()), parent),
	  AbstractMetaSet(reinterpret_cast<QList<StructItem<MetaItemData>*>&>(this->items()))
{
	meta_.itemName = std::move(itemName);
	meta_.setName = std::move(setName);
	meta_.size = sizeof(METASTRUCTDATA);
	meta_.typeDescription = std::move(typeDescription);
	meta_.properties = METASTRUCTDATA().registerMetaFields();
}

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
