/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MetaItemSerialization.h"
// Qt5
#include <QtXml/QDomElement>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDateTime>
#include <QtCore/QIODevice>
#include <QtCore/QMap>
#include <QtEndian>

namespace Ramio {

namespace Serialization {

void serialize(const Meta::Description& meta, const ItemData& data, QDomElement& deItem, const Options& options)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (!options.options.isEmpty() && options.fieldOptionByName(pr.name) && options.skipByOptions(pr, data))
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Type)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMType);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::State)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMState);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Flags)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFlags);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMBool);
			if (value) deItem.setAttribute(pr.protoname, int(value));
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMChar);
			if (value) deItem.setAttribute(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUShort);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUInt);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMLong);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMULong);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFloat);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDouble);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMStdString);
			if (!value.empty()) deItem.setAttribute(pr.protoname, QString::fromStdString(value));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMString);
			if (!value.isEmpty()) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUuid);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(QUuid::WithoutBraces));
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDate);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, QString(value.toBase64()));
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByte);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
			if (value != 0.0) deItem.setAttribute(pr.protoname, QString::number((value+(value > 0 ? 1 : -1)*0.000001), 'f', 2));
		}
		else if (pr.type == Meta::Type::RecordPrtList)
		{
			if (meta.relations[pr.name])
			{
				auto& recptrlist = (*reinterpret_cast<const QList<const BaseItemData*>*>(reinterpret_cast<const std::byte*>(&data)+pr.diff));
				QDomElement deSubSet = deItem.ownerDocument().createElement(pr.protoname);
				deItem.appendChild(deSubSet);
				const QString& itemTag = meta.relations[pr.name]->itemName;
				for (auto rec: recptrlist)
				{
					QDomElement deSubItem = deSubSet.ownerDocument().createElement(itemTag);
					serialize(*meta.relations[pr.name], *rec, deSubItem);
					deSubSet.appendChild(deSubItem);
				}
			}
		}
		else if(pr.type == Meta::Type::PKeyList)
		{
			if (meta.relations[pr.name])
			{
				const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKeyList);
				QDomElement deList = deItem.ownerDocument().createElement(pr.protoname);
				deItem.appendChild(deList);
				const QString idtag = meta.relations[pr.name]->properties[0].protoname;
				for (auto id : value)
				{
					QDomElement deListItem = deItem.ownerDocument().createElement(pr.special);
					deListItem.setAttribute(idtag, id);
					deList.appendChild(deListItem);
				}
			}
		}
		else
			Q_ASSERT_X(0, "serialize", qPrintable(QString("Type \"%1\" not supported").arg(Meta::typeName(pr.type))));
}

