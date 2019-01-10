/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

namespace Ramio {

template<typename STRUCITEM>
class FilterItemSet : public AbstractSet
{
	using Base = AbstractSet;
public:
	FilterItemSet(const AbstractSet& originalSet, std::function<bool(const STRUCITEM& t1)> filterFunction, QObject* parent = Q_NULLPTR);

	QList<STRUCITEM*>& items() {return items_;}
	const QList<STRUCITEM*>& items() const {return items_;}

	Item* createItem() const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	Item* createItem(const ItemData& data) const Q_DECL_OVERRIDE {return Q_NULLPTR;}
	AbstractSet* createTemporaryItemSet(QObject* parent = Q_NULLPTR) const Q_DECL_OVERRIDE {return Q_NULLPTR;}

	void reload();

protected:
	void onAdded(const Item& item);
	void onChanged(const Item& item);
	void onRemoved(const Item& item);

private:
	const AbstractSet& set_;
	std::function<bool(const STRUCITEM& t1)> function_;
	QList<STRUCITEM*> items_;
};

} // Ramio::

#include "FilterItemSet.inl"
