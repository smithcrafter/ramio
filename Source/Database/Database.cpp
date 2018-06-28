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

#include "Database.h"
#include <Database/MetaTable.h>
#include <Items/MetaItemSet.h>
#include <Database/SqlQuery.h>
#include <Log/Log.h>
// Qt
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QDebug>

#define PRINT_ERROR_RETURN_FALSE { \
	qDebug().noquote().nospace()<<query_->lastError().text(); \
	qDebug().noquote().nospace()<<query_->lastQuery(); \
	return false; }

namespace Ramio {

Database::Database(SupportedDatabaseType dbtype, const QString& connectionName, QObject* parent)
	: QObject (parent),
	  type_(dbtype),
	  database_(QSqlDatabase::addDatabase(qtDatabaseName(dbtype), connectionName))
{
}

Database::~Database() = default;

bool Database::initTable(const Meta::Description& metadesc)
{
	return this->initTable(Ramio::MetaTable(metadesc, selectDatabaseSpecial(type_)));
}

bool Database::initTable(const MetaTable& metaTable)
{
	if (!query_)
		return false;

	if (type_ == SupportedDatabaseType::PostgreSQL)
	{
		if (query_->exec(metaTable.createFullTable()) == false)
			PRINT_ERROR_RETURN_FALSE

		Q_FOREACH(const QString& queryStr, metaTable.createFieldForTable())
			if (query_->exec(queryStr) == false)
			{
				qDebug().noquote().nospace()<<query_->lastError().text();
				qDebug().noquote().nospace()<<query_->lastQuery();
			}

		Q_FOREACH(const QString& queryStr, metaTable.createConstraintForTable())
			if (query_->exec(queryStr) == false)
			{
				qDebug().noquote().nospace()<<query_->lastError().text();
				qDebug().noquote().nospace()<<query_->lastQuery();
			}
	}
	else if (type_ == SupportedDatabaseType::SQLite)
	{
		if (query_->exec(SQL("PRAGMA table_info (%1);").arg(metaTable.tableName())) == false)
			PRINT_ERROR_RETURN_FALSE

		QSqlRecord record = query_->record();
		int index = record.indexOf(QStringLiteral("Name"));
		if (index < 0)
			return false;

		QStringList columns;
		while (query_->next())
			columns.append(query_->value(index).toString());

		if (query_->exec(metaTable.createOnlyKeyTable()) == false)
			PRINT_ERROR_RETURN_FALSE
		Q_FOREACH(const QString& queryStr, metaTable.createFieldForTable(columns))
			if (query_->exec(queryStr) == false)
			{
				qDebug().noquote().nospace()<<query_->lastError().text();
				qDebug().noquote().nospace()<<query_->lastQuery();
			}
	}
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
		PLOG("Database not open" % database_.lastError().text());
		return false;
	}
	PLOG(QStringLiteral("Database open"));
	query_.reset(new QSqlQuery(database_));
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

ResDesc Database::saveMetaItemData(ItemData& data, const Meta::Description& rmd)
{
	Ramio::SqlQuery query(Ramio::SqlQueryType::Insert, rmd.setName);
	Q_FOREACH(Meta::Property pr, rmd.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (pr.relationtype == Meta::FieldType::FKey)
				query.addBindValueFKey(pr.protoname, value);
			else
				query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
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
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			query.addBindValue(pr.protoname, value);
		}
		else
			Q_ASSERT(0);

	if (query_->exec(query.createQueryStr()))
	{
		data.id = query_->lastInsertId().toULongLong();
		return ResDesc();
	}
	qDebug()<<"Database::saveMetaItemData::Error"<<query_->lastQuery()<<query_->lastError().text();
	return ResDesc(1, query_->lastError().text());
}

ResDesc Database::udateMetaItemData(const ItemData& data, const Meta::Description& rmd)
{
	Ramio::SqlQuery query(Ramio::SqlQueryType::Update, rmd.setName);
	Q_FOREACH(Meta::Property pr, rmd.properties)
		if (pr.relationtype == Meta::FieldType::PKey)
			continue;
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (pr.relationtype == Meta::FieldType::FKey)
				query.addBindValueFKey(pr.protoname, value);
			else
				query.addBindValue(pr.protoname, value);
		}
		else if (pr.type == Meta::Type::Int)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
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
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			query.addBindValue(pr.protoname, value.toString(Qt::ISODate));
		}
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
			query.addBindValue(pr.protoname, value);
		}
		else
			Q_ASSERT(0);

	query.setConditionId(data.id);
	if (query_->exec(query.createQueryStr())) return ResDesc();
	qDebug()<<"Database::udateMetaItemData::Error"<<query_->lastQuery()<<query_->lastError().text();
	return ResDesc(1, query_->lastError().text());
}

ResDesc Database::deleteMetaItemData(const ItemData& data, const Meta::Description& rmd)
{
	Ramio::SqlQuery query(Ramio::SqlQueryType::Delete, rmd.setName);
	query.setConditionId(data.id);
	if (query_->exec(query.createQueryStr())) return ResDesc();
	qDebug()<<"Database::deleteMetaItemData::Error"<<query_->lastQuery()<<query_->lastError().text();
	return ResDesc(1, query_->lastError().text());
}

ResDesc Database::selectMetaItemData(AbstractMetaSet& metaset, const QString& condition) const
{
	auto& set = static_cast<MetaItemSet<StructItem<MetaItemData>, MetaItemData>&>(metaset);
	const Meta::Description& rmd = metaset.meta();
	const QString selectStr = SQL("SELECT * FROM %1 %2;").arg(rmd.setName, (condition.isEmpty() ? QString() : "WHERE " % condition));

	PLOG(selectStr);

	bool res = query_->exec(selectStr);
	if (res)
	{
		QSqlRecord record = query_->record();
		QMap<int, int> columnIndexes_;
		Q_FOREACH(const Meta::Property& pr, rmd.properties)
			columnIndexes_.insert(pr.dif,  record.indexOf(pr.protoname));
		while (query_->next())
		{
			StructItem<MetaItemData>* item = set.createItem();
			MetaItemData& data = item->data();
			item->beforeChanging();
			Q_FOREACH(const Meta::Property& pr, rmd.properties)
				if (columnIndexes_[pr.dif] == -1)
				{
					qDebug()<<pr.name<<"not finded";
				}
				else if (pr.type == Meta::Type::PKey)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
					value = query_->value(columnIndexes_[pr.dif]).toULongLong();
				}
				else if (pr.type == Meta::Type::Int)
				{
					auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
					value = query_->value(columnIndexes_[pr.dif]).toInt();
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
		DLOG(query_->lastQuery());
		return ResDesc(1, query_->lastError().text());
	}
}

} // Ramio::
