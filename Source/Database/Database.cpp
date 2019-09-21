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

#include "Database.h"
#include <Database/MetaTable.h>
#include <Items/MetaItemSet.h>
#include <Database/SqlQuery.h>
#include <Log/Log.h>
#include <Sets/Arg.h>
// Qt
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtCore/QVariant>

#define PRINT_ERROR { \
	DLOG(query_->lastQuery()); \
	CLOG(query_->lastError().text()); \
	}

#define PRINT_ERROR_RETURN_FALSE { \
	PRINT_ERROR \
	return false; }

#define TABLENAME(rmd, type_) MetaTable(rmd, type_).tableName()

namespace Ramio {

Database::Database(SupportedDatabaseType dbtype, const QString& connectionName, QObject* parent)
	: QObject (parent),
	  type_(dbtype),
	  database_(QSqlDatabase::addDatabase(qtDatabaseName(dbtype), connectionName)),
	  plog_(APP_ARG_CONTAINS(APP_ARGUMENT("PLOG_DATABASE")))
{
}

Database::~Database() = default;

bool Database::initTable(const Meta::Description& metadesc)
{
	return this->initTable(Ramio::MetaTable(metadesc, type_, database_.databaseName()));
}

bool Database::initTable(const MetaTable& metaTable)
{
	if (!isOpen())
		return false;

	if (type_ == SupportedDatabaseType::PostgreSQL)
	{
		if (query_->exec(metaTable.createFullTable()) == false)
			PRINT_ERROR_RETURN_FALSE

		Q_FOREACH(const QString& queryStr, metaTable.createFieldForTable())
			if (query_->exec(queryStr) == false)
				PRINT_ERROR

		Q_FOREACH(const QString& queryStr, metaTable.createConstraintForTable())
			if (query_->exec(queryStr) == false)
				PRINT_ERROR
	}
	else if (type_ == SupportedDatabaseType::SQLite || type_ == SupportedDatabaseType::MySQL)
	{
		QString columnQuery;
		if (type_ == SupportedDatabaseType::SQLite )
			columnQuery = SQL("PRAGMA table_info (%1);").arg(metaTable.tableName());
		else if (type_ == SupportedDatabaseType::MySQL )
			columnQuery = SQL("SELECT column_name AS name FROM INFORMATION_SCHEMA.COLUMNS"
							  " WHERE table_name = '%1' AND table_schema = '%2';")
					.arg(metaTable.tableName(), database_.databaseName());

		if (query_->exec(columnQuery) == false)
			PRINT_ERROR_RETURN_FALSE

		QSqlRecord record = query_->record();
		int index = record.indexOf(QStringLiteral("name"));
		if (index < 0)
			return false;

		QStringList columns;
		while (query_->next())
			columns.append(query_->value(index).toString().toLower());

		if (columns.isEmpty())
			if (query_->exec(metaTable.createOnlyKeyTable()) == false)
				PRINT_ERROR_RETURN_FALSE
		Q_FOREACH(const QString& queryStr, metaTable.createFieldForTable(columns))
			if (query_->exec(queryStr) == false)
				PRINT_ERROR
	}
	else
		return false;
	return true;
}

bool Database::open(const DataBaseConfig& config)
{
	database_.setUserName(config.userName);
	database_.setPassword(config.password);
	database_.setDatabaseName(config.databaseName);
	database_.setHostName(config.host);
	database_.setPort(config.port);
	if (!database_.open())
	{
		if (plog_) PLOG("DB::Open::Error " % database_.lastError().text());
		return false;
	}
	if (plog_) PLOG(QStringLiteral("DB::Open::Ok"));
	query_.reset(new QSqlQuery(database_));
	query_->exec(SQL("SET client_min_messages TO WARNING;"));
	return true;
}

bool Database::isOpen() const
{
	return query_ && database_.isOpen();
}

void Database::close()
{
	if (isOpen())
		database_.close();
}

QString Database::lastError()
{
	return query_ ? query_->lastError().text() : QString();
}

bool Database::startTransaction()
{
	return query_ && query_->exec("BEGIN TRANSACTION;");
}

bool Database::stopTransaction()
{
	return query_ && query_->exec("COMMIT;");
}

ResDesc Database::insertMetaItemData(ItemData& data, const Meta::Description& rmd)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Insert, TABLENAME(rmd, type_));
	for (const Meta::Property& pr: rmd.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			continue;
		else if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (pr.relationtype == Meta::FieldType::FKey)
				query.addBindValueFKey(pr.protoname, value);
			else
				query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
			query.addBindValue(pr.protoname, value.toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDate);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			int m = (value+0.001)*100;
			int cent = qAbs(m)%100;
			query.addBindValue(pr.protoname, QString::number(m/100) % "." % (cent < 10 ? "0" : "") % QString::number(cent));
		}
		else
			Q_ASSERT(0);

	if (query_->exec(query.createQueryStr()))
	{
		data.id = query_->lastInsertId().toULongLong();
		return ResDesc();
	}
	PLOG("DB::save::Error");
	PRINT_ERROR
	return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