void deserialize(const Meta::Description& meta, ItemData& data, const QDomElement& deItem)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMPKey);
			value = deItem.attribute(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Type)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMType);
			value = deItem.attribute(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::State)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMState);
			value = deItem.attribute(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::Flags)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFlags);
			value = deItem.attribute(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMBool);
			value = deItem.attribute(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMChar);
			QString val = deItem.attribute(pr.protoname);
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMShort);
			value = deItem.attribute(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUShort);
			value = deItem.attribute(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
			value = deItem.attribute(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUInt);
			value = deItem.attribute(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMLong);
			value = deItem.attribute(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMULong);
			value = deItem.attribute(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFloat);
			value = deItem.attribute(pr.protoname).replace(",", ".").toFloat();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDouble);
			value = deItem.attribute(pr.protoname).replace(",", ".").toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMStdString);
			value = deItem.attribute(pr.protoname).toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMString);
			value = deItem.attribute(pr.protoname);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUuid);
			value = RMUuid(deItem.attribute(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMTime);
			value = RMTime::fromString(deItem.attribute(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDate);
			value = RMDate::fromString(deItem.attribute(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDateTime);
			value = RMDateTime::fromString(deItem.attribute(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByteArray);
			value = RMByteArray::fromBase64(deItem.attribute(pr.protoname).toLocal8Bit());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByte);
			value = deItem.attribute(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMMoney);
			value = deItem.attribute(pr.protoname).toFloat();
		}
		else if (pr.type == Meta::Type::RecordPrtList)
		{
			if (meta.relations[pr.name] && meta.relations[pr.name]->createDataFunction)
			{
				auto& listptr = (*reinterpret_cast<QList<BaseItemData*>*>(reinterpret_cast<std::byte*>(&data)+pr.diff));
				QDomElement deSubSet = deItem.firstChildElement(pr.protoname);
				QDomElement deSubItem = deSubSet.firstChildElement(meta.relations[pr.name]->itemName);
				while (!deSubItem.isNull())
				{
					BaseItemData* subdata = meta.relations[pr.name]->createDataFunction->operator()();
					deserialize(*meta.relations[pr.name], *subdata, deSubItem);
					listptr.append(subdata);
					deSubItem = deSubItem.nextSiblingElement(meta.relations[pr.name]->itemName);
				}
			}
		}
		else if(pr.type == Meta::Type::PKeyList)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMPKeyList);
			value.clear();

			if (meta.relations[pr.name])
			{
				const QString idtag = meta.relations[pr.name]->properties[0].protoname;
				QDomElement deList = deItem.firstChildElement(pr.protoname);
				QDomElement deListItem = deList.firstChildElement(pr.special);
				while (!deListItem.isNull())
				{
					value.append(deListItem.attribute(idtag).toLongLong());
					deListItem = deListItem.nextSiblingElement(pr.special);
				}
			}
		}
		else
			Q_ASSERT_X(0, "deserialize", qPrintable(QString("Type \"%1\" not supported").arg(Meta::typeName(pr.type))));
}

void serialize(const Meta::Description& meta, const ItemData& data, QMap<QString, QString>& map, const Options& options)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (!options.options.isEmpty() && options.fieldOptionByName(pr.name) && options.skipByOptions(pr, data))
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Type)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMType);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::State)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMState);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Flags)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFlags);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMBool);
			if (value) map.insert(pr.protoname, QString::number(int(value)));
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMChar);
			if (value) map.insert(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUShort);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUInt);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMLong);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMULong);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFloat);
			if (value != 0.0) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDouble);
			if (value != 0.0) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMStdString);
			if (!value.empty()) map.insert(pr.protoname, QString::fromStdString(value));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMString);
			if (!value.isEmpty()) map.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUuid);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(QUuid::WithoutBraces));
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMTime);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDate);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			if (!value.isNull()) map.insert(pr.protoname, value.toBase64());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByte);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
			if (value != 0.0) map.insert(pr.protoname, QString::number(value));
		}
		else
			Q_ASSERT(0);
}

