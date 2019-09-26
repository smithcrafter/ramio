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

#include "ItemData.h"
#include <QtCore/QSet>

namespace Ramio {

class ItemObserver;

class DLL_EXPORT Item
{
	friend class ItemObserver;
	friend class ItemWatcher;
	friend class Database;
	Q_DISABLE_COPY(Item)
public:
	Item(RMetaPKey& id, RMetaInt& type, RMetaUuid& uuid, ItemObserver* watcher = Q_NULLPTR);
	virtual ~Item();

	virtual qint32 itemType() const  {return qint32(0);}
	const RMetaPKey& id() const {return id_;}
	const RMetaInt& type() const {return type_;}
	const RMetaUuid& uuid() const {return uuid_;}
	RMetaString uuidStr() const {return uuid_.toString();}
	void createUuidIfNull() {if (uuid_.isNull()) uuid_ = QUuid::createUuid();}
	virtual ItemData& data() = 0;
	virtual const ItemData& data() const = 0;

	virtual QString shortDesc() const;

	const QSet<ItemObserver*> watchers() const {return watchers_;}
	bool addItemWatcher(ItemObserver& watcher);
	bool removeItemWatcher(ItemObserver& watcher);

protected:
	void beforeChanging();
	void afterChanging();
	void beforeDeleted();

	virtual void doAfterChanging() {}

private:
	RMetaPKey& id_;
	RMetaInt& type_;
	RMetaUuid& uuid_;
	QSet<ItemObserver*> watchers_;
};

} // Ramio::
