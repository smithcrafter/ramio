/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "DatabaseConnection.h"
#include <Database/MetaTable.h>
#include <Items/MetaItemSet.h>
#include <Database/SqlQuery.h>
#include <Log/Log.h>
#include <Sets/Arg.h>
#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtCore/QVariant>

#define PRINT_ERROR { \
	DLOG("SQL: " % query_->lastQuery()); \
	ELOG(query_->lastError().text()); \
	}

#define PRINT_ERROR_RETURN_FALSE { \
	PRINT_ERROR \
	return false; }

#define TABLENAME(md, type_) MetaTable(md, type_).tableName()

namespace Ramio {

DatabaseConnection::DatabaseConnection(Ramio::SupportedDatabaseType dbtype, const QString& connectionName, const DatabaseConfig& config,
				   QObject* parent)
	: QObject (parent),
	  type_(dbtype),
	  config_(config),
	  database_(QSqlDatabase::addDatabase(qtDatabaseName(dbtype), connectionName)),
	  dlog_(APP_ARG_CONTAINS(APP_ARGUMENT("DLOG_DATABASE")))
{
}

DatabaseConnection::~DatabaseConnection()
{
	if (isOpen())
		close();
	QString name = database_.connectionName();
	database_ = QSqlDatabase();
	QSqlDatabase::removeDatabase(name);
}

bool DatabaseConnection::initTable(const Meta::Description& md)
{
	return this->initTable(Ramio::MetaTable(md, type_));
}

bool DatabaseConnection::initTable(const MetaTable& metaTable)
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

bool DatabaseConnection::open(const DatabaseConfig& config)
{
	database_.setUserName(config.username);
	database_.setPassword(config.password);
	database_.setDatabaseName(config.dbname);
	database_.setHostName(config.host);
	database_.setPort(config.port);
	if (!database_.open())
	{
		if (dlog_)
			PLOG("DB::Open::Error " % database_.lastError().text());
		return false;
	}
	if (dlog_)
		PLOG(QStringLiteral("DB::Open::Ok"));
	query_.reset(new QSqlQuery(database_));
	query_->exec(SQL("SET client_min_messages TO WARNING;"));
	config_ = config;
	DLOG_FULL(database_.connectionName());
	emit stateChanged();
	return true;
}

bool DatabaseConnection::isOpen() const
{
	return query_ && database_.isOpen();
}

void DatabaseConnection::close()
{
	if (!isOpen())
		return;
	query_.reset();
	database_.close();
	DLOG_FULL(database_.connectionName());
	emit stateChanged();
}

QString DatabaseConnection::lastError()
{
	return query_ ? query_->lastError().text() : QString();
}

bool DatabaseConnection::startTransaction()
{
	return query_ && query_->exec("BEGIN TRANSACTION;");
}

bool DatabaseConnection::stopTransaction()
{
	return query_ && query_->exec("COMMIT TRANSACTION;");
}

bool DatabaseConnection::abortTransaction()
{
	return query_ && query_->exec("ROLLBACK TRANSACTION;");
}

ResDesc DatabaseConnection::insertMetaItemData(ItemData& itemData, const Meta::Description& md)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Insert, TABLENAME(md, type_), dlog_);
	bindQueryValues(itemData, query, md.properties);
	RMPKey pkey = itemData.id;
	if (query_->exec(query.createQueryStr()))
	{
		if (!pkey)
			itemData.id = query_->lastInsertId().toULongLong();
		return ResDesc();
	}
	PLOG("DB::Save::Error");
	PRINT_ERROR
	return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

ResDesc DatabaseConnection::updateMetaItemData(const ItemData& itemData, const Meta::Description& md)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Update, TABLENAME(md, type_), dlog_);
	bindQueryValues(itemData, query, md.properties);
	query.setConditionId(itemData.id);
	if (query_->exec(query.createQueryStr()))
		return ResDesc();
	PLOG("DB::Udate::Error");
	PRINT_ERROR
	return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

