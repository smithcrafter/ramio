/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

#include "SqlQuery.h"
#include <Log/Log.h>

namespace Ramio {

SqlQuery::SqlQuery(SqlQueryType type, const QString& tableName)
	: type_(type),
	  tableName_(tableName)
{
}

void SqlQuery::addBindValue(const QString& fieldname, const QString& value)
{
	if (value.isEmpty())
		values_.insert(fieldname, QStringLiteral("NULL"));
	else
		values_.insert(fieldname, QStringLiteral("'") % QString(value)
					   .replace(QStringLiteral("'"), QStringLiteral("''")) % QStringLiteral("'"));
}

void SqlQuery::addBindValue(const QString& fieldname, const QByteArray& value)
{
	values_.insert(fieldname, QStringLiteral("'") % value.toHex() % QStringLiteral("'"));
}

void SqlQuery::addBindValue(const QString& fieldname, int value)
{
	values_.insert(fieldname, QStringLiteral("'") % QString::number(value) % QStringLiteral("'"));
}

void SqlQuery::addBindValue(const QString& fieldname, qint64 value)
{
	values_.insert(fieldname, QStringLiteral("'") % QString::number(value) % QStringLiteral("'"));
}

void SqlQuery::addBindValue(const QString& fieldname, quint64 value)
{
	values_.insert(fieldname, QStringLiteral("'") % QString::number(value) % QStringLiteral("'"));
}

void SqlQuery::addBindValue(const QString& fieldname, double value)
{
	values_.insert(fieldname, QStringLiteral("'") % QString::number(value) %QStringLiteral("'"));
}

void SqlQuery::addBindValueFKey(const QString& fieldname, quint64 value)
{
	if (value)
		addBindValue(fieldname, value);
	else
		values_.insert(fieldname, QStringLiteral("NULL"));
}

void SqlQuery::setConditionId(quint64 value)
{
	conditionId_ = value;
}

const QString& SqlQuery::createQueryStr() const
{
	if (!queryText_.isEmpty())
		return queryText_;
	if (type_ == SqlQueryType::Insert)
	{
		QStringList keys;
		QStringList values;
		for (auto i = values_.constBegin(); i != values_.constEnd(); i++)
		{
			keys.append(i.key());
			values.append(i.value());
		}
		queryText_ = QStringLiteral("INSERT INTO ")
				% tableName_
				% QStringLiteral(" ( ")
				% keys.join(QStringLiteral(", "))
				% QStringLiteral(" ) VALUES ( ")
				% values.join(QStringLiteral(", "))
				% QStringLiteral(" ); ");
	}
	else if (type_ == SqlQueryType::Update)
	{
		queryText_ = QStringLiteral("UPDATE ")
				% tableName_
				% QStringLiteral(" SET ");
		for (auto i = values_.constBegin(); i != values_.constEnd(); i++)
		{
			if (i != values_.constBegin()) queryText_.append(" , ");
			queryText_.append(i.key() % QStringLiteral(" = ") % i.value());
		}
		queryText_.append(QStringLiteral(" WHERE ID = '") % QString::number(conditionId_) % QStringLiteral("' ; "));
	}
	else if (type_ == SqlQueryType::Delete)
	{
		queryText_ = QStringLiteral("DELETE FROM ")
				% tableName_
				% QStringLiteral(" WHERE ID = '")
				% QString::number(conditionId_)
				% QStringLiteral("' ; ");
	}
	LOG("[SqlQuery]" % queryText_);
	return queryText_;
}

} // Ramio::
