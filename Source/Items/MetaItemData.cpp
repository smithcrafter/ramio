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
	RMETA_DATA_PROPERTY(id, PKey, "Id", QObject::tr("Идентификатор"), PKey, QString())
			return res;
}

QString MetaItemData::valueToString(quint8 index, const Meta::Description& meta)
{
	return Meta::valueToString(meta.properties[index].type, &field<RMByte>(meta.properties[index].diff));
}

QVector<Meta::Property> MetaStandardItemData::registerMetaFields() const
{
	QVector<Meta::Property> res;
	RMETA_DATA_PROPERTY(id, PKey, "Id", QObject::tr("Идентификатор"), PKey, QString())
	RMETA_DATA_PROPERTY(uuid, Uuid, "Uuid", QObject::tr("Глобальный идентификатор"), Field, QString())
	RMETA_DATA_PROPERTY(type, Type, "Type", QObject::tr("Тип"), Type, QString())
	RMETA_DATA_PROPERTY(state, State , "State", QObject::tr("Состояние"), Type, QString())
	RMETA_DATA_PROPERTY(flags, Flags, "Flags", QObject::tr("Флаги"), Flags, QString())
	return res;
}

namespace Meta {

bool equalsField(const Meta::Property& pr, const Data& data1, const Data& data2)
{
	if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
		return true;
	else if (pr.type == Meta::Type::PKey)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMPKey) != CAST_CONST_DATA2REL_TO_TYPEREL(RMPKey))
			return false;
	}
	else if (pr.type == Meta::Type::Type)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMType) != CAST_CONST_DATA2REL_TO_TYPEREL(RMType))
			return false;
	}
	else if (pr.type == Meta::Type::State)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMState) != CAST_CONST_DATA2REL_TO_TYPEREL(RMState))
			return false;
	}
	else if (pr.type == Meta::Type::Flags)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMFlags) != CAST_CONST_DATA2REL_TO_TYPEREL(RMFlags))
			return false;
	}
	else if (pr.type == Meta::Type::Bool)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMBool) != CAST_CONST_DATA2REL_TO_TYPEREL(RMBool))
			return false;
	}
	else if (pr.type == Meta::Type::Char)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMChar) != CAST_CONST_DATA2REL_TO_TYPEREL(RMChar))
			return false;
	}
	else if (pr.type == Meta::Type::Short)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMShort) != CAST_CONST_DATA2REL_TO_TYPEREL(RMShort))
			return false;
	}
	else if (pr.type == Meta::Type::UShort)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMUShort) != CAST_CONST_DATA2REL_TO_TYPEREL(RMUShort))
			return false;
	}
	else if (pr.type == Meta::Type::Int)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMInt) != CAST_CONST_DATA2REL_TO_TYPEREL(RMInt))
			return false;
	}
	else if (pr.type == Meta::Type::UInt)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMUInt) != CAST_CONST_DATA2REL_TO_TYPEREL(RMUInt))
			return false;
	}
	else if (pr.type == Meta::Type::Long)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMLong) != CAST_CONST_DATA2REL_TO_TYPEREL(RMLong))
			return false;
	}
	else if (pr.type == Meta::Type::ULong)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMULong) != CAST_CONST_DATA2REL_TO_TYPEREL(RMULong))
			return false;
	}
	else if (pr.type == Meta::Type::Float)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMFloat) - CAST_CONST_DATA2REL_TO_TYPEREL(RMFloat)) <= std::numeric_limits<RMFloat>::lowest())
			return false;
	}
	else if (pr.type == Meta::Type::Double)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMDouble) - CAST_CONST_DATA2REL_TO_TYPEREL(RMDouble)) <= std::numeric_limits<RMDouble>::lowest())
			return false;
	}
	else if (pr.type == Meta::Type::StdString)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMStdString).compare(CAST_CONST_DATA2REL_TO_TYPEREL(RMStdString)) != 0)
			return false;
	}
	else if (pr.type == Meta::Type::String)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMString) != CAST_CONST_DATA2REL_TO_TYPEREL(RMString))
			return false;
	}
	else if (pr.type == Meta::Type::Uuid)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMUuid) != CAST_CONST_DATA2REL_TO_TYPEREL(RMUuid))
			return false;
	}
	else if (pr.type == Meta::Type::Time)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMTime) != CAST_CONST_DATA2REL_TO_TYPEREL(RMTime))
			return false;
	}
	else if (pr.type == Meta::Type::Date)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMDate) != CAST_CONST_DATA2REL_TO_TYPEREL(RMDate))
			return false;
	}
	else if (pr.type == Meta::Type::DateTime)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMDateTime) != CAST_CONST_DATA2REL_TO_TYPEREL(RMDateTime))
			return false;
	}
	else if (pr.type == Meta::Type::ByteArray)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMByteArray) != CAST_CONST_DATA2REL_TO_TYPEREL(RMByteArray))
			return false;
	}
	else if (pr.type == Meta::Type::Byte)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMByte) != CAST_CONST_DATA2REL_TO_TYPEREL(RMByte))
			return false;
	}
	else if (pr.type == Meta::Type::Money)
	{
		if (qAbs(CAST_CONST_DATA1REL_TO_TYPEREL(RMMoney) - CAST_CONST_DATA2REL_TO_TYPEREL(RMMoney)) > 0.001f)
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

bool equalsData(const Meta::Description& meta, const Data& data1, const Data& data2)
{
	for (quint8 i = 1; i < meta.properties.count(); i++)
	{
		const auto& pr = meta.properties[i];
		if (!equalsField(pr, data1, data2))
			return false;
	}
	return true;
}

QList<quint8> differingDataFields(const Description& meta, const Data& data1, const Data& data2)
{
	QList<quint8> result;
	for (quint8 i = 1; i < meta.properties.count(); i++)
	{
		const auto& pr = meta.properties[i];
		if (!equalsField(pr, data1, data2))
			result.append(i);
	}
	return result;
}

bool less(Meta::Type fieldtype, const ItemData& left, const ItemData& right, ptrdiff_t diff)
{
	switch (fieldtype) {
		case Ramio::Meta::Type::Bool: return Ramio::Meta::less<RMBool>(left, right, diff);
		case Ramio::Meta::Type::Char: return Ramio::Meta::less<RMChar>(left, right, diff);
		case Ramio::Meta::Type::Short: return Ramio::Meta::less<RMShort>(left, right, diff);
		case Ramio::Meta::Type::UShort: return Ramio::Meta::less<RMUShort>(left, right, diff);
		case Ramio::Meta::Type::Int: return Ramio::Meta::less<RMInt>(left, right, diff);
		case Ramio::Meta::Type::UInt: return Ramio::Meta::less<RMUInt>(left, right, diff);
		case Ramio::Meta::Type::Long: return Ramio::Meta::less<RMLong>(left, right, diff);
		case Ramio::Meta::Type::ULong: return Ramio::Meta::less<RMULong>(left, right, diff);
		case Ramio::Meta::Type::Float: return Ramio::Meta::less<RMFloat>(left, right, diff);
		case Ramio::Meta::Type::Double: return Ramio::Meta::less<RMDouble>(left, right, diff);
		case Ramio::Meta::Type::StdString: return Ramio::Meta::less<RMStdString>(left, right, diff);
		case Ramio::Meta::Type::String: return Ramio::Meta::less<RMString>(left, right, diff);
		case Ramio::Meta::Type::Uuid: return Ramio::Meta::less<RMUuid>(left, right, diff);
		case Ramio::Meta::Type::Date: return Ramio::Meta::less<RMDate>(left, right, diff);
		case Ramio::Meta::Type::Time: return Ramio::Meta::less<RMTime>(left, right, diff);
		case Ramio::Meta::Type::DateTime: return Ramio::Meta::less<RMDateTime>(left, right, diff);
		case Ramio::Meta::Type::ByteArray: return Ramio::Meta::less<RMByteArray>(left, right, diff);
		case Ramio::Meta::Type::Byte: return Ramio::Meta::less<RMByte>(left, right, diff);
		case Ramio::Meta::Type::Money: return Ramio::Meta::less<RMMoney>(left, right, diff);
		case Ramio::Meta::Type::PKey: return Ramio::Meta::less<RMPKey>(left, right, diff);
		case Ramio::Meta::Type::Type: return Ramio::Meta::less<RMType>(left, right, diff);
		case Ramio::Meta::Type::State: return Ramio::Meta::less<RMState>(left, right, diff);
		case Ramio::Meta::Type::Flags: return Ramio::Meta::less<RMFlags>(left, right, diff);
		default: return false;
	}
}

void copyData(const Description& meta, const Data& data1, Data& data2)
{
	for (const Property& pr: meta.properties)
	{
		switch (pr.type) {
		case Ramio::Meta::Type::Bool:
				CAST_FIELDREL_BASE(data2, RMBool, pr.diff,) = CAST_FIELDREL_BASE(data1,RMBool, pr.diff, const); break;
		case Ramio::Meta::Type::Char:
				CAST_FIELDREL_BASE(data2, RMChar, pr.diff,) = CAST_FIELDREL_BASE(data1,RMChar, pr.diff, const); break;
		case Ramio::Meta::Type::Short:
				CAST_FIELDREL_BASE(data2, RMShort, pr.diff,) = CAST_FIELDREL_BASE(data1,RMShort, pr.diff, const); break;
		case Ramio::Meta::Type::UShort:
				CAST_FIELDREL_BASE(data2, RMUShort, pr.diff,) = CAST_FIELDREL_BASE(data1,RMUShort, pr.diff, const); break;
		case Ramio::Meta::Type::Int:
				CAST_FIELDREL_BASE(data2, RMInt, pr.diff,) = CAST_FIELDREL_BASE(data1,RMInt, pr.diff, const); break;
		case Ramio::Meta::Type::UInt:
				CAST_FIELDREL_BASE(data2, RMUInt, pr.diff,) = CAST_FIELDREL_BASE(data1,RMUInt, pr.diff, const); break;
		case Ramio::Meta::Type::Long:
				CAST_FIELDREL_BASE(data2, RMLong, pr.diff,) = CAST_FIELDREL_BASE(data1,RMLong, pr.diff, const); break;
		case Ramio::Meta::Type::ULong:
				CAST_FIELDREL_BASE(data2, RMULong, pr.diff,) = CAST_FIELDREL_BASE(data1,RMULong, pr.diff, const); break;
		case Ramio::Meta::Type::Float:
				CAST_FIELDREL_BASE(data2, RMFloat, pr.diff,) = CAST_FIELDREL_BASE(data1,RMFloat, pr.diff, const); break;
		case Ramio::Meta::Type::Double:
				CAST_FIELDREL_BASE(data2, RMDouble, pr.diff,) = CAST_FIELDREL_BASE(data1,RMDouble, pr.diff, const); break;
		case Ramio::Meta::Type::StdString:
				CAST_FIELDREL_BASE(data2, RMStdString, pr.diff,) = CAST_FIELDREL_BASE(data1,RMStdString, pr.diff, const); break;
		case Ramio::Meta::Type::String:
				CAST_FIELDREL_BASE(data2, RMString, pr.diff,) = CAST_FIELDREL_BASE(data1,RMString, pr.diff, const); break;
		case Ramio::Meta::Type::Uuid:
				CAST_FIELDREL_BASE(data2, RMUuid, pr.diff,) = CAST_FIELDREL_BASE(data1,RMUuid, pr.diff, const); break;
		case Ramio::Meta::Type::Date:
				CAST_FIELDREL_BASE(data2, RMDate, pr.diff,) = CAST_FIELDREL_BASE(data1,RMDate, pr.diff, const); break;
		case Ramio::Meta::Type::Time:
				CAST_FIELDREL_BASE(data2, RMTime, pr.diff,) = CAST_FIELDREL_BASE(data1,RMTime, pr.diff, const); break;
		case Ramio::Meta::Type::DateTime:
				CAST_FIELDREL_BASE(data2, RMDateTime, pr.diff,) = CAST_FIELDREL_BASE(data1,RMDateTime, pr.diff, const); break;
		case Ramio::Meta::Type::ByteArray:
				CAST_FIELDREL_BASE(data2, RMByteArray, pr.diff,) = CAST_FIELDREL_BASE(data1,RMByteArray, pr.diff, const); break;
		case Ramio::Meta::Type::Byte:
				CAST_FIELDREL_BASE(data2, RMByte, pr.diff,) = CAST_FIELDREL_BASE(data1,RMByte, pr.diff, const); break;
		case Ramio::Meta::Type::Money:
				CAST_FIELDREL_BASE(data2, RMMoney, pr.diff,) = CAST_FIELDREL_BASE(data1,RMMoney, pr.diff, const); break;
		case Ramio::Meta::Type::PKey:
				CAST_FIELDREL_BASE(data2, RMPKey, pr.diff,) = CAST_FIELDREL_BASE(data1,RMPKey, pr.diff, const); break;
		case Ramio::Meta::Type::Type:
				CAST_FIELDREL_BASE(data2, RMType, pr.diff,) = CAST_FIELDREL_BASE(data1,RMType, pr.diff, const); break;
		case Ramio::Meta::Type::State:
				CAST_FIELDREL_BASE(data2, RMState, pr.diff,) = CAST_FIELDREL_BASE(data1,RMState, pr.diff, const); break;
		case Ramio::Meta::Type::Flags:
				CAST_FIELDREL_BASE(data2, RMFlags, pr.diff,) = CAST_FIELDREL_BASE(data1,RMFlags, pr.diff, const); break;
		case Ramio::Meta::Type::RecordPrtList:
			if (meta.relations.contains(pr.name) && meta.relations[pr.name] && meta.relations[pr.name]->createDataFunction)
			{
				auto& recptrlist1 = (*reinterpret_cast<const QList<const BaseItemData*>*>(reinterpret_cast<const std::byte*>(&data1)+pr.diff));
				auto& recptrlist2 = (*reinterpret_cast<QList<BaseItemData*>*>(reinterpret_cast<std::byte*>(&data2)+pr.diff));

				for (auto rec: recptrlist1)
				{
					BaseItemData* subdata = meta.relations[pr.name]->createDataFunction->operator()();
					copyData(*meta.relations[pr.name], *rec, *subdata);
					recptrlist2.append(subdata);
				}
			}
			break;
		case Ramio::Meta::Type::Unset:
			break;
		}
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
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMPKey) << ";";
		else if (pr.type == Meta::Type::Bool)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMBool) << ";";
		else if (pr.type == Meta::Type::Char)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMChar) << ";";
		else if (pr.type == Meta::Type::Short)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMShort) << ";";
		else if (pr.type == Meta::Type::UShort)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMUShort) << ";";
		else if (pr.type == Meta::Type::Int)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMInt) << ";";
		else if (pr.type == Meta::Type::UInt)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMUInt) << ";";
		else if (pr.type == Meta::Type::Long)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMLong) << ";";
		else if (pr.type == Meta::Type::ULong)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMULong) << ";";
		else if (pr.type == Meta::Type::StdString)
			dbg.nospace() << pr.name << ":" << QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMStdString)) << ";";
		else if (pr.type == Meta::Type::String)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMString) << ";";
		else if (pr.type == Meta::Type::Double)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMDouble) << ";";
		else if (pr.type == Meta::Type::Uuid)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMUuid) << ";";
		else if (pr.type == Meta::Type::Time)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMTime) << ";";
		else if (pr.type == Meta::Type::Date)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMDate) << ";";
		else if (pr.type == Meta::Type::DateTime)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime) << ";";
		else if (pr.type == Meta::Type::ByteArray)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray).toHex() << ";";
		else if (pr.type == Meta::Type::Byte)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMByte) << ";";
		else if (pr.type == Meta::Type::Money)
			dbg.nospace() << pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMMoney) << ";";
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
