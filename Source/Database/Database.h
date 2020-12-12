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

#pragma once

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
class QSqlQuery;
#include "DatabaseOptions.h"

namespace Ramio {

struct ItemData;
namespace Meta {struct Property;}
struct SqlQuery;

class RAMIO_LIB_EXPORT Database : public QObject
{
	Q_OBJECT
public:
	Database(SupportedDatabaseType dbtype, const QString& connectionName, QObject* parent = Q_NULLPTR)
		: Database(dbtype, connectionName, DatabaseConfig(), parent) {}
	Database(SupportedDatabaseType dbtype, const QString& connectionName, const DatabaseConfig& config, QObject* parent = Q_NULLPTR);
	~Database() Q_DECL_OVERRIDE;

	SupportedDatabaseType type() const {return type_;}

	bool initTable(const Meta::Description& md);
	bool initTable(const MetaTable& metaTable);

	bool openWithInnerConfig() {return open(config_);}
	bool open(const DatabaseConfig& config);
	bool isOpen() const;
	void close();
	QString lastError();

	bool startTransaction();
	bool stopTransaction();

	ResDesc insertMetaItemData(ItemData& itemData, const Meta::Description& md);
	ResDesc updateMetaItemData(const ItemData& itemData, const Meta::Description& md);
	ResDesc deleteMetaItemData(const ItemData& itemData, const Meta::Description& md);
	ResDesc selectMetaItemDataSet(AbstractMetaSet& metaset, const QString& condition = emptyString) const;
	ResDesc selectMetaItemDataSet(AbstractSet& aset, const Meta::Description& md, const QString& condition = emptyString) const;

signals:
	void stateChanged();

private:
	void bindQueryValues(const ItemData& data, SqlQuery& query, const QVector<Meta::Property>& prop);

protected:
	SupportedDatabaseType type_;
	DatabaseConfig config_;
	QSqlDatabase database_;
	QScopedPointer<QSqlQuery> query_;
	bool dlog_ = false;
};

} // Ramio::
