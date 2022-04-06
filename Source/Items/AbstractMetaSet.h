/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
class QJsonArray;
class QObject;

namespace Ramio {

namespace Serialization { struct Options; extern const Options& standardOptions();}

class AbstractListSet;

class RAMIO_LIB_EXPORT AbstractMetaSet
{
public:
	const Meta::Description& meta() const { return meta_; }
	Meta::Description& meta() { return meta_; }

	const QList<StructItem<MetaItemData>*>& metaItems() {
		return reinterpret_cast<const QList<StructItem<MetaItemData>*>&>(const_cast<const AbstractMetaSet*>(this)->metaItems());}
	const QList<const StructItem<MetaItemData>*>& metaItems() const {return metaItems_;}

	virtual StructItem<MetaItemData>* createMetaItem() const = 0;
	virtual StructItem<MetaItemData>* createMetaItem(const MetaItemData& data) const = 0;
	virtual MetaItemData* createMetaItemData() const = 0;
    void insertMetaItem(Item* item) {insertMetaItem(static_cast<StructItem<MetaItemData>*>(item));}
	virtual void insertMetaItem(StructItem<MetaItemData>* item) = 0;

	virtual void serializeItem(QDomElement& deItem, const StructItem<MetaItemData>& item, const Serialization::Options& options = Serialization::standardOptions()) const;
	virtual void deserializeItem(QDomElement& deItem, StructItem<MetaItemData>& item) const;

	void serialize(QDomElement& deItems, const Serialization::Options& options = Serialization::standardOptions()) const;
	virtual void deserialize(const QDomElement& deItems);

	void serialize(QJsonArray& jArray, const Serialization::Options& options = Serialization::standardOptions()) const;
	virtual void deserialize(const QJsonArray& jArray);

	virtual AbstractListSet* aSet() = 0;
	const AbstractListSet* aSet() const {return  const_cast<AbstractMetaSet*>(this)->aSet();}
	virtual AbstractMetaSet* createTemporaryMetaSet(QObject* parent = Q_NULLPTR) const = 0;

	const QMap<QString, const AbstractMetaSet*>& relations() const {return relations_;}
	void setRelationSet(const QString& name, const AbstractMetaSet* set);
	void setRelationSets(const QMap<QString, const AbstractMetaSet*>& relations);

protected:
	AbstractMetaSet(const QList<const StructItem<MetaItemData>*>& items) : metaItems_(items) {}
	AbstractMetaSet(const QList<const StructItem<MetaItemData>*>& items,
					const Meta::Description& meta, const QMap<QString, const AbstractMetaSet*>& relations)
		: metaItems_(items), meta_(meta), relations_(relations) {}

public:
	virtual ~AbstractMetaSet();

protected:
	const QList<const StructItem<MetaItemData>*>& metaItems_;
	Meta::Description meta_;
	QMap<QString, const AbstractMetaSet*> relations_;
};

} // Ramio::
