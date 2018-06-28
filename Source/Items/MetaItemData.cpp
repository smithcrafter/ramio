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

#include "MetaItemData.h"
// Qt
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

QString Description::fieldName(const QString& name) const
{
	Q_FOREACH(Meta::Property pr, properties)
		if (pr.name == name)
			return pr.protoname;
	return QString();
}

quint8 Description::fieldIndex(const QString& name) const
{
	for (quint8 i = 0; i < properties.count(); i++)
		if (properties[i].name == name)
			return i;
	return 0;
}

} // Meta::

QList<Meta::Property> MetaItemData::registerMetaFields()
{
	QList<Meta::Property> res;
	RMETA_OBJECT_FIELD(id, PKey, "Id", QObject::tr("Идентификатор"), PKey)
	RMETA_OBJECT_FIELD(type, Int, "Type", QObject::tr("Тип"), Field)
	RMETA_OBJECT_FIELD(uuid, Uuid, "Uuid", QObject::tr("Глобальный идентификатор"), Field)
	return res;
}

} // Ramio::