ResDesc DatabaseConnection::deleteMetaItemData(const ItemData& itemData, const Meta::Description& md)
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	Ramio::SqlQuery query(Ramio::SqlQueryType::Delete, TABLENAME(md, type_), dlog_);
	query.setConditionId(itemData.id);
	if (query_->exec(query.createQueryStr()))
		return ResDesc();
	PLOG("DB::Delete::Error");
	PRINT_ERROR
			return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
}

void updateItemDataFromQVariant(const Meta::Property& pr, const QVariant& fvalue, ItemData& data)
{
	if (pr.type == Meta::Type::PKey)
		CAST_DATAREL_TO_TYPEREL(RMPKey) = fvalue.toULongLong();
	else if (pr.type == Meta::Type::Type)
		CAST_DATAREL_TO_TYPEREL(RMType) = fvalue.toUInt();
	else if (pr.type == Meta::Type::State)
		CAST_DATAREL_TO_TYPEREL(RMState) = fvalue.toUInt();
	else if (pr.type == Meta::Type::Flags)
		CAST_DATAREL_TO_TYPEREL(RMFlags) = fvalue.toUInt();
	else if (pr.type == Meta::Type::Bool)
		CAST_DATAREL_TO_TYPEREL(RMBool) = fvalue.toBool();
	else if (pr.type == Meta::Type::Short)
		CAST_DATAREL_TO_TYPEREL(RMShort) = static_cast<RMShort>(fvalue.toInt());
	else if (pr.type == Meta::Type::UShort)
		CAST_DATAREL_TO_TYPEREL(RMUShort) = static_cast<RMUShort>(fvalue.toUInt());
	else if (pr.type == Meta::Type::Int)
		CAST_DATAREL_TO_TYPEREL(RMInt) = fvalue.toInt();
	else if (pr.type == Meta::Type::UInt)
		CAST_DATAREL_TO_TYPEREL(RMUInt) = fvalue.toUInt();
	else if (pr.type == Meta::Type::Long)
		CAST_DATAREL_TO_TYPEREL(RMLong) = fvalue.toLongLong();
	else if (pr.type == Meta::Type::ULong)
		CAST_DATAREL_TO_TYPEREL(RMULong) = fvalue.toULongLong();
	else if (pr.type == Meta::Type::StdString)
		CAST_DATAREL_TO_TYPEREL(RMStdString) = fvalue.toString().toStdString();
	else if (pr.type == Meta::Type::String)
		CAST_DATAREL_TO_TYPEREL(RMString) = fvalue.toString();
	else if (pr.type == Meta::Type::StringList)
		CAST_DATAREL_TO_TYPEREL(RMStringList) = fvalue.toString().split("\n", Qt_SkipEmptyParts);
	else if (pr.type == Meta::Type::Float)
		CAST_DATAREL_TO_TYPEREL(RMFloat) = fvalue.toFloat();
	else if (pr.type == Meta::Type::Double)
		CAST_DATAREL_TO_TYPEREL(RMDouble) = fvalue.toDouble();
	else if (pr.type == Meta::Type::Uuid)
		CAST_DATAREL_TO_TYPEREL(RMUuid) = fvalue.toUuid(); // RMUuid(fvalue.toString());
	else if (pr.type == Meta::Type::Time)
		CAST_DATAREL_TO_TYPEREL(RMTime) = fvalue.toTime(); // RMTime::fromString(fvalue.toString(), Qt::ISODateWithMs);
	else if (pr.type == Meta::Type::Date)
		CAST_DATAREL_TO_TYPEREL(RMDate) = fvalue.toDate(); // RMDate::fromString(fvalue.toString(), Qt::ISODate);
	else if (pr.type == Meta::Type::DateTime)
		CAST_DATAREL_TO_TYPEREL(RMDateTime) = fvalue.toDateTime(); // RMDateTime::fromString(fvalue.toString(), Qt::ISODateWithMs);
	else if (pr.type == Meta::Type::ByteArray)
		CAST_DATAREL_TO_TYPEREL(RMByteArray) = QByteArray::fromHex(fvalue.toByteArray());
	else if (pr.type == Meta::Type::Byte)
		CAST_DATAREL_TO_TYPEREL(RMByte) = RMByte(fvalue.toUInt());
	else if (pr.type == Meta::Type::Money)
		CAST_DATAREL_TO_TYPEREL(RMMoney) = fvalue.toFloat();
	else if (pr.type == Meta::Type::PKeyList && pr.role == Meta::FieldRole::Field)
	{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
		QStringList ids = fvalue.toString().split(";", Qt::SkipEmptyParts);
#else
		QStringList ids = fvalue.toString().split(";", QString::SkipEmptyParts);
#endif
		for (const auto& id: ids)
			CAST_DATAREL_TO_TYPEREL(RMPKeyList).append(id.toLongLong());
	}
	else
		Q_ASSERT(0);
}

