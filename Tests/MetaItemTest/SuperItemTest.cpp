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

#include "SuperItemTest.h"
// Qt5
#include <QtTest/QTest>
#include <QtXml/QDomDocument>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>

void SuperItemTest::printSizes()
{
	qDebug()<<"sizeof(Ramio::ItemData) ="<<sizeof(Ramio::ItemData);
	qDebug()<<"sizeof(Ramio::AbstractMetaItemData) ="<<sizeof(Ramio::AbstractMetaItemData);
	qDebug()<<"sizeof(Ramio::MetaItemData) ="<<sizeof(Ramio::MetaItemData);
	qDebug()<<"sizeof(Ramio::MetaBaseItemData) ="<<sizeof(Ramio::MetaBaseItemData);

	qDebug()<<"sizeof(Ramio::Item) ="<<sizeof(Ramio::Item);
	qDebug()<<"sizeof(Ramio::StructItem<Ramio::ItemData>) ="<<sizeof(Ramio::StructItem<Ramio::ItemData>);
	qDebug()<<"sizeof(Ramio::StructItem<Ramio::MetaItemData>) ="<<sizeof(Ramio::StructItem<Ramio::MetaItemData>);
	qDebug()<<"sizeof(Ramio::StructItem<Ramio::MetaBaseItemData>) ="<<sizeof(Ramio::StructItem<Ramio::MetaBaseItemData>);
	qDebug()<<"sizeof(Ramio::BaseItem<Ramio::MetaBaseItemData>) ="<<sizeof(Ramio::BaseItem<Ramio::MetaBaseItemData>);
}

void SuperItemTest::printValueToString()
{
	auto item = createItem();
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::PKey)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::PKey>(item->data().id);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Bool)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Bool>(item->data().boolValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Char)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Char>(item->data().charValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Short)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Short>(item->data().shortintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::UShort)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::UShort>(item->data().unsignedshortintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Int)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Int>(item->data().intValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::UInt)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::UInt>(item->data().unsignedintValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Long)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Long>(item->data().longlongValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::ULong)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::ULong>(item->data().unsignedlonglongValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Float)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Float>(item->data().floatValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Double)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Double>(item->data().doubleValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::StdString)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::StdString>(item->data().StdStringValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::String)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::String>(item->data().QStringValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Uuid)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Uuid>(item->data().QUuidValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Time)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Time>(item->data().QTimeValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Date)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Date>(item->data().QDateValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::DateTime)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::DateTime>(item->data().QDateTimeValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::ByteArray)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::ByteArray>(item->data().QByteArrayValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Byte)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Byte>(item->data().ByteValue);
	qDebug()<< Ramio::Meta::typeName(Ramio::Meta::Type::Money)
			<< Ramio::Meta::valueToString<Ramio::Meta::Type::Money>(item->data().MoneyValue);
	delete item;
}

void SuperItemTest::testSaveLoadXml()
{
	auto item = createItem();
	auto data = item->data();
	set.addItem(item);
	QCOMPARE(set.count(), 1);

	QDomDocument doc;
	QDomElement de = doc.createElement(set.meta().setName);
	doc.appendChild(de);

	set.serialize(de);

	set.clear();
	set.deserialize(de);
	QCOMPARE(set.count(), 1);

	if (!set.isEmpty())
		QVERIFY(Ramio::Meta::equals(set.meta(), data, set.items().first()->data()));

	set.clear();
}

void SuperItemTest::testSaveLoadJSon()
{
	auto item = createItem();
	auto data = item->data();
	set.addItem(item);
	QCOMPARE(set.count(), 1);

	QJsonDocument doc;
	QJsonArray ja;
	set.serialize(ja);

	doc.setArray(ja);
	set.clear();

	set.deserialize(doc.array());
	QCOMPARE(set.count(), 1);

	if (!set.isEmpty())
		QVERIFY(Ramio::Meta::equals(set.meta(), data, set.items().first()->data()));

	set.clear();
}

SuperItem* SuperItemTest::createItem()
{
	auto item = set.createItem();
	item->data().id = 1;
	item->data().quint64Value = 123;
	item->data().boolValue = true;
	item->data().charValue = 'a';
	item->data().shortintValue = -23;
	item->data().unsignedshortintValue = 5454;
	item->data().intValue = -23434;
	item->data().unsignedintValue = 23324;
	item->data().longlongValue = -234324;
	item->data().unsignedlonglongValue = 2344324;
	item->data().floatValue = 2.3;
	item->data().doubleValue = 23423.23;
	item->data().StdStringValue = "hello";
	item->data().QStringValue = "world";
	item->data().QUuidValue = QUuid::createUuid();
	item->data().QTimeValue = QTime::currentTime();
	item->data().QDateValue = QDate::currentDate();
	item->data().QDateTimeValue = QDateTime::currentDateTime();
	item->data().QByteArrayValue = QByteArray::fromHex("0011FF0A");
	item->data().ByteValue = 255;
	item->data().MoneyValue = 323423.89;
	return item;
}
