/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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
// Qt
#include <QtXml/QDomElement>
#include <QtCore/QDateTime>
#include <QtCore/QMap>

namespace Ramio {

void AbstractMetaSet::serialize(QDomElement& deItems) const
{
	const AbstractMetaSet& metaset = *this;
	const Meta::Description& meta = metaset.meta();
	for (const StructItem<MetaItemData>* item: metaset.items())
	{
		const MetaItemData& data = item->data();
		QDomElement deItem = deItems.ownerDocument().createElement(meta.itemName);
		AbstractMetaSet::serialize(meta, data, deItem);
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
		AbstractMetaSet::deserialize(meta, data, deItem);
		this->addMetaItem(item);
		deItem = deItem.nextSiblingElement(meta.itemName);
	}
}

void AbstractMetaSet::serialize(const Meta::Description& meta, const ItemData& data, QDomElement& deItem)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.relationtype == Meta::FieldType::Extended)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
			if (!value.isEmpty()) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else
			Q_ASSERT(0);
}

void AbstractMetaSet::deserialize(const Meta::Description& meta, ItemData& data, const QDomElement& deItem)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			value = deItem.attribute(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = deItem.attribute(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			value = deItem.attribute(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = deItem.attribute(pr.protoname);
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = deItem.attribute(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			value = RMetaUuid(deItem.attribute(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			value = RMetaTime::fromString(deItem.attribute(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = RMetaDateTime::fromString(deItem.attribute(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = deItem.attribute(pr.protoname).toDouble();
		}
		else
			Q_ASSERT(0);
}

void AbstractMetaSet::serialize(const Meta::Description& meta, const ItemData& data, QMap<QString, QString>& map)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.relationtype == Meta::FieldType::Extended)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
			if (!value.isEmpty()) map.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
			if (value != 0.0) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			if (!value.isNull()) map.insert(pr.protoname, value.toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			if (value != 0.0) map.insert(pr.protoname, QString::number(value));
		}
		else
			Q_ASSERT(0);
}

void AbstractMetaSet::deserialize(const Meta::Description& meta, ItemData& data, const QMap<QString, QString>& map)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			value = map.value(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = map.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			value = map.value(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = map.value(pr.protoname);
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = map.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			value = RMetaUuid(map.value(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			value = RMetaTime::fromString(map.value(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = RMetaDateTime::fromString(map.value(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = map.value(pr.protoname).toDouble();
		}
		else
			Q_ASSERT(0);
}

void AbstractMetaSet::setRelationSet(const QString& name, AbstractMetaSet* set)
{
	 metaDescription_.setRelation(name, set ? &set->meta() : Q_NULLPTR);
	 relations_[name] = set;
}

AbstractMetaSet::~AbstractMetaSet() = default;

} // Ramio::
