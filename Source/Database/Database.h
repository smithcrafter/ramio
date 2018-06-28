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

#pragma once

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
class QSqlQuery;
#include "DatabaseOptions.h"

namespace Ramio {
struct ItemData;

class DLL_EXPORT Database  : public QObject
{
public:
	Database(SupportedDatabaseType dbtype, const QString& connectionName, QObject* parent = Q_NULLPTR);
	~Database() Q_DECL_OVERRIDE;

	bool initTable(const Meta::Description& metadesc);
	bool initTable(const MetaTable& metaTable);

	bool open(const DataBaseConfig& config);
	bool isOpen() const;
	void close();
	QString lastError();

	ResDesc saveMetaItemData(ItemData& itemData, const Meta::Description& rmd);
	ResDesc udateMetaItemData(const ItemData& item, const Meta::Description& rmd);
	ResDesc deleteMetaItemData(const ItemData& item, const Meta::Description& rmd);
	ResDesc selectMetaItemData(AbstractMetaSet& metaset, const QString& condition = QString()) const;

protected:
	SupportedDatabaseType type_;
	QSqlDatabase database_;
	QScopedPointer<QSqlQuery> query_;
};

} // Ramio::
