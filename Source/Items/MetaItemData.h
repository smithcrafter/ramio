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

#ifndef Q_OS_ANDROID
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

QString cameCaseFirstChar(const QString& str);

#define RMETA_DATA_DECL(ItemBaseType) \
	using Base = ItemBaseType; \
	QVector<Ramio::Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE; \

#define RMETA_DATA_IMPL(ItemDataType) \
	QVector<Ramio::Meta::Property> ItemDataType::registerMetaFields() const { \
	QVector<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_DATA_START(ItemBaseType) \
	using Base = ItemBaseType; \
	QVector<Ramio::Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE { \
	QVector<Ramio::Meta::Property> res = Base::registerMetaFields(); \

#define RMETA_DATA_PROPERTY(name, type, protoname, prettyname, relationtype, special) \
	res.append(Ramio::Meta::Property(ptrdiff_t(reinterpret_cast<const std::byte*>(&name)-reinterpret_cast<const std::byte*>(static_cast<const Ramio::Data*>(this))),\
	quint8(sizeof(name)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldRole::relationtype, special));

#define RMETA_CLASS_PROPERTY(name, type, protoname, prettyname, relationtype, special) \
	res.append(Ramio::Meta::Property(ptrdiff_t(reinterpret_cast<const std::byte*>(&this->data().name)-reinterpret_cast<const std::byte*>(static_cast<const Ramio::Data*>(&this->data()))),\
	quint8(sizeof(this->data().name)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldRole::relationtype, special));

#define RMETA_DATA_FIELD(name, type, prettyname) \
	RMETA_DATA_PROPERTY(name, type, #name, prettyname, Field, QString())

#define RMETA_DATA_FIELD_C(name, type, prettyname) \
	RMETA_DATA_PROPERTY(name, type, #name, cameCaseFirstChar(prettyname), Field, QString())

#define RMETA_DATA_FKEY_ID(name, prettyname) \
	RMETA_DATA_PROPERTY(name, PKey, #name, prettyname, FKey, "id")

#define RMETA_DATA_FKEY_ID_C(name, prettyname) \
	RMETA_DATA_PROPERTY(name, PKey, #name, cameCaseFirstChar(prettyname), FKey, "id")

#define RMETA_DATA_VALUE(name, type, prettyname) \
	RMETA_DATA_PROPERTY(name, type, #name, prettyname, Value, QString())

#define RMETA_DATA_FUNCTION(ItemDataStruct, name, type, protoname, prettyname, relationtype) \
	{ptrdiff_t diffnk = Ramio::MetaItemData::DataFunctionPrt(static_cast<Ramio::MetaItemData::dataFunction>(&ItemDataStruct::name)).dif;\
	res.append(Ramio::Meta::Property(diffnk, quint8(sizeof(ptrdiff_t)), QStringLiteral(#name), Ramio::Meta::Type::type, \
	QStringLiteral(protoname), prettyname, Ramio::Meta::FieldRole::relationtype));}

#define RMETA_DATA_BEGIN \
	RMETA_DATA_START(Ramio::MetaItemData)

#define RMETA_DATA_END \
	return res; }

namespace Ramio {

struct RAMIO_LIB_EXPORT AbstractMetaItemData
{
	virtual QVector<Meta::Property> registerMetaFields() const = 0;
};

struct RAMIO_LIB_EXPORT MetaItemData : public BaseItemData, public AbstractMetaItemData
{
	using Base = Ramio::ItemData;
	QVector<Meta::Property> registerMetaFields() const Q_DECL_OVERRIDE;
	virtual AbstractMetaItemData* extendedData() {return Q_NULLPTR;}
	virtual const AbstractMetaItemData* extendedData() const {return Q_NULLPTR;}

	typedef QVariant (MetaItemData::*dataFunction)() const;
	union DataFunctionPrt
	{
		dataFunction memfunc_ptr;
		ptrdiff_t dif;
		DataFunctionPrt(ptrdiff_t prdif) : dif(prdif) {}
		DataFunctionPrt(dataFunction ptrFunction) : memfunc_ptr(ptrFunction) {}
	};
	QVariant call(ptrdiff_t
#ifndef QT_DEBUG
				  prdif
#endif
				  ) const
	{
#ifdef QT_DEBUG
		return QVariant();
		// SIGSEGV Segmentation fault
		// return (this->*(DataFunctionPrt(prdif).memfunc_ptr))();
#else
		return (this->*(DataFunctionPrt(prdif).memfunc_ptr))();
#endif
	}
};

struct RAMIO_LIB_EXPORT MetaStandardItemData : public MetaItemData
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

RAMIO_LIB_EXPORT bool equals(const Meta::Description& meta, const Data& data1, const Data& data2);

RAMIO_LIB_EXPORT bool equalsData(const Meta::Description& meta, const MetaItemData& data1, const MetaItemData& data2);

template<typename FIELDTYPE>
bool less(const Ramio::ItemData& left, const Ramio::ItemData& right, ptrdiff_t diff)
{
	return left.field<FIELDTYPE>(diff) < right.field<FIELDTYPE>(diff);
}

RAMIO_LIB_EXPORT bool less(Ramio::Meta::Type fieldtype, const Ramio::ItemData& left, const Ramio::ItemData& right, ptrdiff_t diff);

} // Meta ::

RAMIO_LIB_EXPORT QDebug operator << (QDebug dbg, const MetaItemData& data);

} // Ramio::
