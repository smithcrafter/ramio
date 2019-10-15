/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

bool Database::open(const DatabaseConfig& config)
{
	database_.setUserName(config.username);
	database_.setPassword(config.password);
	database_.setDatabaseName(config.dbname);
	database_.setHostName(config.host);
	database_.setPort(config.port);
	if (!database_.open())
	{
		if (plog_)
			PLOG("DB::Open::Error " % database_.lastError().text());
		return false;
	}
	if (plog_)
		PLOG(QStringLiteral("DB::Open::Ok"));
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
	bindQueryValues(data, query, rmd.properties);
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
	bindQueryValues(data, query, rmd.properties);
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

	if (plog_)
		PLOG(selectStr);

	if (query_->exec(selectStr))
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
			{
				if (pr.relationtype == Meta::FieldType::Value || pr.relationtype == Meta::FieldType::Function)
					continue;

				QVariant fvalue = query_->value(columnIndexes_[pr.dif]);

				if (columnIndexes_[pr.dif] == -1)
				{
					if (!warning_miss)
						DLOG(QStringLiteral("DB::Select::Warning not find column %1 at %2, value")
							 .arg(pr.protoname, TABLENAME(rmd, type_)).arg(fvalue.toString()));
					warning_miss = true;
					continue;
				}
				else if (pr.type == Meta::Type::PKey)
					CAST_DATAREL_TO_TYPEREL(RMetaPKey) = fvalue.toULongLong();
				else if (pr.type == Meta::Type::Bool)
					CAST_DATAREL_TO_TYPEREL(RMetaBool) = fvalue.toBool();
				else if (pr.type == Meta::Type::Short)
					CAST_DATAREL_TO_TYPEREL(RMetaShort) = fvalue.toInt();
				else if (pr.type == Meta::Type::UShort)
					CAST_DATAREL_TO_TYPEREL(RMetaUShort) = fvalue.toUInt();
				else if (pr.type == Meta::Type::Int)
					CAST_DATAREL_TO_TYPEREL(RMetaInt) = fvalue.toInt();
				else if (pr.type == Meta::Type::UInt)
					CAST_DATAREL_TO_TYPEREL(RMetaUInt) = fvalue.toUInt();
				else if (pr.type == Meta::Type::Long)
					CAST_DATAREL_TO_TYPEREL(RMetaLong) = fvalue.toLongLong();
				else if (pr.type == Meta::Type::ULong)
					CAST_DATAREL_TO_TYPEREL(RMetaULong) = fvalue.toULongLong();
				else if (pr.type == Meta::Type::String)
					CAST_DATAREL_TO_TYPEREL(RMetaString) = fvalue.toString();
				else if (pr.type == Meta::Type::Double)
					CAST_DATAREL_TO_TYPEREL(RMetaDouble) = fvalue.toDouble();
				else if (pr.type == Meta::Type::Uuid)
					CAST_DATAREL_TO_TYPEREL(RMetaUuid) = RMetaUuid(fvalue.toString());
				else if (pr.type == Meta::Type::Time)
					CAST_DATAREL_TO_TYPEREL(RMetaTime) = RMetaTime::fromString(fvalue.toString(), Qt::ISODate);
				else if (pr.type == Meta::Type::Date)
					CAST_DATAREL_TO_TYPEREL(RMetaDate) = RMetaDate::fromString(fvalue.toString(), Qt::ISODate);
				else if (pr.type == Meta::Type::DateTime)
					CAST_DATAREL_TO_TYPEREL(RMetaDateTime) = RMetaDateTime::fromString(fvalue.toString(), Qt::ISODate);
				else if (pr.type == Meta::Type::Byte)
					CAST_DATAREL_TO_TYPEREL(RMetaByte) = fvalue.toUInt();
				else if (pr.type == Meta::Type::Money)
					CAST_DATAREL_TO_TYPEREL(RMetaMoney) = fvalue.toFloat();
				else
					Q_ASSERT(0);
			}
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

void Database::bindQueryValues(const ItemData& data, SqlQuery& query, const QList<Meta::Property>& prop)
{
	for (const Meta::Property& pr: prop)
		if (pr.relationtype == Meta::FieldType::PKey || pr.relationtype == Meta::FieldType::Value
				|| pr.relationtype == Meta::FieldType::Function)
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
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool));
		else if (pr.type == Meta::Type::Short)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort));
		else if (pr.type == Meta::Type::UShort)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort));
		else if (pr.type == Meta::Type::Int)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt));
		else if (pr.type == Meta::Type::UInt)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt));
		else if (pr.type == Meta::Type::Long)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong));
		else if (pr.type == Meta::Type::ULong)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong));
		else if (pr.type == Meta::Type::Float)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaFloat));
		else if (pr.type == Meta::Type::Double)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble));
		else if (pr.type == Meta::Type::String)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaString));
		else if (pr.type == Meta::Type::Uuid)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid).toString());
		else if (pr.type == Meta::Type::Time)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime).toString(Qt::ISODate));
		else if (pr.type == Meta::Type::Date)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate).toString(Qt::ISODate));
		else if (pr.type == Meta::Type::DateTime)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime).toString(Qt::ISODate));
		else if (pr.type == Meta::Type::Byte)
			query.addBindValue(pr.protoname, CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte));
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			query.addBindCheckedValue(pr.protoname, QString::number((value+(value > 0 ? 1 : -1)*0.000001), 'f', 2));
		}
		else
			Q_ASSERT(0);
}

} // Ramio::
