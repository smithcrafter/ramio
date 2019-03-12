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

namespace Ramio {

QList<Meta::Property> MetaItemData::registerMetaFields()
{
	QList<Meta::Property> res;
	RMETA_OBJECT_FIELD(id, PKey, "Id", QObject::tr("Идентификатор"), PKey)
	RMETA_OBJECT_FIELD(type, Int, "Type", QObject::tr("Тип"), Type)
	RMETA_OBJECT_FIELD(uuid, Uuid, "Uuid", QObject::tr("Глобальный идентификатор"), Field)
	return res;
}

} // Ramio::
