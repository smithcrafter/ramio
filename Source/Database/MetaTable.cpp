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

#include "MetaTable.h"
#include "DatabaseOptions.h"
#include <Items/MetaItemData.h>
// Qt5
#include <QStringBuilder>

namespace Ramio {

DatabaseSpecial create_Postgres_DatabaseSpecial()
{
	DatabaseSpecial res;
	res.serialKey = "serial PRIMARY KEY";
	return res;
}

DatabaseSpecial create_SQLite_DatabaseSpecial()
{
	DatabaseSpecial res;
	res.serialKey = "INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL";
	return res;
}

QString dbTypeFromMeta(Meta::Type type)
{
	switch (type) {
		case Meta::Type::PKey : return "INT8";
		case Meta::Type::Int : return "INT4";
		case Meta::Type::Long : return "INT8";
		case Meta::Type::Uuid : return "UUID";
		case Meta::Type::Double : return "DOUBLE PRECISION";
		case Meta::Type::String : return "TEXT";
		case Meta::Type::Time : return "TIME";
		case Meta::Type::Date : return "DATE";
		case Meta::Type::DateTime : return "TIMESTAMP";
		case Meta::Type::Money : return "DECIMAL";
		case Meta::Type::Unset : break;
	}
	Q_ASSERT(0);
	return QString();
}

const DatabaseSpecial Postgres_DatabaseSpecial = create_Postgres_DatabaseSpecial();
const DatabaseSpecial SQLite_DatabaseSpecial = create_SQLite_DatabaseSpecial();
const DatabaseSpecial SQLDefault_DatabaseSpecial;

MetaTable::MetaTable(const Meta::Description& rmd, const DatabaseSpecial& special)
	: rmd_(rmd),
	  special_(special)
{
}

QString MetaTable::tableName() const
{
	if (rmd_.schemeName.isEmpty())
		return rmd_.setName;
	return (rmd_.schemeName % "." % rmd_.setName).toLower();
}

QString MetaTable::createOnlyKeyTable() const
{
	QString IdFieldName = "id";
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			IdFieldName = pr.protoname.toLower();

	return "CREATE TABLE IF NOT EXISTS " % tableName() % " ( " % IdFieldName % " " % special_.serialKey % ");";
}

QStringList MetaTable::createFieldForTable() const
{
	QStringList result;
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype != Meta::FieldType::PKey)
			result.append("ALTER TABLE " % tableName() % " ADD COLUMN IF NOT EXISTS " % pr.protoname.toLower() % " " % dbTypeFromMeta(pr.type) % ";");
	return result;
}

QStringList MetaTable::createFieldForTable(QStringList& alredyExist) const
{
	QStringList result;
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype != Meta::FieldType::PKey)
			if (!alredyExist.contains(pr.protoname.toLower()))
				result.append("ALTER TABLE " % tableName() % " ADD COLUMN " % pr.protoname.toLower() % " " % dbTypeFromMeta(pr.type) % ";");
	return result;
}

QStringList MetaTable::createConstraintForTable() const
{
	QStringList result;

	QString shemename = rmd_.schemeName.isEmpty() ? emptyString : rmd_.schemeName.toLower() +".";

	result.append(SQL("create or replace function %1create_constraint_if_not_exists "
					  "\n(constraint_name text, constraint_sql text ) "
					  "\nreturns void AS"
					  "\n$$"
					  "\nbegin"
					  "\nIF NOT exists (SELECT 1 FROM pg_catalog.pg_constraint WHERE conname = constraint_name) then"
					  "\nexecute constraint_sql;"
					  "\nend if;"
					  "\nend;"
					  "\n$$ "
					  "\nlanguage 'plpgsql';").arg(shemename));

	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype == Meta::FieldType::FKey)
			if (rmd_.relations.contains(pr.name) && rmd_.relations[pr.name])
			{
				QString conname = QString(shemename).replace(".", "_") % rmd_.setName.toLower() % "_" % pr.protoname.toLower() % "_fkey";
				QString alterquery = "ALTER TABLE " % tableName() % " ADD CONSTRAINT " % conname
						% " FOREIGN KEY (" % pr.protoname.toLower() % ") " %  "REFERENCES " %
						(rmd_.relations[pr.name]->schemeName.isEmpty() ? emptyString : rmd_.relations[pr.name]->schemeName + ".")
						% rmd_.relations[pr.name]->setName.toLower() % "(id)";

				result.append("SELECT "%shemename%"create_constraint_if_not_exists('" % conname % "','" % alterquery % "');");
			}
	if (result.count() == 1)
		result.clear();
	return result;
}

QString MetaTable::createFullTable() const
{
	QString IdFieldName = QStringLiteral("Id");
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			IdFieldName = pr.protoname.toLower();

	QString result = "CREATE TABLE IF NOT EXISTS " % tableName() % " ( " % IdFieldName % " " % special_.serialKey % " ";
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype != Meta::FieldType::PKey)
		{
			result = result % ", " % pr.protoname.toLower() % " " % dbTypeFromMeta(pr.type) % " ";
		}
	result = result % ");";
	return result;
}

const DatabaseSpecial& selectDatabaseSpecial(SupportedDatabaseType type)
{
	if (type == SupportedDatabaseType::PostgreSQL)
		return Postgres_DatabaseSpecial;
	if (type == SupportedDatabaseType::SQLite)
		return SQLite_DatabaseSpecial;
	return SQLDefault_DatabaseSpecial;
}

} // Ramio::
