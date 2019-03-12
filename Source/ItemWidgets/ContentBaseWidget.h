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

#pragma once

#include <QtWidgets/QWidget>
class QTableView;
#include <Items/MetaItemSet.h>

namespace Ramio {

class MetaItemsModel;

class DLL_EXPORT ContentBaseWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ContentBaseWidget(const AbstractSet& set, const Meta::Description& metaDescription, QWidget* parent = Q_NULLPTR);

	void loadSettings();
	void saveSettings();

	void reload();

	void setColumns(const QList<quint8>& columns);
	QTableView* table() { return table_; }

signals:
	void selectedChanged(const Item* item);

private:
	MetaItemsModel* model_;
	QTableView* table_;
};

} // Ramio::
