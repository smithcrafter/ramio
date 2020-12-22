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


#include <QApplication>
#include <QDebug>
#include <Items/MetaStandardItemSet.h>
#include "SuperItem.h"
#include "TestItems.h"

#define PRINT_QDEBUG_SIZEOF_ALINGOF(TYPE) \
	qDebug()<<#TYPE" sizeof ="<<sizeof(TYPE)<<"alignof ="<<alignof(TYPE);

void printSizes()
{
	qDebug()<<"=====";
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::ItemData)
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::AbstractMetaItemData);
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::MetaItemData);
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::MetaStandardItemData);
	qDebug()<<"=====";
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::Item)
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::StructItem<Ramio::ItemData>);
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::StructItem<Ramio::MetaItemData>);
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::StructItem<Ramio::MetaStandardItemData>);
	PRINT_QDEBUG_SIZEOF_ALINGOF(Ramio::StandardItem<Ramio::MetaStandardItemData>);
	qDebug()<<"=====";
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVData)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVMetaData)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVItem)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVMetaItem)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVItemSet)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVMetaItemSet)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVSet)
	PRINT_QDEBUG_SIZEOF_ALINGOF(KVMetaSet)
	qDebug()<<"=====";
}

void printValueToString()
{
	auto item = createItem();
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::PKey) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::PKey>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::PKey>(item->data().id);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Bool) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Bool>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Bool>(item->data().boolValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Char) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Char>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Char>(item->data().charValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Short) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Short>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Short>(item->data().shortintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::UShort) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::UShort>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::UShort>(item->data().unsignedshortintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Int) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Int>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Int>(item->data().intValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::UInt) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::UInt>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::UInt>(item->data().unsignedintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Long) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Long>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Long>(item->data().longlongValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::ULong) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::ULong>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::ULong>(item->data().unsignedlonglongValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Float) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Float>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Float>(item->data().floatValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Double) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Double>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Double>(item->data().doubleValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::StdString) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::StdString>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::StdString>(item->data().StdStringValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::String) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::String>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::String>(item->data().QStringValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Uuid) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Uuid>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Uuid>(item->data().QUuidValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Time) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Time>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Time>(item->data().QTimeValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Date) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Date>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Date>(item->data().QDateValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::DateTime) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::DateTime>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::DateTime>(item->data().QDateTimeValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::ByteArray) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::ByteArray>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::ByteArray>(item->data().QByteArrayValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Byte) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Byte>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Byte>(item->data().ByteValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Money) << sizeof(Ramio::Meta::RMetaType<Ramio::Meta::Type::Money>::type)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Money>(item->data().MoneyValue);
	delete item;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	printSizes();
	printValueToString();
	return 0;
}
