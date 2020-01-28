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

#pragma once

#include "ItemData.h"
#include "MetaDescription.h"

#define RMETA_OBJECT_DECL(ItemBaseType) \
	using Base = ItemBaseType; \
	QVector<Ramio::Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE; \

#define RMETA_OBJECT_IMPL(ItemDataType) \
	QVector<Ramio::Meta::Property> ItemDataType::registerMetaFields() const { \
	QVector<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_OBJECT_START(ItemBaseType) \
	using Base = ItemBaseType; \
	QVector<Ramio::Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE { \
	QVector<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_OBJECT_PROPERTY(name, type, protoname, prettyname, relationtype) \
	res.append(Ramio::Meta::Property(ptrdiff_t(reinterpret_cast<const std::byte*>(&name)-reinterpret_cast<const std::byte*>(this)),\
	quint8(sizeof(name)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldRole::relationtype));

#define RMETA_OBJECT_FIELD(name, type, prettyname) \
	RMETA_OBJECT_PROPERTY(name, type, #name, prettyname, Field)

QString cameCaseFirstChar(const QString& str);
#define RMETA_OBJECT_FIELD_C(name, type, prettyname) \
	RMETA_OBJECT_PROPERTY(name, type, #name, cameCaseFirstChar(prettyname), Field)

#define RMETA_OBJECT_FUNCTION(ItemDataStruct, name, type, protoname, prettyname, relationtype) \
	{ptrdiff_t diffnk = Ramio::DataFunctionPrt(reinterpret_cast<Ramio::DataFunctionPrt::dataFunction>(&ItemDataStruct::name)).dif;\
	res.append(Ramio::Meta::Property(diffnk, quint8(sizeof(ptrdiff_t)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldRole::relationtype));}

#define RMETA_OBJECT_BEGIN \
	RMETA_OBJECT_START(Ramio::MetaItemData)

#define RMETA_OBJECT_END \
	return res; }

namespace Ramio {

struct RAMIO_LIB_EXPORT AbstractMetaItemData
{
	virtual QVector<Meta::Property> registerMetaFields() const = 0;
};

struct RAMIO_LIB_EXPORT MetaItemData : public ItemData, public AbstractMetaItemData
{
	using Base = Ramio::ItemData;
	QVector<Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE;
	virtual AbstractMetaItemData* extendedData() {return Q_NULLPTR;}
	virtual const AbstractMetaItemData* extendedData() const {return Q_NULLPTR;}
};

struct RAMIO_LIB_EXPORT MetaBaseItemData : public MetaItemData
{
	using Base = MetaItemData;

	RMetaUuid uuid;
	RMetaShort type = 0;
	RMetaShort state = 0;
	RMetaInt flags = 0;

	QVector<Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE;
};


template<typename BASEMETAITEMDATA, typename EXTENDEDTDATA>
struct ExtendedItemData : public BASEMETAITEMDATA
{
	EXTENDEDTDATA extended;
	QVector<Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE
	{
		QVector<Meta::Property> res = BASEMETAITEMDATA::registerMetaFields();
		Q_FOREACH (Meta::Property pr, extended.registerMetaFields())
		{
			pr.diff += ptrdiff_t(reinterpret_cast<const std::byte*>(&extended)-reinterpret_cast<const std::byte*>(this));
			pr.role = Meta::FieldRole::Extended;
			res.append(pr);
		}
		return res;
	}
	AbstractMetaItemData* extendedData() Q_DECL_OVERRIDE {return &extended;}
	const AbstractMetaItemData* extendedData() const Q_DECL_OVERRIDE {return &extended;}
};

namespace Meta {

RAMIO_LIB_EXPORT bool equals(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2);

RAMIO_LIB_EXPORT bool equalsData(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2);

template<typename FIELDTYPE>
bool less(const Ramio::ItemData& left, const Ramio::ItemData& right, ptrdiff_t diff)
{
	return left.field<FIELDTYPE>(diff) < right.field<FIELDTYPE>(diff);
}

RAMIO_LIB_EXPORT bool less(Ramio::Meta::Type fieldtype, const Ramio::ItemData& left, const Ramio::ItemData& right, ptrdiff_t diff);

} // Meta ::

RAMIO_LIB_EXPORT QDebug operator << (QDebug dbg, const MetaItemData& data);

union DataFunctionPrt
{
	typedef QVariant (MetaItemData::*dataFunction)() const;
	dataFunction memfunc_ptr;
	ptrdiff_t dif;
	DataFunctionPrt(ptrdiff_t prdif) : dif(prdif) {}
	DataFunctionPrt(dataFunction ptrFunction) : memfunc_ptr(ptrFunction) {}
};

} // Ramio::
