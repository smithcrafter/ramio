#pragma once

#include <Items/MetaItems.h>
#include <QtCore/QDateTime>

struct SuperItemRecord : Ramio::MetaItemData
{
	RMetaPKey quint64Value;
	RMetaBool boolValue;
	RMetaChar charValue;
	RMetaShort shortintValue;
	RMetaUShort unsignedshortintValue;
	RMetaInt intValue;
	RMetaUInt unsignedintValue;
	RMetaLong longlongValue;
	RMetaULong unsignedlonglongValue;
	RMetaFloat floatValue;
	RMetaDouble doubleValue;
	RMetaString QStringValue;
	RMetaUuid QUuidValue;
	RMetaTime QTimeValue;
	RMetaDate QDateValue;
	RMetaDateTime QDateTimeValue;
	RMetaByteArray QByteArrayValue;
	RMetaByte ByteValue;
	RMetaMoney MoneyValue;

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


GENERATE_HEADER_CLASS(SuperItem, SuperItemRecord)

GENERATE_CLASS_SET(SuperItemSet, SuperItem, SuperItemRecord)

GENERATE_CLASS_METASET(MetaSuperItemSet, SuperItem, SuperItemRecord, "Notebook", "Note")
