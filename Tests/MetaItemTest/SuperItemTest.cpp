/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
#include <Items/MetaStandardItemSet.h>
#include <Items/MetaItemSerialization.h>
// Qt5
#include <QtTest/QTest>
#include <QtXml/QDomDocument>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QDebug>
#include <QtCore/QBuffer>

void SuperItemTest::testSaveLoadXml()
{
	set.clear();

	auto item = createItem();
	auto data = item->data();
	set.insertItem(item);
	QCOMPARE(set.count(), 1);

	QDomDocument doc;
	QDomElement de = doc.createElement(set.meta().setName);
	doc.appendChild(de);
	set.serialize(de);

	qDebug()<<"sizeof serialize xml"<<doc.toByteArray().size();

	set.clear();
	set.deserialize(de);
	QCOMPARE(set.count(), 1);

	if (!set.isEmpty())
		QVERIFY(Ramio::Meta::equals(set.meta(), data, set.items().first()->data()));
}

void SuperItemTest::testSaveLoadJSon()
{
	set.clear();

	auto item = createItem();
	auto data = item->data();
	set.insertItem(item);
	QCOMPARE(set.count(), 1);

	QJsonDocument doc;
	QJsonArray ja;
	set.serialize(ja);
	doc.setArray(ja);

	qDebug()<<"sizeof serialize json"<<doc.toBinaryData().size();

	set.clear();

	set.deserialize(doc.array());
	QCOMPARE(set.count(), 1);

	if (!set.isEmpty())
		QVERIFY(Ramio::Meta::equals(set.meta(), data, set.items().first()->data()));

	set.clear();
}

void SuperItemTest::testSaveLoadByteArray()
{
	auto item = createItem();
	QByteArray data;
	QBuffer buffer(&data);
	buffer.open(QIODevice::ReadWrite);
	Ramio::Meta::serialize(set.meta(), item->data(), buffer);

	qDebug()<<"sizeof serialize ba"<<data.size();

	buffer.seek(0);
	auto citem = set.createItem();
	qDebug()<<"deserialize"<<Ramio::Meta::deserialize(set.meta(), citem->data(), buffer);

	QVERIFY(Ramio::Meta::equals(set.meta(), item->data(), citem->data()));
}
