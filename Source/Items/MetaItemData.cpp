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

#include "MetaItemData.h"
// Qt5
#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

#define CAST_CONST_DATA1REL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data1, type, pr.diff, const)
#define CAST_CONST_DATA2REL_TO_TYPEREL(type) CAST_FIELDREL_BASE(data2, type, pr.diff, const)

namespace Ramio {

QVector<Meta::Property> MetaItemData::registerMetaFields() const
{
	QVector<Meta::Property> res;
	RMETA_OBJECT_PROPERTY(id, PKey, "Id", QObject::tr("Идентификатор"), PKey)
	return res;
}

QVector<Meta::Property> MetaStandardItemData::registerMetaFields() const
{
	QVector<Meta::Property> res;
	RMETA_OBJECT_PROPERTY(id, PKey, "Id", QObject::tr("Идентификатор"), PKey)
	RMETA_OBJECT_PROPERTY(uuid, Uuid, "Uuid", QObject::tr("Глобальный идентификатор"), Field)
	RMETA_OBJECT_PROPERTY(type, Short, "Type", QObject::tr("Тип"), Type)
	RMETA_OBJECT_PROPERTY(state, Short, "State", QObject::tr("Состояние"), Value)
	RMETA_OBJECT_PROPERTY(flags, Int, "Flags", QObject::tr("Флаги"), Value)
	return res;
}

namespace Meta {

bool equalsField(const Meta::Property& pr, const Data& data1, const Data& data2)
{
	if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
		return true;
	else if (pr.type == Meta::Type::PKey)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaPKey) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaPKey))
			return false;
	}
	else if (pr.type == Meta::Type::Bool)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaBool) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaBool))
			return false;
	}
	else if (pr.type == Meta::Type::Char)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaChar) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaChar))
			return false;
	}
	else if (pr.type == Meta::Type::Short)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaShort) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaShort))
			return false;
	}
	else if (pr.type == Meta::Type::UShort)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaUShort) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaUShort))
			return false;
	}
	else if (pr.type == Meta::Type::Int)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaInt) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaInt))
			return false;
	}
	else if (pr.type == Meta::Type::UInt)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaUInt) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaUInt))
			return false;
	}
	else if (pr.type == Meta::Type::Long)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaLong) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaLong))
			return false;
	}
	else if (pr.type == Meta::Type::ULong)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaULong) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaULong))
			return false;
	}
	else if (pr.type == Meta::Type::Float)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMetaFloat) - CAST_CONST_DATA2REL_TO_TYPEREL(RMetaFloat)) <= std::numeric_limits<RMetaFloat>::lowest())
			return false;
	}
	else if (pr.type == Meta::Type::Double)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMetaDouble) - CAST_CONST_DATA2REL_TO_TYPEREL(RMetaDouble)) <= std::numeric_limits<RMetaDouble>::lowest())
			return false;
	}
	else if (pr.type == Meta::Type::StdString)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaStdString).compare(CAST_CONST_DATA2REL_TO_TYPEREL(RMetaStdString)) != 0)
			return false;
	}
	else if (pr.type == Meta::Type::String)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaString) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaString))
			return false;
	}
	else if (pr.type == Meta::Type::Uuid)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaUuid) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaUuid))
			return false;
	}
	else if (pr.type == Meta::Type::Time)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaTime) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaTime))
			return false;
	}
	else if (pr.type == Meta::Type::Date)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaDate) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaDate))
			return false;
	}
	else if (pr.type == Meta::Type::DateTime)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaDateTime) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaDateTime))
			return false;
	}
	else if (pr.type == Meta::Type::ByteArray)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaByteArray) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaByteArray))
			return false;
	}
	else if (pr.type == Meta::Type::Byte)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaByte) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaByte))
			return false;
	}
	else if (pr.type == Meta::Type::Money)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMetaMoney) - CAST_CONST_DATA2REL_TO_TYPEREL(RMetaMoney)) > 0.001f)
			return false;
	}
	else
		Q_ASSERT(0);
	return true;
}

bool equals(const Meta::Description& meta, const Data& data1, const Data& data2)
{
	for (const auto& pr: meta.properties)
		if (!equalsField(pr, data1, data2))
			return false;
	return true;
}

bool equalsData(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2)
{
	for (int i = 1; i < meta.properties.count(); i++)
	{
		const auto& pr = meta.properties[i];
		if (!equalsField(pr, data1, data2))
			return false;
	}
	return true;
}

