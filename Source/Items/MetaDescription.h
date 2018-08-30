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
#include <QtCore/QMap>
#include <QtCore/QScopedPointer>
#include <memory>
class QDebug;

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
	Type,
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

struct DLL_EXPORT TypeDescription
{
	TypeDescription(bool fixedTypeCount = false);
	virtual ~TypeDescription() = default;

	virtual TypeDescription* clone() const {return new TypeDescription(fixedTypeCount);}

	virtual const QString& typeName(RMetaInt);
	virtual QList<RMetaInt> supportedTypes();
	virtual const QStringList& supportedTypeNames();

	const bool fixedTypeCount;
};

struct DLL_EXPORT Description
{
	QString itemName;
	QString setName;
	QList<Property> properties;
	size_t size;
	QMap<QString, const Description*> relations;

	std::unique_ptr<TypeDescription> typeDescription;

	std::unique_ptr<TypeDescription> cloneTypeDescription() const {return std::unique_ptr<TypeDescription>(
					typeDescription ? typeDescription->clone() : Q_NULLPTR);}

	QString fieldName(const QString& name) const;
	quint8 fieldIndex(const QString& name) const;

	void setRelation(const QString& name, const Description* desc) {relations[name] = desc;}
};

} // Meta::
} // Ramio::
