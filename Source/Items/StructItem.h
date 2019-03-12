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

#include "Item.h"

namespace Ramio {

template<typename STRUCTDATA>
class StructItem : public Item
{
public:
	explicit StructItem(ItemObserver* watcher = Q_NULLPTR)
		: Item(data_.id, data_.type, data_.uuid, watcher) {}
	StructItem(const STRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR)
		: Item(data_.id, data_.type, data_.uuid, watcher), data_(data) {}
	StructItem(STRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR)
		: Item(data_.id, data_.type, data_.uuid, watcher), data_(std::move(data)) {}
	~StructItem() Q_DECL_OVERRIDE { this->beforeDeleted(); }

	STRUCTDATA& data() Q_DECL_OVERRIDE {return data_;}
	const STRUCTDATA& data() const Q_DECL_OVERRIDE {return data_;}

	void updateData(const STRUCTDATA& data) {beforeChanging(); data_ = data; afterChanging();}

private:
	STRUCTDATA data_;

	friend struct ItemChanger;
public:
	struct ItemChanger
	{
		ItemChanger() = delete;
		ItemChanger(const ItemChanger& ) = delete;
		StructItem<STRUCTDATA>* item_ = Q_NULLPTR;
	public:
		ItemChanger(StructItem::ItemChanger&& changer) {item_ = changer.item_; changer.item_ = Q_NULLPTR;}
		ItemChanger(StructItem<STRUCTDATA>& item) : item_(&item) {}
		~ItemChanger() {if (item_) item_->afterChanging();}

		StructItem<STRUCTDATA>& item() {return *item_;}
		STRUCTDATA& data() {Q_ASSERT(item_); return item_->data();}
		STRUCTDATA* operator->() {Q_ASSERT(item_); return item_ ? &item_->data() : Q_NULLPTR;}
	};

	ItemChanger changer() {beforeChanging(); return ItemChanger(*this);}
};

} // Ramio::