void deserialize(const Meta::Description& meta, ItemData& data, const QMap<QString, QString>& map)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMPKey);
			value = map.value(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Type)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMType);
			value = map.value(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::State)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMState);
			value = map.value(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::Flags)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFlags);
			value = map.value(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMBool);
			value = map.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMChar);
			QString val = map.value(pr.protoname);
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMShort);
			value = map.value(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUShort);
			value = map.value(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
			value = map.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUInt);
			value = map.value(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMLong);
			value = map.value(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMULong);
			value = map.value(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFloat);
			value = map.value(pr.protoname).toFloat();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDouble);
			value = map.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMStdString);
			value = map.value(pr.protoname).toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMString);
			value = map.value(pr.protoname);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUuid);
			value = RMUuid(map.value(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMTime);
			value = RMTime::fromString(map.value(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDate);
			value = RMDate::fromString(map.value(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDateTime);
			value = RMDateTime::fromString(map.value(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByteArray);
			value = RMByteArray::fromBase64(map.value(pr.protoname).toLocal8Bit());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByte);
			value = map.value(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMMoney);
			value = map.value(pr.protoname).toFloat();
		}
		else
			Q_ASSERT(0);
}

void serialize(const Meta::Description& meta, const ItemData& data, QJsonObject& jsObject, const Options& options)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (!options.options.isEmpty() && options.fieldOptionByName(pr.name) && options.skipByOptions(pr, data))
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Type)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMType);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::State)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMState);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Flags)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFlags);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMBool);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMChar);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUShort);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUInt);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMLong);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMULong);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFloat);
			if (options.keepEmptyValues || value != 0.0)
				jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDouble);
			if (options.keepEmptyValues || value != 0.0)
				jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMStdString);
			if (options.keepEmptyValues || !value.empty())
				jsObject.insert(pr.protoname, QJsonValue(QString::fromStdString(value)));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMString);
			if (options.keepEmptyValues || !value.isEmpty())
				jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUuid);
			if (options.keepEmptyValues || !value.isNull())
				jsObject.insert(pr.protoname, QJsonValue(value.toString(QUuid::WithoutBraces)));
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMTime);
			if (options.keepEmptyValues || !value.isNull())
				jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODateWithMs)));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDate);
			if (options.keepEmptyValues || !value.isNull())
				jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODate)));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime);
			if (options.keepEmptyValues || !value.isNull())
				jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODateWithMs)));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			if (options.keepEmptyValues || !value.isNull())
				jsObject.insert(pr.protoname, QJsonValue(QString(value.toBase64())));
		}
		else if(pr.type == Meta::Type::StringList)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMStringList);
			QJsonArray jsSubArray;
			for (auto str : value)
				jsSubArray.append(QJsonValue(str));
			jsObject.insert(pr.protoname, jsSubArray);
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByte);
			if (options.keepEmptyValues || value)
				jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
			if (options.keepEmptyValues || value != 0.0)
				jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::RecordPrtList)
		{
			if (meta.relations[pr.name])
			{
				auto& listptr = (*reinterpret_cast<const QList<const BaseItemData*>*>(reinterpret_cast<const std::byte*>(&data)+pr.diff));
				QJsonArray jsSubArray;
				for (auto rec: listptr)
				{
					QJsonObject jsObject;
					serialize(*meta.relations[pr.name], *rec, jsObject, options);
					jsSubArray.append(jsObject);
				}
				jsObject.insert(pr.protoname, jsSubArray);
			}
		}
		else if(pr.type == Meta::Type::PKeyList)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKeyList);
			QJsonArray jsSubArray;
			for (auto id : value)
				jsSubArray.append(QJsonValue(QString::number(id)));
			jsObject.insert(pr.protoname, jsSubArray);
		}
		else
			Q_ASSERT(0);
}

void deserialize(const Meta::Description& meta, ItemData& data, const QJsonObject& jsObject)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMPKey);
			value = jsObject.value(pr.protoname).toString().toULongLong();
		}
		else if (pr.type == Meta::Type::Type)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMType);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::State)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMState);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Flags)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFlags);
			value = jsObject.value(pr.protoname).toString().toUInt();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMBool);
			value = jsObject.value(pr.protoname).toBool();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMChar);
			QString val = jsObject.value(pr.protoname).toString();
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMShort);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUShort);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUInt);
			value = jsObject.value(pr.protoname).toString().toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMLong);
			value = jsObject.value(pr.protoname).toString().toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMULong);
			value = jsObject.value(pr.protoname).toString().toULongLong();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDouble);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMFloat);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMStdString);
			value = jsObject.value(pr.protoname).toString().toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMString);
			value = jsObject.value(pr.protoname).toString();
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMUuid);
			value = RMUuid(jsObject.value(pr.protoname).toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMTime);
			value = RMTime::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDate);
			value = RMDate::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMDateTime);
			value = RMDateTime::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByteArray);
			value = RMByteArray::fromBase64(jsObject.value(pr.protoname).toString().toLocal8Bit());
		}
		else if(pr.type == Meta::Type::StringList)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMStringList);
			value.clear();
			QJsonArray jsSubArray = jsObject.value(pr.protoname).toArray();
			for (const QJsonValue& subVal: jsSubArray)
				value.append(subVal.toString());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMByte);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMMoney);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::RecordPrtList)
		{
			if (meta.relations[pr.name] && meta.relations[pr.name]->createDataFunction)
			{
				auto& listptr = (*reinterpret_cast<QList<BaseItemData*>*>(reinterpret_cast<std::byte*>(&data)+pr.diff));
				QJsonArray jsSubArray = jsObject.value(pr.protoname).toArray();
				for (const QJsonValue& subVal: jsSubArray)
				{
					BaseItemData* subdata = meta.relations[pr.name]->createDataFunction->operator()();
					deserialize(*meta.relations[pr.name], *subdata, subVal.toObject());
					listptr.append(subdata);
				}
			}
		}
		else if(pr.type == Meta::Type::PKeyList)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMPKeyList);
			value.clear();
			QJsonArray jsSubArray = jsObject.value(pr.protoname).toArray();
			for (const QJsonValue& subVal: jsSubArray)
				value.append(subVal.toString().toLongLong());
		}
		else
			Q_ASSERT(0);
}

