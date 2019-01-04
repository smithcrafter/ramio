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
// Qt
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
	return rmd_.setName;
}

QString MetaTable::createOnlyKeyTable() const
{
	QString IdFieldName = "id";
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			IdFieldName = pr.protoname.toLower();

	return "CREATE TABLE IF NOT EXISTS " % rmd_.setName % " ( " % IdFieldName % " " % special_.serialKey % ");";
}

QStringList MetaTable::createFieldForTable() const
{
	QStringList result;
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype != Meta::FieldType::PKey)
			result.append("ALTER TABLE " % rmd_.setName % " ADD COLUMN IF NOT EXISTS " % pr.protoname.toLower() % " " % dbTypeFromMeta(pr.type) % ";");
	return result;
}

QStringList MetaTable::createFieldForTable(QStringList& alredyExist) const
{
	QStringList result;
	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype != Meta::FieldType::PKey)
			if (!alredyExist.contains(pr.protoname.toLower()))
				result.append("ALTER TABLE " % rmd_.setName % " ADD COLUMN " % pr.protoname.toLower() % " " % dbTypeFromMeta(pr.type) % ";");
	return result;
}

QStringList MetaTable::createConstraintForTable() const
{
	QStringList result;

	result.append(SQL("create or replace function create_constraint_if_not_exists "
					  "\n( t_name text, c_name text, constraint_sql text ) "
					  "\nreturns void AS"
					  "\n$$"
					  "\nbegin"
					  "\nif not exists (SELECT 1 FROM pg_constraint WHERE conname = c_name)"
					  "\n/*(select constraint_name "
					  "\nfrom information_schema.constraint_column_usage "
					  "\nwhere table_name = t_name  and constraint_name = c_name) */"
					  "\nthen"
					  "\nexecute constraint_sql;"
					  "\nend if;"
					  "\nend;"
					  "\n$$ language 'plpgsql';"));

	for (const Meta::Property& pr: rmd_.properties)
		if (pr.relationtype == Meta::FieldType::FKey)
			if (rmd_.relations.contains(pr.name) && rmd_.relations[pr.name])
				result.append("SELECT create_constraint_if_not_exists('" % rmd_.setName.toLower()
							  % "','" % rmd_.setName.toLower() % "_" % pr.protoname.toLower() % "_fkey',"
							  % "'ALTER TABLE " % rmd_.setName.toLower() % " ADD CONSTRAINT "
							  % rmd_.setName.toLower() % "_" % pr.protoname.toLower()
							  % "_fkey FOREIGN KEY (" % pr.protoname.toLower() % ") "
							  %  "REFERENCES " % rmd_.relations[pr.name]->setName.toLower() %"(id);');");
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

	QString result = "CREATE TABLE IF NOT EXISTS " % rmd_.setName % " ( " % IdFieldName % " " % special_.serialKey % " ";
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
