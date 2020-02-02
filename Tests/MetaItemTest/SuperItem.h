/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Tests, a Qt-based casual C++ classes for quick application writing.
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

#include <Items/MetaItems.h>
#include <QtCore/QDateTime>

struct SuperItemRecord : Ramio::MetaItemData
{
	RMetaPKey quint64Value = UNUSEDID;
	RMetaBool boolValue = false;
	RMetaChar charValue = char(0);
	RMetaShort shortintValue = 0;
	RMetaUShort unsignedshortintValue = 0;
	RMetaInt intValue = 0;
	RMetaUInt unsignedintValue = 0;
	RMetaLong longlongValue = 0;
	RMetaULong unsignedlonglongValue = 0;
	RMetaFloat floatValue = 0.0;
	RMetaDouble doubleValue = 0.0;
	RMetaStdString StdStringValue;
	RMetaString QStringValue;
	RMetaUuid QUuidValue;
	RMetaTime QTimeValue;
	RMetaDate QDateValue;
	RMetaDateTime QDateTimeValue;
	RMetaByteArray QByteArrayValue;
	RMetaByte ByteValue = 0x00;
	RMetaMoney MoneyValue = 0.0;

	RMETA_OBJECT_BEGIN
	RMETA_OBJECT_FIELD(quint64Value, PKey, "PKey")
	RMETA_OBJECT_FIELD(boolValue, Bool, "Bool")
	RMETA_OBJECT_FIELD(charValue, Char, "Char")
	RMETA_OBJECT_FIELD(shortintValue, Short, "Short")
	RMETA_OBJECT_FIELD(unsignedshortintValue, UShort, "UShort")
	RMETA_OBJECT_FIELD(intValue, Int, "Int")
	RMETA_OBJECT_FIELD(unsignedintValue, UInt, "UInt")
	RMETA_OBJECT_FIELD(longlongValue, Long, "Long")
	RMETA_OBJECT_FIELD(unsignedlonglongValue, ULong, "ULong")
	RMETA_OBJECT_FIELD(floatValue, Float, "Float")
	RMETA_OBJECT_FIELD(doubleValue, Double, "Double")
	RMETA_OBJECT_FIELD(StdStringValue, StdString, "StdString")
	RMETA_OBJECT_FIELD(QStringValue, String, "String")
	RMETA_OBJECT_FIELD(QUuidValue, Uuid, "Uuid")
	RMETA_OBJECT_FIELD(QTimeValue, Time, "Time")
	RMETA_OBJECT_FIELD(QDateValue, Date, "Date")
	RMETA_OBJECT_FIELD(QDateTimeValue, DateTime, "DateTime")
	RMETA_OBJECT_FIELD(QByteArrayValue, ByteArray, "ByteArray")
	RMETA_OBJECT_FIELD(ByteValue, Byte, "Byte")
	RMETA_OBJECT_FIELD(MoneyValue, Money, "Money")
	RMETA_OBJECT_END
};


GENERATE_METACLASS(SuperItem, SuperItemRecord)

GENERATE_ITEMSET(SuperItemSet, SuperItem, SuperItemRecord)

GENERATE_METASET(MetaSuperItemSet, SuperItem, SuperItemRecord, "MetaSuperItemSet", "SuperItem")
