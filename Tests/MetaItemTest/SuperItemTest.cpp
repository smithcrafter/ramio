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
#include <QtXml/QDomDocument>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtTest/QTest>

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
	item->createUuidIfNull();
	item->data().type = 2;
	item->data().floatValue = 2.3;
	item->data().doubleValue = 23423.23;
	item->data().MoneyValue = 323423.89;
	item->data().QByteArrayValue = QByteArray::fromHex("0011FF0A");
	item->data().StdStringValue = "hello";
	item->data().QStringValue = "world";

	return item;
}
