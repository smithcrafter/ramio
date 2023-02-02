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

#include "QueryPackets.h"
#include "ProtocolStr.h"
#include <Items/MetaItemSerialization.h>

namespace Ramio {

void Proto::QPLogin::serialize(Proto::XmlDocument& msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(UsernameAtr, username);
	msg.deParameters.setAttribute(PasswordAtr, password);
}

void Proto::QPLogin::deserialize(const Proto::XmlDocument& msg)
{
	QueryPacket::deserialize(msg);
	username = msg.deParameters.attribute(UsernameAtr);
	password = msg.deParameters.attribute(PasswordAtr);
}

Proto::QPGetDataObject::QPGetDataObject(QString dataSetNameArg, qint64 itemIdArg, qint64 pid)
	: QueryPacket(Queries::GetDataObject, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemId(itemIdArg)
{
}

void Proto::QPGetDataObject::serialize(Proto::XmlDocument& msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(ItemIdAtr, QString::number(itemId));
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
}

void Proto::QPGetDataObject::deserialize(const Proto::XmlDocument& msg)
{
	QueryPacket::deserialize(msg);
	itemId = msg.deParameters.attribute(ItemIdAtr).toInt();
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
}

Proto::QPGetDataSet::QPGetDataSet(qint64 pid, QString dataSetNameArg)
	: QueryPacket(Queries::GetDataSet, pid),
	  dataSetName(std::move(dataSetNameArg))
{
}

void Proto::QPGetDataSet::serialize(Proto::XmlDocument& msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(DataSetChangeNotificationAtr, int(dataSetChangeNotification));

}

void Proto::QPGetDataSet::deserialize(const Proto::XmlDocument& msg)
{
	QueryPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	dataSetChangeNotification = DataSetChangeNotification(msg.deParameters.attribute(DataSetChangeNotificationAtr).toInt());
}

Proto::QPCreateDataObject::QPCreateDataObject(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: QueryPacket(Queries::CreateDataObject, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void Proto::QPCreateDataObject::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	if (dataSetName.isEmpty())
		dataSetName = meta.setName;
	if (itemName.isEmpty())
		itemName = meta.itemName;
	Ramio::Serialization::serialize(meta, data, fields);
}

void Proto::QPCreateDataObject::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void Proto::QPCreateDataObject::serialize(Proto::XmlDocument& msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it !=fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void Proto::QPCreateDataObject::deserialize(const Proto::XmlDocument& msg)
{
	QueryPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		if (!deItem.isNull())
			for (int i = 0; i < deItem.attributes().count(); i++)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
	}
}

Proto::QPSaveDataObject::QPSaveDataObject(QString dataSetNameArg, QString itemNameArg, qint64 pid)
	: QueryPacket(Queries::SaveDataObject, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg))
{
}

void Proto::QPSaveDataObject::createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data)
{
	if (dataSetName.isEmpty())
		dataSetName = meta.setName;
	if (itemName.isEmpty())
		itemName = meta.itemName;
	Ramio::Serialization::serialize(meta, data, fields);
}

void Proto::QPSaveDataObject::updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void Proto::QPSaveDataObject::serialize(Proto::XmlDocument& msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it !=fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void Proto::QPSaveDataObject::deserialize(const Proto::XmlDocument& msg)
{
	QueryPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	if (!itemName.isEmpty())
	{
		QDomElement deItem = msg.deData.firstChildElement(itemName);
		if (!deItem.isNull())
			for (int i = 0; i < deItem.attributes().count(); i++)
				fields.insert(deItem.attributes().item(i).toAttr().name(), deItem.attributes().item(i).toAttr().value());
	}
}

void Proto::QPGetData::serialize(Proto::XmlDocument&) const
{
}

void Proto::QPGetData::deserialize(const Proto::XmlDocument&)
{
}

Proto::QPDeleteDataObject::QPDeleteDataObject(QString dataSetNameArg, QString itemNameArg, QString idArg, QString uuidArg, qint64 pid)
		: QueryPacket(Queries::DeleteDataObject, pid),
		  dataSetName(std::move(dataSetNameArg)),
		  itemName(std::move(itemNameArg)),
		  itemId(std::move(idArg)),
		  itemUuid(std::move(uuidArg))
{
}

void Proto::QPDeleteDataObject::serialize(Proto::XmlDocument &msg) const
{
	QueryPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
	msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
}

void Proto::QPDeleteDataObject::deserialize(const Proto::XmlDocument &msg)
{
	QueryPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
}

} // Ramio::
