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

#include "SuperItem.h"

SuperItem* createItem()
{
	auto item = new SuperItem();
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