bool less(Meta::Type fieldtype, const ItemData& left, const ItemData& right, ptrdiff_t diff)
{
	switch (fieldtype) {
		case Ramio::Meta::Type::PKey: return Ramio::Meta::less<RMetaPKey>(left, right, diff);
		case Ramio::Meta::Type::Bool: return Ramio::Meta::less<RMetaBool>(left, right, diff);
		case Ramio::Meta::Type::Char: return Ramio::Meta::less<RMetaChar>(left, right, diff);
		case Ramio::Meta::Type::Short: return Ramio::Meta::less<RMetaShort>(left, right, diff);
		case Ramio::Meta::Type::UShort: return Ramio::Meta::less<RMetaUShort>(left, right, diff);
		case Ramio::Meta::Type::Int: return Ramio::Meta::less<RMetaInt>(left, right, diff);
		case Ramio::Meta::Type::UInt: return Ramio::Meta::less<RMetaUInt>(left, right, diff);
		case Ramio::Meta::Type::Long: return Ramio::Meta::less<RMetaLong>(left, right, diff);
		case Ramio::Meta::Type::ULong: return Ramio::Meta::less<RMetaULong>(left, right, diff);
		case Ramio::Meta::Type::Float: return Ramio::Meta::less<RMetaFloat>(left, right, diff);
		case Ramio::Meta::Type::Double: return Ramio::Meta::less<RMetaDouble>(left, right, diff);
		case Ramio::Meta::Type::StdString: return Ramio::Meta::less<RMetaStdString>(left, right, diff);
		case Ramio::Meta::Type::String: return Ramio::Meta::less<RMetaString>(left, right, diff);
		case Ramio::Meta::Type::Uuid: return Ramio::Meta::less<RMetaUuid>(left, right, diff);
		case Ramio::Meta::Type::Date: return Ramio::Meta::less<RMetaDate>(left, right, diff);
		case Ramio::Meta::Type::Time: return Ramio::Meta::less<RMetaTime>(left, right, diff);
		case Ramio::Meta::Type::DateTime: return Ramio::Meta::less<RMetaDateTime>(left, right, diff);
		case Ramio::Meta::Type::ByteArray: return Ramio::Meta::less<RMetaByteArray>(left, right, diff);
		case Ramio::Meta::Type::Byte: return Ramio::Meta::less<RMetaByte>(left, right, diff);
		case Ramio::Meta::Type::Money: return Ramio::Meta::less<RMetaMoney>(left, right, diff);
		default: return false;
	}
}

} // Meta ::

QDebug operator << (QDebug dbg, const MetaItemData& data)
{
	auto properties = data.registerMetaFields();

	for (const auto& pr: properties)
	{
		if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey) << ";";
		else if (pr.type == Meta::Type::Bool)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool) << ";";
		else if (pr.type == Meta::Type::Char)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaChar) << ";";
		else if (pr.type == Meta::Type::Short)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort) << ";";
		else if (pr.type == Meta::Type::UShort)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort) << ";";
		else if (pr.type == Meta::Type::Int)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt) << ";";
		else if (pr.type == Meta::Type::UInt)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt) << ";";
		else if (pr.type == Meta::Type::Long)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong) << ";";
		else if (pr.type == Meta::Type::ULong)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong) << ";";
		else if (pr.type == Meta::Type::StdString)
			dbg.nospace() << pr.name << ":" << QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMetaStdString)) << ";";
		else if (pr.type == Meta::Type::String)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaString) << ";";
		else if (pr.type == Meta::Type::Double)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble) << ";";
		else if (pr.type == Meta::Type::Uuid)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid) << ";";
		else if (pr.type == Meta::Type::Time)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime) << ";";
		else if (pr.type == Meta::Type::Date)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate) << ";";
		else if (pr.type == Meta::Type::DateTime)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime) << ";";
		else if (pr.type == Meta::Type::ByteArray)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaByteArray).toHex() << ";";
		else if (pr.type == Meta::Type::Byte)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte) << ";";
		else if (pr.type == Meta::Type::Money)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney) << ";";
		else
			Q_ASSERT(0);
	}
	return dbg.space();
}

} // Ramio::

QString cameCaseFirstChar(const QString& str)
{
	return str.mid(0, 1).append(str.mid(1));
}
