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

#define FIELD_DETECTOR(FieldDetetorName, FType, FName) \
template<typename T> struct FieldDetetorName { \
private: \
	template<typename U> static decltype(std::declval<U>().FName) detect(const U&); \
	static void detect(...); \
public: \
	static constexpr bool value = std::is_same<FType, decltype(detect(std::declval<T>()))>::value; \
};

namespace Ramio {

template<typename STRUCTDATA, bool> class StructUUidItem;
FIELD_DETECTOR(has_uuid, QUuid, uuid)

template<typename STRUCTDATA>
class StructItem : public Item, public StructUUidItem<STRUCTDATA, has_uuid<STRUCTDATA>::value>
{
	friend struct ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA>;
public:
	explicit StructItem(ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher) {}
	StructItem(const STRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(data) {}
	StructItem(STRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(std::move(data)) {}
	~StructItem() Q_DECL_OVERRIDE { this->beforeDeleted(); }

	STRUCTDATA& data() {return data_;}
	const STRUCTDATA& data() const {return data_;}

	ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA> changer() {return ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA>(*this);}
	void updateData(const STRUCTDATA& data) {beforeChanging(); data_ = data; afterChanging();}

private:
	STRUCTDATA data_;
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