void serialize(const Meta::Description& meta, const ItemData& data, QIODevice& device)
{
	QByteArray res(4, 0x00);

	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			QByteArray vdata(8, 0x00);
			qToBigEndian<qint64>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Type)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMType);
			QByteArray vdata(2, 0x00);
			qToBigEndian<qint16>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::State)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMState);
			QByteArray vdata(2, 0x00);
			qToBigEndian<qint16>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Flags)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFlags);
			QByteArray vdata(4, 0x00);
			qToBigEndian<quint32>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMBool);
			QByteArray vdata(1, 0x00);
			vdata[0] = quint8(value);
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMChar);
			QByteArray vdata(1, 0x00);
			vdata[0] = value;
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
			QByteArray vdata(2, 0x00);
			qToBigEndian<qint16>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
			QByteArray vdata(2, 0x00);
			qToBigEndian<quint16>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
			QByteArray vdata(4, 0x00);
			qToBigEndian<qint32>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUInt);
			QByteArray vdata(4, 0x00);
			qToBigEndian<quint32>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMLong);
			QByteArray vdata(8, 0x00);
			qToBigEndian<qint64>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMULong);
			QByteArray vdata(8, 0x00);
			qToBigEndian<quint64>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMFloat);
			QByteArray vdata(4, 0x00);
			qToBigEndian<float>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDouble);
			QByteArray vdata(8, 0x00);
			qToBigEndian<double>(value, vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMStdString);
			QByteArray vdata(4, 0x00);
			qToBigEndian<qint32>(value.length(), vdata.data());
			vdata.append(value.data(), value.length());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMString);
			QByteArray strdata = value.toUtf8();
			QByteArray vdata(4, 0x00);
			qToBigEndian<qint32>(strdata.size(), vdata.data());
			vdata.append(strdata);
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMUuid);
			QByteArray vdata(16, 0x00);
			qToBigEndian<uint>(value.data1, vdata.data());
			qToBigEndian<ushort>(value.data2, vdata.data()+4);
			qToBigEndian<ushort>(value.data3, vdata.data()+6);
			for(int i = 0; i < 8; i++)
				vdata[8+i] = value.data4[i];
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMTime);
			QByteArray vdata(4, 0x00);
			qToBigEndian<qint32>(value.msecsSinceStartOfDay(), vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDate);
			QByteArray vdata(8, 0x00);
			qToBigEndian<qint64>(value.toJulianDay(), vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime);
			QByteArray vdata(8, 0x00);
			qToBigEndian<qint64>(value.toMSecsSinceEpoch(), vdata.data());
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			QByteArray vdata(4, 0x00);
			qToBigEndian<qint32>(value.size(), vdata.data());
			vdata.append(value);
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByte);
			QByteArray vdata(1, 0x00);
			vdata[0] = value;
			res.append(vdata);
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
			QByteArray vdata(4, 0x00);
			qToBigEndian<float>(value, vdata.data());
			res.append(vdata);
		}

	qToBigEndian<qint32>(qint32(res.size()-4), res.data());
	device.write(res);
}

