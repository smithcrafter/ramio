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
	RMPKey quint64Value = UNUSEDID;
	RMBool boolValue = false;
	RMChar charValue = char(0);
	RMShort shortintValue = 0;
	RMUShort unsignedshortintValue = 0;
	RMInt intValue = 0;
	RMUInt unsignedintValue = 0;
	RMLong longlongValue = 0;
	RMULong unsignedlonglongValue = 0;
	RMFloat floatValue = 0.0;
	RMDouble doubleValue = 0.0;
	RMStdString StdStringValue;
	RMString QStringValue;
	RMUuid QUuidValue;
	RMTime QTimeValue;
	RMDate QDateValue;
	RMDateTime QDateTimeValue;
	RMByteArray QByteArrayValue;
	RMByte ByteValue = 0x00;
	RMMoney MoneyValue = 0.0;

	RMETA_DATA_BEGIN
	RMETA_DATA_FIELD(quint64Value, PKey, "PKey")
	RMETA_DATA_FIELD(boolValue, Bool, "Bool")
	RMETA_DATA_FIELD(charValue, Char, "Char")
	RMETA_DATA_FIELD(shortintValue, Short, "Short")
	RMETA_DATA_FIELD(unsignedshortintValue, UShort, "UShort")
	RMETA_DATA_FIELD(intValue, Int, "Int")
	RMETA_DATA_FIELD(unsignedintValue, UInt, "UInt")
	RMETA_DATA_FIELD(longlongValue, Long, "Long")
	RMETA_DATA_FIELD(unsignedlonglongValue, ULong, "ULong")
	RMETA_DATA_FIELD(floatValue, Float, "Float")
	RMETA_DATA_FIELD(doubleValue, Double, "Double")
	RMETA_DATA_FIELD(StdStringValue, StdString, "StdString")
	RMETA_DATA_FIELD(QStringValue, String, "String")
	RMETA_DATA_FIELD(QUuidValue, Uuid, "Uuid")
	RMETA_DATA_FIELD(QTimeValue, Time, "Time")
	RMETA_DATA_FIELD(QDateValue, Date, "Date")
	RMETA_DATA_FIELD(QDateTimeValue, DateTime, "DateTime")
	RMETA_DATA_FIELD(QByteArrayValue, ByteArray, "ByteArray")
	RMETA_DATA_FIELD(ByteValue, Byte, "Byte")
	RMETA_DATA_FIELD(MoneyValue, Money, "Money")
	RMETA_DATA_END
};


GENERATE_METACLASS(SuperItem, SuperItemRecord)

GENERATE_ITEMSET(SuperItemSet, SuperItem, SuperItemRecord)

GENERATE_METASET(MetaSuperItemSet, SuperItem, SuperItemRecord, "MetaSuperItemSet", "SuperItem")

SuperItem* createItem();
