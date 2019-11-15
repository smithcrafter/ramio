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

#include "ItemObserver.h"

namespace Ramio {

class DLL_EXPORT ItemWatcher : public ItemObserver
{
	Q_DISABLE_COPY(ItemWatcher)
public:
	ItemWatcher(Item* item = Q_NULLPTR, QObject* parent = Q_NULLPTR);
	~ItemWatcher() Q_DECL_OVERRIDE;

	Item* item() {return item_;}
	const Item* item() const {return item_;}
	void setItem(Item* item);

	bool contains(const Item& item) const Q_DECL_OVERRIDE {return &item == item_;}
	int count() const Q_DECL_OVERRIDE {return item_ ? 1 : 0;}
	bool isEmpty() const Q_DECL_OVERRIDE {return !item_;}
	void clear() Q_DECL_OVERRIDE {setItem(Q_NULLPTR);}

private:
	void doOnItemAdding(Item&) Q_DECL_OVERRIDE {}
	void doOnItemChanging(Item&) Q_DECL_OVERRIDE {}
	void doOnItemChanged(Item&) Q_DECL_OVERRIDE {}
	void doOnItemRemoving(Item& item) Q_DECL_OVERRIDE;

private:
	Item* item_ = Q_NULLPTR;
};

} // Ramio::