bool deserialize(const Meta::Description& meta, ItemData& data, QIODevice& device)
{
	QByteArray sizeData = device.read(4);
	if (sizeData.size() == 4)
	{
		auto size = qFromBigEndian<qint32>(sizeData.data());
		if (size >= 0)
		{
			QByteArray itemData = device.read(size);
			int pos = 0;
			if (itemData.size() == size)
			{
				for (const Meta::Property& pr: meta.properties)
					if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
						continue;
					else if (pr.type == Meta::Type::PKey)
					{
						if (pos + 8 > itemData.size())
							return false;

						auto& value = CAST_DATAREL_TO_TYPEREL(RMPKey);
						value = qFromBigEndian<qint64>(itemData.data() + pos);
						pos += 8;
					}
					else if (pr.type == Meta::Type::Type)
					{
						if (pos + 2 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMType);
						value = qFromBigEndian<qint16>(itemData.data() + pos);
						pos += 2;
					}
					else if (pr.type == Meta::Type::State)
					{
						if (pos + 2 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMState);
						value = qFromBigEndian<qint16>(itemData.data() + pos);
						pos += 2;
					}
					else if (pr.type == Meta::Type::Flags)
					{
						if (pos + 4 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMFlags);
						value = qFromBigEndian<quint32>(itemData.data() + pos);
						pos += 4;
					}
					else if (pr.type == Meta::Type::Bool)
					{
						if (pos + 1 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMBool);
						value = itemData.data()[pos];
						pos += 1;
					}
					else if (pr.type == Meta::Type::Char)
					{
						if (pos + 1 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMChar);
						value = itemData.data()[pos];
						pos += 1;
					}
					else if (pr.type == Meta::Type::Short)
					{
						if (pos + 2 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMShort);
						value = qFromBigEndian<qint16>(itemData.data() + pos);
						pos += 2;
					}
					else if (pr.type == Meta::Type::UShort)
					{
						if (pos + 2 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMUShort);
						value = qFromBigEndian<quint16>(itemData.data() + pos);
						pos += 2;
					}
					else if (pr.type == Meta::Type::Int)
					{
						if (pos + 4 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
						value = qFromBigEndian<qint32>(itemData.data() + pos);
						pos += 4;
					}
					else if (pr.type == Meta::Type::UInt)
					{
						if (pos + 4 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMUInt);
						value = qFromBigEndian<quint32>(itemData.data() + pos);
						pos += 4;
					}
					else if (pr.type == Meta::Type::Long)
					{
						if (pos + 8 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMLong);
						value = qFromBigEndian<qint64>(itemData.data() + pos);
						pos += 8;
					}
					else if (pr.type == Meta::Type::ULong)
					{
						if (pos + 8 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMULong);
						value = qFromBigEndian<quint64>(itemData.data() + pos);
						pos += 8;
					}
					else if (pr.type == Meta::Type::Float)
					{
						if (pos + 4 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMFloat);
						value = qFromBigEndian<float>(itemData.data() + pos);
						pos += 4;
					}
					else if (pr.type == Meta::Type::Double)
					{
						if (pos + 8 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMDouble);
						value = qFromBigEndian<double>(itemData.data() + pos);
						pos += 8;
					}
					else if (pr.type == Meta::Type::StdString)
					{
						if (pos + 4 > itemData.size())
							return false;
						int size = qFromBigEndian<qint32>(itemData.data() + pos);
						pos += 4;
						if (pos + size > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMStdString);
						value = RMStdString(itemData.data() + pos, size);
						pos += size;
					}
					else if (pr.type == Meta::Type::String)
					{
						if (pos + 4 > itemData.size())
							return false;
						int size = qFromBigEndian<qint32>(itemData.data() + pos);
						pos += 4;
						if (pos + size > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMString);
						value = RMString::fromUtf8(itemData.data() + pos, size);
						pos += size;
					}
					else if (pr.type == Meta::Type::Uuid)
					{
						if (pos + 16 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMUuid);
						value.data1 = qFromBigEndian<uint>(itemData.data() + pos);
						value.data2 = qFromBigEndian<ushort>(itemData.data() + pos+4);
						value.data3 = qFromBigEndian<ushort>(itemData.data() + pos+6);
						for(int i = 0; i < 8; i++)
							value.data4[i] = itemData[pos+8+i];
						pos += 16;
					}
					else if (pr.type == Meta::Type::Time)
					{
						if (pos + 4 > itemData.size())
							return false;
						int ms = qFromBigEndian<qint32>(itemData.data() + pos);
						auto& value = CAST_DATAREL_TO_TYPEREL(RMTime);
						value = QTime::fromMSecsSinceStartOfDay(ms);
						pos += 4;
					}
					else if (pr.type == Meta::Type::Date)
					{
						if (pos + 8 > itemData.size())
							return false;
						qint64 jd = qFromBigEndian<qint64>(itemData.data() + pos);
						auto& value = CAST_DATAREL_TO_TYPEREL(RMDate);
						value = QDate::fromJulianDay(jd);
						pos += 8;
					}
					else if (pr.type == Meta::Type::DateTime)
					{
						if (pos + 8 > itemData.size())
							return false;
						qint64 ms = qFromBigEndian<qint64>(itemData.data() + pos);
						auto& value = CAST_DATAREL_TO_TYPEREL(RMDateTime);
						value = QDateTime::fromMSecsSinceEpoch(ms);
						pos += 8;
					}
					else if (pr.type == Meta::Type::ByteArray)
					{
						if (pos + 4 > itemData.size())
							return false;
						int size = qFromBigEndian<qint32>(itemData.data() + pos);
						pos += 4;
						if (pos + size > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMByteArray);
						value = RMByteArray(itemData.data() + pos, size);
						pos += size;
					}
					else if (pr.type == Meta::Type::Byte)
					{
						if (pos + 1 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMByte);
						value = itemData.data()[pos];
						pos += 1;
					}
					else if (pr.type == Meta::Type::Money)
					{
						if (pos + 4 > itemData.size())
							return false;
						auto& value = CAST_DATAREL_TO_TYPEREL(RMMoney);
						value = qFromBigEndian<float>(itemData.data() + pos);
						pos += 4;
					}
				return pos == itemData.size();
			}
		}
	}
	return false;
}

void Options::serialize(QDomElement& deOptions) const
{
	if (!options.isEmpty())
	{
		QDomElement deFields = deOptions.ownerDocument().createElement("Fields");
		for (auto& option : options)
		{
			QDomElement deField = deOptions.ownerDocument().createElement("Field");
			deField.setAttribute("option", int(option.option));
			deField.setAttribute("name", option.name);
			deField.setAttribute("value", option.value);

			deFields.appendChild(deField);
		}
		deOptions.appendChild(deFields);
	}
	deOptions.setAttribute("keepEmptyValues", int(keepEmptyValues));
}

void Options::deserialize(const QDomElement& deOptions)
{
	QDomElement deFields = deOptions.firstChildElement("Fields");
	if (!deFields.isNull())
	{
		QDomElement deField = deFields.firstChildElement("Field");
		while (!deField.isNull()) {
			FieldOption foption;
			foption.option = FieldOptions(deField.attribute("option").toInt());
			foption.name = deField.attribute("name");
			foption.value = deField.attribute("value");
			this->options.append(foption);
			deField = deField.nextSiblingElement("Field");
		}
	}
	keepEmptyValues = deOptions.attribute("keepEmptyValues").toInt();
}

static const Options ramioStandardOptions;

const Options& standardOptions()
{
	return ramioStandardOptions;
}

const FieldOption* Options::fieldOptionByName(const QString& fname) const
{
	for (auto& op : options)
		if (op.name == fname)
			return &op;
	return Q_NULLPTR;
}

bool Options::skipByOptions(const Meta::Property& pr, const ItemData& data) const
{
	for (auto& op : options)
		if (op.name == pr.name)
		{
			if (op.option == FieldOptions::Skip)
				return true;

			if (pr.type == Meta::Type::PKey)
			{
				const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
				RMPKey ovalue = op.value.toLongLong();
				switch (op.option) {
					case FieldOptions::Equal: if (value != ovalue) return true; break;
					case FieldOptions::More: if (value <= ovalue) return true; break;
					case FieldOptions::MoreOrEqual: if (value < ovalue) return true; break;
					case FieldOptions::Less: if (value > ovalue) return true; break;
					case FieldOptions::LessOrEqual: if (value >= ovalue) return true; break;
					case FieldOptions::Unset: case FieldOptions::Skip: break;
				}
			}
		}
	return false;
}

} // Serialization ::

} // Ramio ::
