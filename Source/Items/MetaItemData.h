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

#pragma once

#include "ItemData.h"
#include <QtCore/QList>
#include <QtCore/QMap>
class QDebug;

#define RMETA_OBJECT_START(ItemType) \
	using Base = ItemType; \
	QList<Ramio::Meta::Property> registerMetaFields() Q_DECL_OVERRIDE { \
	QList<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_OBJECT_FIELD(name, type, protoname, prettyname, relationtype) \
	res.append(Ramio::Meta::Property(ptrdiff_t(reinterpret_cast<char*>(&name)-reinterpret_cast<char*>(this)),\
	quint8(sizeof(name)), #name, Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldType::relationtype));

#define RMETA_OBJECT_END \
	return res; }

namespace Ramio {

namespace Meta {

enum class Type
{
	Unset = 0,
	PKey,
	Int,
	Uuid,
	Double,
	String,
	DateTime,
	Money
};

enum class FieldType
{
	Field = 0,
	PKey,
	FKey,
	Extended
};

struct DLL_EXPORT Property
{
	Property(ptrdiff_t dif, quint8 size, QString name, Meta::Type type, QString protoname,
			 QString prettyname = QString(), FieldType relationtype = FieldType::Field);
/// Смещение от начала структуры и размер
	ptrdiff_t dif;
	size_t size;
/// имя переменной, тип
	QString name;
	Meta::Type type;
/// имя переменной для бд, сериализации, тип отношения в бд
	FieldType relationtype;
	QString protoname;
/// наименование переменной, заголовок таблиц
	QString prettyname;
};

QDebug operator << (QDebug dbg, const Property& pr);

struct DLL_EXPORT Description
{
	QString itemName;
	QString setName;
	QList<Property> properties;
	int size;
	QMap<QString, const Description*> relations;

	QString fieldName(const QString& name) const;
	quint8 fieldIndex(const QString& name) const;

	void setRelation(const QString& name, const Description* desc) {relations[name] = desc;}

};

} // Meta::


struct DLL_EXPORT BaseMetaItemData
{
	virtual QList<Meta::Property> registerMetaFields() {return {};}
};

struct DLL_EXPORT MetaItemData : public ItemData, public BaseMetaItemData
{
	using Base = ItemData;
	QList<Meta::Property> registerMetaFields() Q_DECL_OVERRIDE;
	virtual BaseMetaItemData* extendedData() {return Q_NULLPTR;}
};

template<typename BASEMETAITEMDATA, typename EXTENDEDTDATA>
struct ExtendedItemData : public BASEMETAITEMDATA
{
	EXTENDEDTDATA extended;
	QList<Meta::Property> registerMetaFields() Q_DECL_OVERRIDE
	{
		QList<Meta::Property> res = BASEMETAITEMDATA::registerMetaFields();
		Q_FOREACH(Meta::Property pr, extended.registerMetaFields())
		{
			pr.dif=pr.dif+ptrdiff_t(reinterpret_cast<char*>(&extended)-reinterpret_cast<char*>(this));
			pr.relationtype = Meta::FieldType::Extended;
			res.append(pr);
		}
		return res;
	}
	BaseMetaItemData* extendedData() Q_DECL_OVERRIDE {return &extended;}
};

} // Ramio::
