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

#include "MetaItemSerialization.h"
// Qt5
#include <QtXml/QDomElement>
#include <QtCore/QJsonObject>
#include <QtCore/QDateTime>
#include <QtCore/QMap>

namespace Ramio {

namespace Meta {

void serialize(const Meta::Description& meta, const ItemData& data, QDomElement& deItem)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool);
			if (value) deItem.setAttribute(pr.protoname, int(value));
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaChar);
			if (value) deItem.setAttribute(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaFloat);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
			if (value != 0.0) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaStdString);
			if (!value.empty()) deItem.setAttribute(pr.protoname, QString::fromStdString(value));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
			if (!value.isEmpty()) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByteArray);
			if (!value.isNull()) deItem.setAttribute(pr.protoname, QString(value.toBase64()));
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte);
			if (value) deItem.setAttribute(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			if (value != 0.0) deItem.setAttribute(pr.protoname, QString::number((value+(value > 0 ? 1 : -1)*0.000001), 'f', 2));
		}
		else
			Q_ASSERT_X(0, "serialize", qPrintable(QString("Type \"%1\" not supported").arg(Ramio::Meta::typeName(pr.type))));
}

void deserialize(const Meta::Description& meta, ItemData& data, const QDomElement& deItem)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			value = deItem.attribute(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaBool);
			value = deItem.attribute(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaChar);
			QString val = deItem.attribute(pr.protoname);
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaShort);
			value = deItem.attribute(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUShort);
			value = deItem.attribute(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = deItem.attribute(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUInt);
			value = deItem.attribute(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			value = deItem.attribute(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaULong);
			value = deItem.attribute(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaFloat);
			value = deItem.attribute(pr.protoname).replace(",", ".").toFloat();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = deItem.attribute(pr.protoname).replace(",", ".").toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaStdString);
			value = deItem.attribute(pr.protoname).toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = deItem.attribute(pr.protoname);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			value = RMetaUuid(deItem.attribute(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			value = RMetaTime::fromString(deItem.attribute(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDate);
			value = RMetaDate::fromString(deItem.attribute(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = RMetaDateTime::fromString(deItem.attribute(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByteArray);
			value = RMetaByteArray::fromBase64(deItem.attribute(pr.protoname).toLocal8Bit());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByte);
			value = deItem.attribute(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = deItem.attribute(pr.protoname).toFloat();
		}
		else
			Q_ASSERT_X(0, "deserialize", qPrintable(QString("Type \"%1\" not supported").arg(Ramio::Meta::typeName(pr.type))));
}

void serialize(const Meta::Description& meta, const ItemData& data, QMap<QString, QString>& map)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool);
			if (value) map.insert(pr.protoname, QString::number(int(value)));
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaChar);
			if (value) map.insert(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaStdString);
			if (!value.empty()) map.insert(pr.protoname, QString::fromStdString(value));
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
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			if (!value.isNull()) map.insert(pr.protoname, value.toString(Qt::ISODateWithMs));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByteArray);
			if (!value.isNull()) map.insert(pr.protoname, value.toBase64());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte);
			if (value) map.insert(pr.protoname, QString::number(value));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
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
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			value = map.value(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaBool);
			value = map.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaChar);
			QString val = map.value(pr.protoname);
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaShort);
			value = map.value(pr.protoname).toShort();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUShort);
			value = map.value(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = map.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUInt);
			value = map.value(pr.protoname).toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			value = map.value(pr.protoname).toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaULong);
			value = map.value(pr.protoname).toULongLong();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaFloat);
			value = map.value(pr.protoname).toFloat();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = map.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaStdString);
			value = map.value(pr.protoname).toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = map.value(pr.protoname);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			value = RMetaUuid(map.value(pr.protoname));
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			value = RMetaTime::fromString(map.value(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDate);
			value = RMetaDate::fromString(map.value(pr.protoname), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = RMetaDateTime::fromString(map.value(pr.protoname), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByteArray);
			value = RMetaByteArray::fromBase64(map.value(pr.protoname).toLocal8Bit());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByte);
			value = map.value(pr.protoname).toUShort();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = map.value(pr.protoname).toFloat();
		}
		else
			Q_ASSERT(0);
}

void serialize(const Meta::Description& meta, const ItemData& data, QJsonObject& jsObject)
{
	for (const Meta::Property& pr: meta.properties)
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (value) jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool);
			if (value) jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Char)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaChar);
			if (value) jsObject.insert(pr.protoname, QString(value));
		}
		else if (pr.type == Meta::Type::Short)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort);
			if (value) jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UShort)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort);
			if (value) jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			if (value) jsObject.insert(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::UInt)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt);
			if (value) jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			if (value) jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::ULong)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong);
			if (value) jsObject.insert(pr.protoname, QJsonValue(QString::number(value)));
		}
		else if (pr.type == Meta::Type::Float)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaFloat);
			if (value != 0.0) jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
			if (value != 0.0) jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::StdString)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaStdString);
			if (!value.empty()) jsObject.insert(pr.protoname, QJsonValue(QString::fromStdString(value)));
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
			if (!value.isEmpty()) jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			if (!value.isNull()) jsObject.insert(pr.protoname, QJsonValue(value.toString()));
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			if (!value.isNull()) jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODateWithMs)));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate);
			if (!value.isNull()) jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODate)));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			if (!value.isNull()) jsObject.insert(pr.protoname, QJsonValue(value.toString(Qt::ISODateWithMs)));
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByteArray);
			if (!value.isNull()) jsObject.insert(pr.protoname, QJsonValue(QString(value.toBase64())));
		}
		else if (pr.type == Meta::Type::Byte)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte);
			if (value) jsObject.insert(pr.protoname, QJsonValue(value));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			if (value != 0.0) jsObject.insert(pr.protoname, QJsonValue(value));
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
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			value = jsObject.value(pr.protoname).toString().toULongLong();
		}
		else if (pr.type == Meta::Type::Bool)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaBool);
			value = jsObject.value(pr.protoname).toBool();
		}
		else if (pr.type == Meta::Type::Char)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaChar);
			QString val = jsObject.value(pr.protoname).toString();
			value = val.isEmpty() ? 0x00 : val[0].toLatin1();
		}
		else if (pr.type == Meta::Type::Short)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaShort);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UShort)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUShort);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::UInt)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUInt);
			value = jsObject.value(pr.protoname).toString().toUInt();
		}
		else if (pr.type == Meta::Type::Long)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			value = jsObject.value(pr.protoname).toString().toLongLong();
		}
		else if (pr.type == Meta::Type::ULong)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaULong);
			value = jsObject.value(pr.protoname).toString().toULongLong();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::Float)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaFloat);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else if (pr.type == Meta::Type::StdString)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaStdString);
			value = jsObject.value(pr.protoname).toString().toStdString();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = jsObject.value(pr.protoname).toString();
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			value = RMetaUuid(jsObject.value(pr.protoname).toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			value = RMetaTime::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::Date)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDate);
			value = RMetaDate::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODate);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = RMetaDateTime::fromString(jsObject.value(pr.protoname).toString(), Qt::ISODateWithMs);
		}
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByteArray);
			value = RMetaByteArray::fromBase64(jsObject.value(pr.protoname).toString().toLocal8Bit());
		}
		else if (pr.type == Meta::Type::Byte)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaByte);
			value = jsObject.value(pr.protoname).toInt();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = jsObject.value(pr.protoname).toDouble();
		}
		else
			Q_ASSERT(0);
}

} // Meta ::

} // Ramio::
