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

#include "BaseListSet.h"

namespace Ramio {

template<typename STRUCTITEM>
class FilterItemSet : public BaseListSet<STRUCTITEM, typename Ramio::RItem2StrucData<STRUCTITEM>::type>
{
	using Base = BaseListSet<STRUCTITEM, typename RItem2StrucData<STRUCTITEM>::type>;
public:
	FilterItemSet(const AbstractListSet& originalSet, std::function<bool(const STRUCTITEM& t1)> filterFunction, QObject* parent = Q_NULLPTR);

	const QList<STRUCTITEM*>& items() {return items_;}
	const QList<const STRUCTITEM*>& items() const {
		return reinterpret_cast<const QList<const STRUCTITEM*>&>(const_cast<FilterItemSet*>(this)->items());}

	AbstractListSet* createTemporaryItemSet(QObject* = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}

	void reload();

protected:
	void onAdded(const Item& item);
	void onChanged(const Item& item);
	void onRemoved(const Item& item);

private:
	const AbstractListSet& set_;
	std::function<bool(const STRUCTITEM& t1)> function_;
	QList<STRUCTITEM*> items_;
};

} // Ramio::

#include "FilterItemSet.inl"
