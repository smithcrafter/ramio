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

#include <QtCore/QMap>

namespace Ramio {

enum class SupportedDatabaseType;
namespace Meta { struct Description; }

struct DatabaseSpecial
{
	QString serialKey;
};

extern const DatabaseSpecial SQLDefault_DatabaseSpecial;
extern const DatabaseSpecial Postgres_DatabaseSpecial;
extern const DatabaseSpecial SQLite_DatabaseSpecial;

const DatabaseSpecial& selectDatabaseSpecial(SupportedDatabaseType type);


class MetaTable
{
public:
	MetaTable(const Meta::Description& rmd, const DatabaseSpecial& special);

	void addFiledlRedefence(const QString& currentField, const QString& remoteTable, const QString& remoteField);

	QString tableName() const;

	QString createOnlyKeyTable() const;
	QStringList createFieldForTable() const;
	QStringList createFieldForTable(QStringList& alredyExist) const;
	QStringList createConstraintForTable() const;
	QString createFullTable() const;


private:
	const Meta::Description& rmd_;
	const DatabaseSpecial& special_;
	QMap<QString, QPair<QString, QString> > references_;
};

} // Ramio::
