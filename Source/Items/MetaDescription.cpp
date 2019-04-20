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

#include "MetaDescription.h"
// Qt5
#include <QtCore/QDebug>

namespace Ramio {
namespace Meta {

Property::Property(ptrdiff_t dif_, quint8 size_, QString name_, Meta::Type type_,
				   QString protoname_, QString prettyname_, FieldType relationtype_)
	: dif(dif_),
	  size(size_),
	  name(std::move(name_)),
	  type(type_),
	  relationtype(relationtype_),
	  protoname(std::move(protoname_)),
	  prettyname(std::move(prettyname_))
{
}

QDebug operator<<(QDebug dbg, const Property& pr)
{
	dbg.nospace() << " dif=" << pr.dif
				  << " size=" << pr.size
				  << " name=" << pr.name
				  << " type=" << int(pr.type)
				  << " proto_name=" << pr.protoname
				  << " rel_type=" << int(pr.relationtype)
				  << " pretty_name=" << pr.prettyname;
	return dbg.space();
}

QList<int> TypeDescription::supportedTypes()
{
	return QList<int>();
}

const QStringList& TypeDescription::supportedTypeNames()
{
	return emptyStringList;
}

TypeDescription::TypeDescription(bool pfixedTypeCount)
	: fixedTypeCount(pfixedTypeCount)
{
}

const QString& TypeDescription::typeName(RMetaInt)
{
	return emptyString;
}

const QString& Description::fieldName(const QString& name) const
{
	for (const Meta::Property& pr: properties)
		if (pr.name == name)
			return pr.protoname;
	return emptyString;
}

qint8 Description::fieldIndex(const QString& name) const
{
	for (quint8 i = 0; i < properties.count(); i++)
		if (properties[i].name == name)
			return i;
	return -1;
}

QList<quint8> Description::fieldIndexes(const QStringList& names) const
{
	QList<quint8> result;
	for (const QString& name : names)
	{
		qint8 index = fieldIndex(name);
		if (index >= 0)
			result.append(index);
	}
	return result;
}

} // Meta::
} // Ramio::