ResDesc DatabaseConnection::selectBaseItemDataPrtList(QList<BaseItemData*>& itemDataPrtList, const Meta::Description& md, const QString& condition) const
{
	if (md.createDataFunction == Q_NULLPTR)
		return ResDesc(RD_PROGRAMM_ERROR, tr("Мета описание подготовлено не полностью."));

	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	const QString selectStr = SQL("SELECT * FROM %1 %2;")
			.arg(TABLENAME(md, type_), (condition.isEmpty() ? QString() : "WHERE " % condition));

	if (dlog_)
		DLOG(selectStr);

	if (query_->exec(selectStr))
	{
		QSqlRecord record = query_->record();
		QMap<ptrdiff_t, int> columnIndexes_;
		for (const Meta::Property& pr: md.properties)
		{
			int index = record.indexOf(pr.protoname.toLower());
			if (index != -1)
				columnIndexes_.insert(pr.diff, index);
		}
		bool warning_miss = false;
		while (query_->next())
		{
			BaseItemData* dataPrt = md.createDataFunction->operator()();
			ItemData& data = *dataPrt;
			for (const Meta::Property& pr: md.properties)
			{
				if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
					continue;
				if (pr.type == Meta::Type::RecordPrtList || pr.type == Meta::Type::TypeList)
					continue;
				QVariant fvalue = query_->value(columnIndexes_[pr.diff]);
				if (columnIndexes_[pr.diff] == -1)
				{
					if (!warning_miss)
						DLOG(QStringLiteral("DB::Select::Warning not find column %1 at %2, value %3")
							 .arg(pr.protoname, TABLENAME(md, type_), fvalue.toString()));
					warning_miss = true;
					continue;
				}
				else
					updateItemDataFromQVariant(pr, fvalue, data);
			}
			itemDataPrtList.append(dataPrt);
		}
		return ResDesc();
	}
	else
	{
		DLOG("SQL:" % query_->lastQuery() % " Error:" % query_->lastError().text());
		return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
	}
}

ResDesc DatabaseConnection::selectMetaItemDataSet(AbstractMetaSet& metaset, const QString& condition) const
{
	Q_ASSERT(metaset.aSet());
	return selectMetaItemDataSet(*metaset.aSet(), metaset.meta(), condition);
}

ResDesc DatabaseConnection::selectMetaItemDataSet(AbstractListSet& aset, const Meta::Description& md, const QString& condition) const
{
	if (!isOpen())
		return ResDesc(RD_DATABASE_ERROR, tr("Во время запроса соединение с базой данной не установлено."));

	const QString selectStr = SQL("SELECT * FROM %1 %2;")
			.arg(TABLENAME(md, type_), (condition.isEmpty() ? QString() : "WHERE " % condition));

	if (dlog_)
		DLOG(selectStr);

	if (query_->exec(selectStr))
	{
		QSqlRecord record = query_->record();
		QMap<ptrdiff_t, int> columnIndexes_;
		for (const Meta::Property& pr: md.properties)
		{
			int index = record.indexOf(pr.protoname.toLower());
			if (index != -1)
				columnIndexes_.insert(pr.diff, index);
		}
		bool warning_miss = false;
		while (query_->next())
		{
			auto* item = aset.createItem();
			ItemData& data = item->data();
			for (const Meta::Property& pr: md.properties)
			{
				if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
					continue;
				if (pr.type == Meta::Type::RecordPrtList || pr.type == Meta::Type::TypeList)
					continue;
				QVariant fvalue = query_->value(columnIndexes_[pr.diff]);
				if (columnIndexes_[pr.diff] == -1)
				{
					if (!warning_miss)
						DLOG(QString("DB::Select::Warning not find column %1 at %2, value %3")
							 .arg(pr.protoname, TABLENAME(md, type_), fvalue.toString()));
					warning_miss = true;
					continue;
				}
				else
					updateItemDataFromQVariant(pr, fvalue, data);

			}
			aset.insertItem(*item);
		}
		return ResDesc();
	}
	else
	{
		DLOG("SQL:" % query_->lastQuery() % " Error:" % query_->lastError().text());
		return ResDesc(RD_DATABASE_ERROR, query_->lastError().text());
	}
}

