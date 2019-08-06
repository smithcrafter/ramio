/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <QtCore/QMap>
#include <QtCore/QString>

namespace Ramio {

/**
 * @brief Перечисление операций SqlQueryType
 */
enum class SqlQueryType
{
	Insert,
	Update,
	Delete
};

/**
 * @brief Класс SqlQuery подготовки запроса к БД.
 */
class SqlQuery
{
public:
	SqlQuery(SqlQueryType type, const QString& tableName);

	void addBindValue(const QString& fieldname, const QString& value);
	void addBindValue(const QString& fieldname, const QByteArray& value);
	void addBindValue(const QString& fieldname, bool value);
	void addBindValue(const QString& fieldname, int value);
	void addBindValue(const QString& fieldname, qint64 value);
	void addBindValue(const QString& fieldname, quint64 value);
	void addBindValue(const QString& fieldname, double value);
	void addBindValueFKey(const QString& fieldname, quint64 value);

	void setConditionId(quint64 value);

	const QString& createQueryStr() const;

private:
	SqlQueryType type_;
	QString tableName_;
	QMap<QString, QString> values_;
	quint64 conditionId_ = 0;
	mutable QString queryText_;
};

} // Ramio::
