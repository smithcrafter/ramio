/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
#include <QtCore/QDebug>

namespace Ramio {

QList<Meta::Property> MetaItemData::registerMetaFields() const
{
	QList<Meta::Property> res;
	RMETA_OBJECT_PROPERTY(id, PKey, "Id", QObject::tr("Идентификатор"), PKey)
	RMETA_OBJECT_PROPERTY(uuid, Uuid, "Uuid", QObject::tr("Глобальный идентификатор"), Field)
	RMETA_OBJECT_PROPERTY(type, Int, "Type", QObject::tr("Тип"), Type)
	return res;
}

bool equalsField(const Meta::Property& pr, const MetaItemData& data1, const MetaItemData& data2)
{
	if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
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
	else if (pr.type == Meta::Type::Int)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaInt) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaInt))
			return false;
	}
	else if (pr.type == Meta::Type::Long)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaLong) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaLong))
			return false;
	}
	else if (pr.type == Meta::Type::String)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaString) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaString))
			return false;
	}
	else if (pr.type == Meta::Type::Double)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaDouble) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaDouble))
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
	else if (pr.type == Meta::Type::Money)
	{
		if (CAST_CONST_DATA1REL_TO_TYPEREL(RMetaMoney) != CAST_CONST_DATA2REL_TO_TYPEREL(RMetaMoney))
			return false;
	}
	else
		Q_ASSERT(0);
	return true;
}

bool equals(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2)
{
	for (const auto& pr: meta.properties)
		if (!equalsField(pr, data1, data2))
			return false;
	return true;
}

bool equalsData(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2)
{
	for (int i = 2; i < meta.properties.count(); i++)
	{
		const auto& pr = meta.properties[i];
		if (!equalsField(pr, data1, data2))
			return false;
	}
	return true;
}

QDebug operator << (QDebug dbg, const MetaItemData& data)
{
	auto properties = data.registerMetaFields();

	for (const auto& pr: properties)
	{
		if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey) << ";";
		else if (pr.type == Meta::Type::Bool)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool) << ";";
		else if (pr.type == Meta::Type::Int)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt) << ";";
		else if (pr.type == Meta::Type::Long)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong) << ";";
		else if (pr.type == Meta::Type::String)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaString) << ";";
		else if (pr.type == Meta::Type::Double)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble) << ";";
		else if (pr.type == Meta::Type::Uuid)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid) << ";";
		else if (pr.type == Meta::Type::Time)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime) << ";";
		else if (pr.type == Meta::Type::Date)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate) << ";";
		else if (pr.type == Meta::Type::DateTime)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime) << ";";
		else if (pr.type == Meta::Type::Money)
			dbg.nospace() <<pr.name << ":" << CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney) << ";";
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