ResDesc Database::updateMetaItemData(const ItemData& data, const Meta::Description& rmd)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Update, TABLENAME(rmd, type_));
	for (const Meta::Property& pr: rmd.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			continue;
		else if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (pr.relationtype == Meta::FieldType::FKey)
				query.addBindValueFKey(pr.protoname, value);
			else
				query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Bool)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Long)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::String)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Double)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
			query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			query.addBindValue(pr.protoname, value.toString());
		}
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Date)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			int m = (value+0.001)*100;
			int cent = qAbs(m)%100;
			query.addBindValue(pr.protoname, QString::number(m/100) % "." % (cent < 10 ? "0" : "") % QString::number(cent));
		}
		else
			Q_ASSERT(0);

	query.setConditionId(data.id);
	if (query_->exec(query.createQueryStr()))
		return ResDesc();
	PLOG("DB::Udate::Error");
	PRINT_ERROR
	return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

ResDesc Database::deleteMetaItemData(const ItemData& data, const Meta::Description& rmd)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Delete, TABLENAME(rmd, type_));
	query.setConditionId(data.id);
	if (query_->exec(query.createQueryStr()))
		return ResDesc();
	PLOG("DB::Delete::Error");
	PRINT_ERROR
	return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

ResDesc Database::selectMetaItemDataSet(AbstractMetaSet& metaset, const QString& condition) const
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	auto& set = static_cast<MetaItemSet<StructItem<MetaItemData>, MetaItemData>&>(metaset);
	const Meta::Description& rmd = metaset.meta();
	const QString selectStr = SQL("SELECT * FROM %1 %2;")
			.arg(TABLENAME(rmd, type_), (condition.isEmpty() ? QString() : "WHERE " % condition));

	if (plog_) PLOG(selectStr);

	bool res = query_->exec(selectStr);
	if (res)
	{
		QSqlRecord record = query_->record();
		QMap<ptrdiff_t, int> columnIndexes_;
		for (const Meta::Property& pr: rmd.properties)
			columnIndexes_.insert(pr.dif,  record.indexOf(pr.protoname));

		bool warning_miss = false;

		while (query_->next())
		{
			StructItem<MetaItemData>* item = set.createItem();
			MetaItemData& data = item->data();
			item->beforeChanging();
			for (const Meta::Property& pr: rmd.properties)
				if (columnIndexes_[pr.dif] == -1)
				{
					if (!warning_miss)
					{
						DLOG(QStringLiteral("DB::Select::Warning not find column %1 at %2")
							 .arg(pr.protoname, TABLENAME(rmd, type_)));
						warning_miss = true;
					}
				}
				else if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
					continue;
				else if (pr.type == Meta::Type::PKey)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
					value = query_->value(columnIndexes_[pr.dif]).toULongLong();
				}
				else if (pr.type == Meta::Type::Bool)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaBool);
					value = query_->value(columnIndexes_[pr.dif]).toBool();
				}
				else if (pr.type == Meta::Type::Int)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
					value = query_->value(columnIndexes_[pr.dif]).toInt();
				}
				else if (pr.type == Meta::Type::Long)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaLong);
					value = query_->value(columnIndexes_[pr.dif]).toLongLong();
				}
				else if (pr.type == Meta::Type::String)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
					value = query_->value(columnIndexes_[pr.dif]).toString();
				}
				else if (pr.type == Meta::Type::Double)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
					value = query_->value(columnIndexes_[pr.dif]).toDouble();
				}
				else if (pr.type == Meta::Type::Uuid)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaUuid);
					value = RMetaUuid(query_->value(columnIndexes_[pr.dif]).toString());
				}
				else if (pr.type == Meta::Type::Time)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaTime);
					value = RMetaTime::fromString(query_->value(columnIndexes_[pr.dif]).toString(), Qt::ISODate);
				}
				else if (pr.type == Meta::Type::Date)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDate);
					value = RMetaDate::fromString(query_->value(columnIndexes_[pr.dif]).toString(), Qt::ISODate);
				}
				else if (pr.type == Meta::Type::DateTime)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
					value = RMetaDateTime::fromString(query_->value(columnIndexes_[pr.dif]).toString(), Qt::ISODate);
				}
				else if (pr.type == Meta::Type::Money)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
					value = query_->value(columnIndexes_[pr.dif]).toDouble();
				}
				else
					Q_ASSERT(0);
			item->afterChanging();
			set.addItem(item);
		}
		return ResDesc();
	}
	else
	{
		DLOG("SQL:" % query_->lastQuery() % " Error:" % query_->lastError().text());
		return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
	}
}

} // Ramio::
