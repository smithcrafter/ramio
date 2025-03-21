/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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

#include "StructItemTemplates.h"

namespace Ramio {

template<typename STRUCTDATA>
class StructItem : public Item, public StructItemCheckUUid<StructItem<STRUCTDATA>, STRUCTDATA>
{
	friend struct ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA>;
public:
	explicit StructItem(ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher) {}
	StructItem(const STRUCTDATA& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(data) {}
	StructItem(STRUCTDATA&& data, ItemObserver* watcher = Q_NULLPTR) : Item(data_, watcher), data_(std::move(data)) {}
	~StructItem() Q_DECL_OVERRIDE { if (!watchers_.isEmpty()) this->beforeDeleted(); }

	STRUCTDATA& data() {return data_;}
	const STRUCTDATA& data() const {return data_;}

	void updateData(const STRUCTDATA& data) {beforeChanging(); data_ = data; afterChanging();}

	ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA> changer() {return ItemChanger<StructItem<STRUCTDATA>, STRUCTDATA>(*this);}
	ItemStateChanger<StructItem<STRUCTDATA>, STRUCTDATA> stateChanger() {return ItemStateChanger<StructItem<STRUCTDATA>, STRUCTDATA>(*this);}

private:
	STRUCTDATA data_;
};

} // Ramio::
