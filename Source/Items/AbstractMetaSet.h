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

#include "MetaItemData.h"
#include "StructItem.h"
class QDomElement;
class QJsonObject;
class QObject;

namespace Ramio {

class AbstractSet;

class DLL_EXPORT AbstractMetaSet
{
public:
	const Meta::Description& meta() const { return meta_; }

	QList<StructItem<MetaItemData>*>& items() {return metaitems_;}
	const QList<StructItem<MetaItemData>*>& items() const {return metaitems_;}
	virtual StructItem<MetaItemData>* createMetaItem() const = 0;
	virtual StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const = 0;
	virtual MetaItemData* createMetaItemData() const = 0;
	virtual void addMetaItem(StructItem<MetaItemData>* item) = 0;

	void serialize(QDomElement& deItems) const;
	void deserialize(const QDomElement& deItems);

	static void serialize(const Meta::Description& meta, const ItemData& data, QDomElement& deItem);
	static void deserialize(const Meta::Description& meta, ItemData& data, const QDomElement& deItem);

	static void serialize(const Meta::Description& meta, const ItemData& data, QMap<QString, QString>& map);
	static void deserialize(const Meta::Description& meta, ItemData& data, const QMap<QString, QString>& map);

	static void serialize(const Meta::Description& meta, const ItemData& data, QJsonObject& jsObject);
	static void deserialize(const Meta::Description& meta, ItemData& data, const QJsonObject& jsObject);

	virtual AbstractSet* aSet() = 0;
	const AbstractSet* aSet() const {return  const_cast<AbstractMetaSet*>(this)->aSet();}
	virtual AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const = 0;

	const QMap<QString, const AbstractMetaSet*>& relations() const {return relations_;}
	void setRelationSet(const QString& name, AbstractMetaSet* set);

protected:
	AbstractMetaSet(QList<StructItem<MetaItemData>*>& items) : metaitems_(items) {}

public:
	virtual ~AbstractMetaSet() = default;

protected:
	QList<StructItem<MetaItemData>*>& metaitems_;
	Meta::Description meta_;
	QMap<QString, const AbstractMetaSet*> relations_;
};

} // Ramio::
