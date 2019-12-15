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

#include "Item.h"

#define HAS_FIELD(TemplateName, FType, FName) \
template<typename T> struct TemplateName { \
private: \
	template<typename U> static decltype(std::declval<U>().FName) detect(const U&); \
	static void detect(...); \
public: \
	static constexpr bool value = std::is_same<FType, decltype(detect(std::declval<T>()))>::value; \
};

HAS_FIELD(has_uuid, QUuid, uuid)

namespace Ramio {

template<typename STRUCTDATA, bool> class StructUUidItem;

template<typename STRUCTDATA>
class StructItem : public Item, public StructUUidItem<STRUCTDATA, has_uuid<STRUCTDATA>::value>
{
public:
	explicit StructItem(ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher) {}
	StructItem(const STRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(data) {}
	StructItem(STRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(std::move(data)) {}
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
	private:
		ItemChanger() = delete;
		ItemChanger(const ItemChanger& ) = delete;
		StructItem<STRUCTDATA>* item_ = Q_NULLPTR;
	public:
		ItemChanger(StructItem::ItemChanger&& changer) {item_ = changer.item_; changer.item_ = Q_NULLPTR;}
		ItemChanger(StructItem<STRUCTDATA>& item) : item_(&item) {item_->beforeChanging();}
		~ItemChanger() {if (item_) item_->afterChanging();}

		StructItem<STRUCTDATA>& item() {return *item_;}
		STRUCTDATA& data() {Q_ASSERT(item_); return item_->data();}
		STRUCTDATA* operator->() {Q_ASSERT(item_); return item_ ? &item_->data() : Q_NULLPTR;}
	};

	ItemChanger changer() {return ItemChanger(*this);}
};

template<typename STRUCTDATA> class StructUUidItem<STRUCTDATA, false> {
};

template<typename STRUCTDATA> class StructUUidItem<STRUCTDATA, true> {

public:
	const RMetaUuid& uuid() const {return static_cast<const StructItem<STRUCTDATA>*>(this)->data().uuid;}
	RMetaString uuidStr() const {return static_cast<const StructItem<STRUCTDATA>*>(this)->data().uuid.toString();}
	void createUuidIfNull() {if (static_cast<StructItem<STRUCTDATA>*>(this)->data().uuid.isNull()) static_cast<StructItem<STRUCTDATA>*>(this)->data().uuid = QUuid::createUuid();}
};



} // Ramio::
