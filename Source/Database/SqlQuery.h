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

#pragma once

#include "ramio.h"
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QUuid>

namespace Ramio {

enum class SqlQueryType
{
	Insert,
	Update,
	Delete
};

struct RAMIO_LIB_EXPORT SqlQuery
{
public:
	SqlQuery(SqlQueryType type, const QString& tableName, bool dlog = false);
	~SqlQuery();

	void addBindValue(const QString& fieldname, bool value);
	void addBindValue(const QString& fieldname, short value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, unsigned short value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, int value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, unsigned value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, long long value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, unsigned long long value) {addBindCheckedValue(fieldname, QString::number(value));}
	void addBindValue(const QString& fieldname, float value) {addBindCheckedValue(fieldname, QString().setNum(value));}
	void addBindValue(const QString& fieldname, double value) {addBindCheckedValue(fieldname, QString::number(value, 'g', 15));}
	void addBindValue(const QString& fieldname, const QByteArray& value) {addBindCheckedValue(fieldname, value.toHex());}
	void addBindValue(const QString& fieldname, const QString& value);
	void addBindValueFKey(const QString& fieldname, qint64 value);
	void setConditionId(quint64 value);
	void setConditionUuid(const QUuid& value);
	void addBindCheckedValue(const QString& fieldname, const QString& checkedValue);

	const QString& createQueryStr() const;

private:
	SqlQueryType type_;
	QString tableName_;
	bool dlog_;
	QMap<QString, QString> values_;
	quint64 conditionId_ = 0;
	QUuid conditionUuid_;
	mutable QString queryText_;
};

} // Ramio::
