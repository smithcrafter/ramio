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

#include "EventPackets.h"
#include "ProtocolStr.h"
#include <Items/MetaItemSerialization.h>

namespace Ramio {
namespace Proto {

EPDataObjectCreated::EPDataObjectCreated(QString v_dataSetName, QString v_itemName, qint64 pid)
	: EventPacket(Events::DataObjectCreated, pid),
	  dataSetName(std::move(v_dataSetName)),
	  itemName(std::move(v_itemName))
{
}

void EPDataObjectCreated::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	itemId = QString::number(data.id);
	if (auto uuiddiff = meta.fieldDiff("uuid", Ramio::Meta::Type::Uuid))
		itemUuid = data.field<RMUuid>(uuiddiff).toString();
	Ramio::Meta::serialize(meta, data, fields);
}

void EPDataObjectCreated::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Meta::deserialize(meta, data, fields);
}

void EPDataObjectCreated::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
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

EPDataObjectChanged::EPDataObjectChanged(QString v_dataSetName, QString v_itemName, qint64 pid)
	: EventPacket(Events::DataObjectChanged, pid),
	  dataSetName(std::move(v_dataSetName)),
	  itemName(std::move(v_itemName))
{
}

void EPDataObjectChanged::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	itemId = QString::number(data.id);
	if (auto uuiddiff = meta.fieldDiff("uuid", Ramio::Meta::Type::Uuid))
		itemUuid = data.field<RMUuid>(uuiddiff).toString();
	Ramio::Meta::serialize(meta, data, fields);
}

void EPDataObjectChanged::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Meta::deserialize(meta, data, fields);
}

void EPDataObjectChanged::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
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

EPDataObjectDeleted::EPDataObjectDeleted(QString v_dataSetName, QString v_itemName, QString v_id, QString v_uuid, qint64 pid)
	: EventPacket(Events::DataObjectDeleted, pid),
	  dataSetName(std::move(v_dataSetName)),
	  itemName(std::move(v_itemName)),
	  itemId(std::move(v_id)),
	  itemUuid(std::move(v_uuid))
{
}

void EPDataObjectDeleted::serialize(XmlDocument& msg) const
{
	EventPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
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

} // Proto::
} // Ramio::
