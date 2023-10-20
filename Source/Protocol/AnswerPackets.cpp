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

#include "AnswerPackets.h"
#include "ProtocolStr.h"
#include <Items/AbstractMetaSet.h>
#include <Items/MetaItemSerialization.h>

namespace Ramio {

void Proto::APLogin::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(UserIdAtr, userId);
	msg.deParameters.setAttribute(UsernameAtr, name);
	msg.deParameters.setAttribute(UUIDAtr, uuid);
	msg.deParameters.setAttribute(SessionKeyAtr, sessionKey);
}

void Proto::APLogin::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	userId = msg.deParameters.attribute(UserIdAtr);
	name = msg.deParameters.attribute(UsernameAtr);
	uuid = msg.deParameters.attribute(UUIDAtr);
	sessionKey = msg.deParameters.attribute(SessionKeyAtr);
}

Proto::APGetDataObject::APGetDataObject(QString dataSetNameArg, QString itemNameArg, QString idArg, QString uuidArg, qint64 pid)
	: AnswerQueryPacket(Queries::GetDataObject, pid),
	  dataSetName(std::move(dataSetNameArg)),
	  itemName(std::move(itemNameArg)),
	  itemId(std::move(idArg)),
	  itemUuid(std::move(uuidArg))
{
}

void Proto::APGetDataObject::createFromData(const Meta::Description& meta, const ItemData& data)
{
	Ramio::Serialization::serialize(meta, data, fields);
}

void Proto::APGetDataObject::updateData(const Meta::Description& meta, ItemData& data) const
{
	Ramio::Serialization::deserialize(meta, data, fields);
}

void Proto::APGetDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	QDomElement deItem = msg.deData.ownerDocument().createElement(itemName);
	for (auto it = fields.begin(); it !=fields.end(); ++it)
		deItem.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deItem);
}

void Proto::APGetDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
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

Proto::APGetDataSet::APGetDataSet(const AbstractMetaSet& setArg, qint64 pid)
	: AnswerQueryPacket(Queries::GetDataSet, pid), set(&setArg),
	  dataSetName(set->meta().setName)
{
}

void Proto::APGetDataSet::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	if (set)
	{
		const auto& setname = dataSetName.isEmpty() ? set->meta().setName : dataSetName;
		msg.deParameters.setAttribute(DataSetNameAtr, setname);
		QDomElement deSet = msg.deData.ownerDocument().createElement(setname);
		set->serialize(deSet);
		msg.deData.appendChild(deSet);
	}
}

void Proto::APGetDataSet::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
}

void Proto::APCreateDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APCreateDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

void Proto::APSaveDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APSaveDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

void Proto::APDeleteDataObject::serialize(Proto::XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(DataSetNameAtr, dataSetName);
	msg.deParameters.setAttribute(ItemNameAtr, itemName);
	if (!itemUuid.isEmpty())
		msg.deParameters.setAttribute(ItemUuidAtr, itemUuid);
	msg.deParameters.setAttribute(ItemIdAtr, itemId);
}

void Proto::APDeleteDataObject::deserialize(const Proto::XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	dataSetName = msg.deParameters.attribute(DataSetNameAtr);
	itemName = msg.deParameters.attribute(ItemNameAtr);
	itemUuid = msg.deParameters.attribute(ItemUuidAtr);
	itemId = msg.deParameters.attribute(ItemIdAtr);
}

void Proto::APRunAction::serialize(XmlDocument& msg) const
{
	AnswerPacket::serialize(msg);
	msg.deParameters.setAttribute(ActionAtr, action);
	msg.deParameters.setAttribute(SectionAtr, section);
	auto deResult = msg.deData.ownerDocument().createElement(ResultAtr);
	deResult.setAttribute(ResStr, res);
	deResult.setAttribute(DescSrt, desc);
	msg.deData.appendChild(deResult);
	auto deValues = msg.deData.ownerDocument().createElement(ValuesAtr);
	for (auto it = values.begin(); it != values.end(); ++it)
		deValues.setAttribute(it.key(), it.value());
	msg.deData.appendChild(deValues);
}

void Proto::APRunAction::deserialize(const XmlDocument& msg)
{
	AnswerPacket::deserialize(msg);
	action = msg.deParameters.attribute(ActionAtr);
	section = msg.deParameters.attribute(SectionAtr);
	auto deResult = msg.deData.firstChildElement(ResultAtr);
	result.res = deResult.attribute(ResStr).toInt();
	result.desc = deResult.attribute(DescSrt);
	auto deValues  = msg.deData.firstChildElement(ValuesAtr);
	auto attributes = deValues.attributes();
	for (int i = 0; i < attributes.count(); i++)
		values.insert(attributes.item(i).toAttr().name(), attributes.item(i).toAttr().value());
}

} // Ramio::
