/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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

static const QString quote("'");
#define QUOTED(value) (quote % (value) % quote)

SqlQuery::SqlQuery(SqlQueryType type, const QString& tableName, bool dlog)
	: type_(type),
	  tableName_(tableName),
	  dlog_(dlog)
{
}

SqlQuery::~SqlQuery() = default;

void SqlQuery::addBindValue(const QString& fieldname, const QString& value)
{
	if (value.isEmpty())
		values_.insert(fieldname, QStringLiteral("NULL"));
	else
		values_.insert(fieldname, QUOTED(QString(value).replace(QStringLiteral("'"), QStringLiteral("''"))));
}

void SqlQuery::addBindCheckedValue(const QString &fieldname, const QString& checkedValue)
{
	values_.insert(fieldname, QUOTED(checkedValue));
}

void SqlQuery::addBindValue(const QString &fieldname, bool value)
{
	values_.insert(fieldname, QUOTED(value ? QStringLiteral("true") : QStringLiteral("false")));
}

void SqlQuery::addBindValueFKey(const QString& fieldname, qint64 value)
{
	if (value)
		addBindValue(fieldname, value);
	else
		values_.insert(fieldname, QStringLiteral("NULL"));
}

void SqlQuery::setConditionId(quint64 value)
{
	conditionUuid_ = QUuid();
	conditionId_ = value;
}

void SqlQuery::setConditionUuid(const QUuid& value)
{
	conditionId_ = 0;
	conditionUuid_ = value;
}

const QString& SqlQuery::createQueryStr() const
{
	if (!queryText_.isEmpty())
		return queryText_;
	if (type_ == SqlQueryType::Insert)
	{
		QStringList keys;
		QStringList values;
		for (auto it = values_.constBegin(); it != values_.constEnd(); ++it)
		{
			keys.append("\"" % it.key()% "\"");
			values.append(it.value());
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
		for (auto it = values_.constBegin(); it != values_.constEnd(); ++it)
		{
			if (it != values_.constBegin())
				queryText_.append(" , ");
			queryText_.append("\"" % it.key() % "\"" % QStringLiteral(" = ") % it.value());
		}

		if (conditionId_)
			queryText_.append(QStringLiteral(" WHERE Id = '") % QString::number(conditionId_) % QStringLiteral("' ; "));
		else if (!conditionUuid_.isNull())
			queryText_.append(QStringLiteral(" WHERE Uuid = '") % conditionUuid_.toString(QUuid::WithoutBraces) % QStringLiteral("' ; "));
		else
			Q_ASSERT_X(false, "SqlQuery::Condition", "Condition field not set");

	}
	else if (type_ == SqlQueryType::Delete)
	{
		queryText_ = QStringLiteral("DELETE FROM ") % tableName_;
		if (conditionId_)
			queryText_.append(QStringLiteral(" WHERE Id = '") % QString::number(conditionId_) % QStringLiteral("' ; "));
		else if (!conditionUuid_.isNull())
			queryText_.append(QStringLiteral(" WHERE Uuid = '") % conditionUuid_.toString(QUuid::WithoutBraces) % QStringLiteral("' ; "));
		else
			Q_ASSERT_X(false, "SqlQuery::Condition", "Condition field not set");
	}
	if (dlog_)
		DLOG("[SqlQuery] " % queryText_);
	return queryText_;
}


} // Ramio::
