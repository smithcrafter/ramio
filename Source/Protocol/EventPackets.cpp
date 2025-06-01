/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "EventPackets.h"
#include "ProtocolStr.h"
#include <Items/MetaItemSerialization.h>

namespace Ramio {
namespace Proto {

EPDataObjectCreated::EPDataObjectCreated(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: EventPacket(Events::DataObjectCreated, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void EPDataObjectCreated::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	itemId = QString::number(data.id);
	if (auto uuiddiff = meta.fieldDiff("uuid", Ramio::Meta::Type::Uuid))
		if (!data.field<RMUuid>(uuiddiff).isNull())
			itemUuid = data.field<RMUuid>(uuiddiff).toString();
	Ramio::Serialization::serialize(meta, data, fields);
}

void EPDataObjectCreated::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void EPDataObjectCreated::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it != fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void EPDataObjectCreated::deserialize(const XmlDocument& msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);

	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		if (!deItem.isNull())
			for (int i = 0; i < deItem.attributes().count(); ++i)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
	}
}

EPDataObjectsCreated::EPDataObjectsCreated(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: EventPacket(Events::DataObjectsCreated, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void EPDataObjectsCreated::appendFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	QMap<QString, QString> fields;
	Ramio::Serialization::serialize(meta, data, fields);
	fieldsList.append(fields);
}

void EPDataObjectsCreated::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data, int index) const
{
	Ramio::Serialization::deserialize(meta, data, fieldsList[index]);
}

void EPDataObjectsCreated::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	for (auto& fields: fieldsList)
	{
		QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
		for (auto it = fields.begin(); it != fields.end(); ++it)
			deItem.setAttribute(it.key(), it.value());
		msg.deData.appendChild(deItem);
	}
}

void EPDataObjectsCreated::deserialize(const XmlDocument& msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);


	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		while (!deItem.isNull())
		{
			QMap<QString, QString> fields;
			for (int i = 0; i < deItem.attributes().count(); ++i)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
			fieldsList.append(fields);
			deItem = deItem.nextSiblingElement(itemName);
		}
	}
}

EPDataObjectChanged::EPDataObjectChanged(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: EventPacket(Events::DataObjectChanged, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void EPDataObjectChanged::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	itemId = QString::number(data.id);
	if (auto uuiddiff = meta.fieldDiff("uuid", Ramio::Meta::Type::Uuid))
		if (!data.field<RMUuid>(uuiddiff).isNull())
			itemUuid = data.field<RMUuid>(uuiddiff).toString();
	Ramio::Serialization::serialize(meta, data, fields);
}

void EPDataObjectChanged::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void EPDataObjectChanged::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it != fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void EPDataObjectChanged::deserialize(const XmlDocument& msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		if (!deItem.isNull())
			for (int i = 0; i < deItem.attributes().count(); ++i)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
	}
}


EPDataObjectsChanged::EPDataObjectsChanged(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: EventPacket(Events::DataObjectsChanged, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void EPDataObjectsChanged::appendFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	QMap<QString, QString> fields;
	Ramio::Serialization::serialize(meta, data, fields);
	fieldsList.append(fields);
}

void EPDataObjectsChanged::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data, int index) const
{
	Ramio::Serialization::deserialize(meta, data, fieldsList[index]);
}

void EPDataObjectsChanged::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	for (auto& fields: fieldsList)
	{
		QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
		for (auto it = fields.begin(); it != fields.end(); ++it)
			deItem.setAttribute(it.key(), it.value());
		msg.deData.appendChild(deItem);
	}
}

void EPDataObjectsChanged::deserialize(const XmlDocument& msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		while (!deItem.isNull())
		{
			QMap<QString, QString> fields;
			for (int i = 0; i < deItem.attributes().count(); ++i)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
			fieldsList.append(fields);
			deItem = deItem.nextSiblingElement(itemName);
		}
	}
}


EPDataObjectDeleted::EPDataObjectDeleted(QString dataSetNameArg, QString itemNameArg, QString idArg, QString uuidArg, qint64 pid)
	: EventPacket(Events::DataObjectDeleted, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg)),
	  itemId(std::move(idArg)),
	  itemUuid(std::move(uuidArg))
{
}

void EPDataObjectDeleted::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
}

void EPDataObjectDeleted::deserialize(const XmlDocument &msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
}

EPDataObjectsDeleted::EPDataObjectsDeleted(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: EventPacket(Events::DataObjectsDeleted, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void EPDataObjectsDeleted::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	for (auto& pair: itemIdUUid)
	{
		QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
		deItem.setAttribute(ItemIdAtr, pair.first);
		if (!pair.second.isEmpty())
			deItem.setAttribute(ItemUuidAtr, pair.second);
		msg.deData.appendChild(deItem);
	}
}

void EPDataObjectsDeleted::deserialize(const XmlDocument &msg)
{
	EventPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		while (!deItem.isNull())
		{
			QPair<QString, QString> pair;
			pair.first = deItem.attribute(ItemIdAtr);
			pair.second = deItem.attribute(ItemUuidAtr);
			itemIdUUid.append(pair);
			deItem = deItem.nextSiblingElement(itemName);
		}
	}
}

} // Proto::
} // Ramio::