bool DatabaseConnection::execSql(const QString& sqltext)
{
	return query_ && query_->exec(sqltext);
}

QSqlRecord DatabaseConnection::queryRecord() const
{
	return query_ ? query_->record() : QSqlRecord();
}

QSqlRecord DatabaseConnection::queryNextRecord() const
{
	return query_ && query_->next() ? query_->record() : QSqlRecord();
}

void DatabaseConnection::bindQueryValues(const ItemData& data, SqlQuery& query, const QVector<Meta::Property>& prop)
{
	for (const Meta::Property& pr: prop)
		if (pr.role == Meta::FieldRole::Value|| pr.role == Meta::FieldRole::Function || pr.type == Meta::Type::RecordPrtList)
			continue;
		else if (pr.role == Meta::FieldRole::PKey)
		{
			if (pr.type == Meta::Type::PKey)
			{
				const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
				if (value)
					query.addBindValue(pr.protoname.toLower(), value);
			}
			continue;
		}
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			if (pr.role == Meta::FieldRole::FKey)
				query.addBindValueFKey(pr.protoname.toLower(), value);
			else
				query.addBindValue(pr.protoname.toLower(), value);
		}
		else if (pr.type == Meta::Type::Bool)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMBool));
		else if (pr.type == Meta::Type::Short)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMShort));
		else if (pr.type == Meta::Type::UShort)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMUShort));
		else if (pr.type == Meta::Type::Int)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMInt));
		else if (pr.type == Meta::Type::UInt)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMUInt));
		else if (pr.type == Meta::Type::Long)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMLong));
		else if (pr.type == Meta::Type::ULong)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMULong));
		else if (pr.type == Meta::Type::Float)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMFloat));
		else if (pr.type == Meta::Type::Double)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMDouble));
		else if (pr.type == Meta::Type::StdString)
			query.addBindValue(pr.protoname.toLower(), QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMStdString)));
		else if (pr.type == Meta::Type::String)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMString));
		else if (pr.type == Meta::Type::StringList)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMStringList).join("\n"));
		else if (pr.type == Meta::Type::Uuid)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMUuid).toString(QUuid::WithoutBraces));
		else if (pr.type == Meta::Type::Time)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMTime).toString(Qt::ISODateWithMs));
		else if (pr.type == Meta::Type::Date)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMDate).toString(Qt::ISODate));
		else if (pr.type == Meta::Type::DateTime)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime).toString(Qt::ISODateWithMs));
		else if (pr.type == Meta::Type::ByteArray)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray));
		else if (pr.type == Meta::Type::Byte)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMByte));
		else if (pr.type == Meta::Type::Money)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
			query.addBindCheckedValue(pr.protoname.toLower(), QString::number((double(value)+(value > 0 ? 1 : -1)*0.000001), 'f', 2));
		}
		else if (pr.type == Meta::Type::Type)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMType));
		else if (pr.type == Meta::Type::State)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMState));
		else if (pr.type == Meta::Type::Flags)
			query.addBindValue(pr.protoname.toLower(), CAST_CONST_DATAREL_TO_TYPEREL(RMFlags));
		else if (pr.type == Meta::Type::PKeyList && pr.role == Meta::FieldRole::Field)
		{
			QString str;
			auto list = CAST_CONST_DATAREL_TO_TYPEREL(RMPKeyList);
			for (const auto& id: list)
				str.append(QString::number(id)+";");
			query.addBindValue(pr.protoname.toLower(), str);
		}
		else
			Q_ASSERT(0);
}

} // Ramio::
