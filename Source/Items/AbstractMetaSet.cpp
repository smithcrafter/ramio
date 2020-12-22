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

#include "AbstractMetaSet.h"
#include "MetaItemSerialization.h"
// Qt5
#include <QtXml/QDomElement>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace Ramio {

void AbstractMetaSet::serialize(QDomElement& deItems) const
{
	const AbstractMetaSet& metaset = *this;
	const Meta::Description& meta = metaset.meta();
	for (const auto* item: metaset.metaItems())
	{
		const MetaItemData& data = item->data();
		QDomElement deItem = deItems.ownerDocument().createElement(meta.itemName);
		Meta::serialize(meta, data, deItem);
		deItems.appendChild(deItem);
	}
}

void AbstractMetaSet::deserialize(const QDomElement& deItems)
{
	const Meta::Description& meta = this->meta();
	QDomElement deItem = deItems.firstChildElement(meta.itemName);
	while (!deItem.isNull())
	{
		StructItem<MetaItemData>* item = this->createMetaItem();
		MetaItemData& data = item->data();
		Meta::deserialize(meta, data, deItem);
		this->insertMetaItem(item);
		deItem = deItem.nextSiblingElement(meta.itemName);
	}
}

void AbstractMetaSet::serialize(QJsonArray& jArray) const
{
	const AbstractMetaSet& metaset = *this;
	const Meta::Description& meta = metaset.meta();
	for (const auto* item: metaset.metaItems())
	{
		const MetaItemData& data = item->data();
		QJsonObject object;
		Meta::serialize(meta, data, object);
		jArray.append(object);
	}
}

void AbstractMetaSet::deserialize(const QJsonArray& jArray)
{
	const AbstractMetaSet& metaset = *this;
	const Meta::Description& meta = metaset.meta();
	for (const QJsonValue& value: jArray)
	{
		Q_ASSERT(value.isObject());

		StructItem<MetaItemData>* item = this->createMetaItem();
		MetaItemData& data = item->data();
		Meta::deserialize(meta, data, value.toObject());
		this->insertMetaItem(item);
	}
}

void AbstractMetaSet::setRelationSet(const QString& name, const AbstractMetaSet* set)
{
	 meta_.setRelation(name, set ? &set->meta() : Q_NULLPTR);
	 relations_[name] = set;
}

void AbstractMetaSet::setRelationSets(const QMap<QString, const AbstractMetaSet*>& relations)
{
	for (auto it = relations.begin(); it != relations.end(); ++it)
		setRelationSet(it.key(), it.value());
}

AbstractMetaSet::~AbstractMetaSet() = default;


} // Ramio::
