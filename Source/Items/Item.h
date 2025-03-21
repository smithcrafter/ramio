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

#include "ItemData.h"
#include <QtCore/QSet>

namespace Ramio {

template<class T> struct RItem2StrucData;
template<class T> struct RContainer2Item;

class Item; struct ItemData;
template<> struct RItem2StrucData<Item> {using type = ItemData;};

template<class Item, typename STRUCTDATA> struct ItemChanger
{
	ItemChanger(ItemChanger&& changer) {item_ = changer.item_; changer.item_ = Q_NULLPTR;}
	ItemChanger(Item& item) : item_(&item) {item_->beforeChanging();}
	~ItemChanger() {if (item_) item_->afterChanging();}

	Item& item() {return *item_;}
	STRUCTDATA& data() {Q_ASSERT(item_); return item_->data();}
	STRUCTDATA* operator->() {Q_ASSERT(item_); return item_ ? &item_->data() : Q_NULLPTR;}

private:
	ItemChanger() = delete;
	ItemChanger(const ItemChanger& ) = delete;
	Item* item_ = Q_NULLPTR;
};

template<class Item, typename STRUCTDATA> struct ItemStateChanger
{
	ItemStateChanger(ItemStateChanger&& changer) {item_ = changer.item_; changer.item_ = Q_NULLPTR;}
	ItemStateChanger(Item& item) : item_(&item) {}
	~ItemStateChanger() {if (item_) item_->stateChanged();}

	Item& item() {return *item_;}
	STRUCTDATA& data() {Q_ASSERT(item_); return item_->data();}
	STRUCTDATA* operator->() {Q_ASSERT(item_); return item_ ? &item_->data() : Q_NULLPTR;}

private:
	ItemStateChanger() = delete;
	ItemStateChanger(const ItemStateChanger& ) = delete;
	Item* item_ = Q_NULLPTR;
};

class ItemObserver;
namespace Meta { struct Description; }

class RAMIO_LIB_EXPORT Item
{
	friend class ItemObserver;
	friend class ItemWatcher;
	friend class DatabaseConnection;
	friend struct ItemChanger<Item, ItemData>;
	friend struct ItemStateChanger<Item, ItemData>;
	Q_DISABLE_COPY(Item)

public:
	Item(ItemData& data_, ItemObserver* watcher = Q_NULLPTR);
	virtual ~Item();

	const RMPKey& id() const {return data_.id;}
	QString idStr() const {return Meta::valueToString<Meta::Type::PKey>(data_.id);}

	ItemData& data() {return data_;}
	const ItemData& data() const {return data_;}

	ItemChanger<Item, ItemData> changer() {return ItemChanger<Item, ItemData>(*this);}
	ItemStateChanger<Item, ItemData> stateChanger() {return ItemStateChanger<Item, ItemData>(*this);}

	virtual qint32 itemType() const {return qint32(0);}
	virtual QString shortDesc() const;

	const QSet<ItemObserver*>& watchers() const {return watchers_;}
	bool addItemWatcher(ItemObserver& watcher);
	bool removeItemWatcher(ItemObserver& watcher);

	virtual void updateMetaDescription(Meta::Description& /*md*/) {}

protected:
	void beforeChanging();
	void afterChanging();
	void stateChanged();
	void beforeDeleted();
	virtual void doAfterChanging() {}

protected:
	ItemData& data_;
	QSet<ItemObserver*> watchers_;
};

} // Ramio::


#define RDECL_CLASS_STRUCT(classname, structname) \
	class classname; struct structname; \
	template<> struct Ramio::RItem2StrucData<classname> {using type = structname;};

#define RDECL_CONTAINER_CLASS(containername, classname) \
	class containername; class classname; \
	template<> struct Ramio::RContainer2Item<containername> {using type = classname;};

#define RDECL_CONTAINER_CLASS_STRUCT(containername, classname, structname) \
	class containername; class classname; struct structname; \
	template<> struct Ramio::RItem2StrucData<classname> {using type = structname;}; \
	template<> struct Ramio::RContainer2Item<containername> {using type = classname;};


#define RDECL_NS_CLASS_STRUCT(classnamespace, classname, structname) \
	namespace classnamespace {class classname; struct structname;} \
	template<> struct Ramio::RItem2StrucData<classnamespace::classname> {using type = classnamespace::structname;};

#define RDECL_NS_CONTAINER_CLASS(classnamespace, containername, classname) \
	namespace classnamespace {class containername; class classname;} \
	template<> struct Ramio::RContainer2Item<classnamespace::containername> {using type = classnamespace::classname;};

#define RDECL_NS_CONTAINER_CLASS_STRUCT(classnamespace, containername, classname, structname) \
	namespace classnamespace {class containername; class classname; struct structname;} \
	template<> struct Ramio::RItem2StrucData<classnamespace::classname> {using type = classnamespace::structname;}; \
	template<> struct Ramio::RContainer2Item<classnamespace::containername> {using type = classnamespace::classname;};
