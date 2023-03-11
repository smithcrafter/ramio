/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ReflItems.h"
#include <QtCore/QDateTime>

namespace Ramio {

ReflSet::ReflSet(const Meta::Description& meta, QObject* parent)
	: AbstractListSet(items_, parent),
	  meta_(meta)
{
}

Item* ReflSet::createItem() const
{
	Item* item = Q_NULLPTR;
	if (meta_.size<=8)
		item = new ReflItem<8>();
	else if (meta_.size<=32)
		item =  new ReflItem<32>();
	else if (meta_.size<=128)
		item = new ReflItem<128>();
	else if (meta_.size<=1024)
		item = new ReflItem<1024>();
	else
		return Q_NULLPTR;
	auto& data = item->data();
	for (auto pr: meta_.properties)
	{
		if (pr.type == Meta::Type::PKey)
			CAST_DATAREL_TO_TYPEREL(RMPKey) = 0;
		else if (pr.type == Meta::Type::Type)
			CAST_DATAREL_TO_TYPEREL(RMType) = 0;
		else if (pr.type == Meta::Type::State)
			CAST_DATAREL_TO_TYPEREL(RMState) = 0;
		else if (pr.type == Meta::Type::Flags)
			CAST_DATAREL_TO_TYPEREL(RMFlags) = 0;
		else if (pr.type == Meta::Type::Bool)
			CAST_DATAREL_TO_TYPEREL(RMBool) = 0;
		else if (pr.type == Meta::Type::Char)
			CAST_DATAREL_TO_TYPEREL(RMChar) = 0;
		else if (pr.type == Meta::Type::Short)
			CAST_DATAREL_TO_TYPEREL(RMShort) = 0;
		else if (pr.type == Meta::Type::UShort)
			CAST_DATAREL_TO_TYPEREL(RMUShort) = 0;
		else if (pr.type == Meta::Type::Int)
			CAST_DATAREL_TO_TYPEREL(RMInt) = 0;
		else if (pr.type == Meta::Type::UInt)
			CAST_DATAREL_TO_TYPEREL(RMUInt) = 0;
		else if (pr.type == Meta::Type::Long)
			CAST_DATAREL_TO_TYPEREL(RMLong) = 0;
		else if (pr.type == Meta::Type::ULong)
			CAST_DATAREL_TO_TYPEREL(RMULong) = 0;
		else if (pr.type == Meta::Type::Float)
			CAST_DATAREL_TO_TYPEREL(RMFloat) = 0;
		else if (pr.type == Meta::Type::Double)
			CAST_DATAREL_TO_TYPEREL(RMDouble) = 0;
		else if (pr.type == Meta::Type::StdString)
			new (&CAST_DATAREL_TO_TYPEREL(RMStdString)) RMStdString();
		else if (pr.type == Meta::Type::String)
			new (&CAST_DATAREL_TO_TYPEREL(RMString)) RMString();
		else if (pr.type == Meta::Type::Uuid)
			new (&CAST_DATAREL_TO_TYPEREL(RMUuid)) RMUuid();
		else if (pr.type == Meta::Type::Time)
			new (&CAST_DATAREL_TO_TYPEREL(RMTime)) RMTime();
		else if (pr.type == Meta::Type::Date)
			new (&CAST_DATAREL_TO_TYPEREL(RMDate)) RMDate();
		else if (pr.type == Meta::Type::DateTime)
			new (&CAST_DATAREL_TO_TYPEREL(RMDateTime)) RMDateTime();
		else if (pr.type == Meta::Type::ByteArray)
			new (&CAST_DATAREL_TO_TYPEREL(RMByteArray)) RMByteArray();
		else if (pr.type == Meta::Type::StringList)
			new (&CAST_DATAREL_TO_TYPEREL(RMStringList)) RMStringList();
		else if (pr.type == Meta::Type::Byte)
			CAST_DATAREL_TO_TYPEREL(RMByte) = 0;
		else if (pr.type == Meta::Type::Money)
			CAST_DATAREL_TO_TYPEREL(RMMoney) = 0;
		else if (pr.type == Meta::Type::RecordPrtList)
			new (&CAST_DATAREL_TO_TYPEREL(QList<BaseItemData*>)) QList<BaseItemData*>();
		else if (pr.type == Meta::Type::PKeyList)
			new (&CAST_DATAREL_TO_TYPEREL(RMPKeyList)) RMPKeyList();
		else if (pr.type == Meta::Type::TypeList)
			new (&CAST_DATAREL_TO_TYPEREL(RMTypeList)) RMTypeList();
		else
			Q_ASSERT_X(0, "createItem", qPrintable(QString("Type \"%1\" not supported").arg(Meta::typeName(pr.type))));
	}
	return item;
}

} // Ramio::
