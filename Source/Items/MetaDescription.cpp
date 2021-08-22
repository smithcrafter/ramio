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

#include "MetaDescription.h"
#include <Log/Log.h>
// Qt5
#include <QtCore/QDebug>

namespace Ramio {
namespace Meta {

static QList<RMType> emtpyTypeList;

Property::Property(ptrdiff_t diff_, size_t size_, QString name_, Ramio::Meta::Type type_,
				   QString protoname_, QString prettyname_, Ramio::Meta::FieldRole role_, QString special_)
	: diff(diff_),
	  size(quint8(size_)),
	  type(type_),
	  role(role_),
	  special(std::move(special_)),
	  name(std::move(name_)),
	  protoname(std::move(protoname_)),
	  prettyname(std::move(prettyname_))
{
}

QDebug operator<<(QDebug dbg, const Property& pr)
{
	dbg.nospace() << " diff=" << pr.diff
				  << " size=" << pr.size
				  << " type=" << unsigned(pr.type)
				  << " role=" << unsigned(pr.role)
				  << " special=" << pr.special
				  << " name=" << pr.name
				  << " proto_name=" << pr.protoname
				  << " pretty_name=" << pr.prettyname;
	return dbg.space();
}

const QList<RMType>& TypeDescription::supportedTypes() const
{
	return emtpyTypeList;
}

static QStringList emptyStringList;

const QStringList& TypeDescription::supportedTypeNames() const
{
	return emptyStringList;
}

TypeDescription::TypeDescription(bool pfixedTypeCount)
	: fixedTypeCount(pfixedTypeCount)
{
}

TypeDescription::~TypeDescription() = default;

const QString& TypeDescription::typeName(RMType) const
{
	return emptyString;
}

const QString& Description::fieldProtoName(const QString& name) const
{
	for (const Meta::Property& pr: properties)
		if (pr.name == name)
			return pr.protoname;
	return emptyString;
}

QStringList Description::fieldNames(const QStringList& exclude) const
{
	QStringList result;
	for (const Meta::Property& pr: properties)
		if (!exclude.contains(pr.name))
			result.append(pr.name);
	return result;
}

qint8 Description::fieldIndex(const QString& name) const
{
	for (qint8 i = 0; i < properties.count(); ++i)
		if (properties[i].name == name)
			return i;
	return -1;
}

ptrdiff_t Description::fieldDiff(const QString& name) const
{
	for (qint8 i = 1; i < properties.count(); ++i)
		if (properties[i].name == name)
			return properties[i].diff;
	return 0;
}

ptrdiff_t Description::fieldDiff(const QString& name, Ramio::Meta::Type type) const
{
	for (qint8 i = 1; i < properties.count(); ++i)
		if (properties[i].type == type && properties[i].name == name)
			return properties[i].diff;
	return 0;
}

QList<quint8> Description::fieldIndexes(const QStringList& names, bool logNotFinded) const
{
	QList<quint8> result;
	for (const QString& name : names)
	{
		qint8 index = fieldIndex(name);
		if (index >= 0)
			result.append(quint8(index));
		else if (logNotFinded)
			CLOG(QObject::tr("[Meta] Not finded field %1 at %2 item").arg(name, this->itemName));
	}
	return result;
}

} // Meta::

std::shared_ptr<Meta::TypeDescription> createStandardTypeDescription(const QList<short>& types, const QStringList& names)
{
	return std::shared_ptr<Ramio::Meta::TypeDescription>(new Ramio::Meta::StandardTypeDescription(types, names));
}

} // Ramio::
