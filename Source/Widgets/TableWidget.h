/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#pragma once

#include <QtWidgets/QWidget>
class QTableView;
#include <Items/MetaItemSet.h>
#include <Items/AbstractMetaSet.h>
class QSortFilterProxyModel;

namespace Ramio {

class MetaItemsModel;
class ModelFilterWidget;

class RAMIO_LIB_EXPORT TableWidget : public QWidget
{
	Q_OBJECT
public:
	TableWidget(MetaItemsModel& model, QSortFilterProxyModel* fmodel = Q_NULLPTR, QWidget* parent = Q_NULLPTR);
	TableWidget(const AbstractListSet& set, const Meta::Description& meta, QWidget* parent = Q_NULLPTR);
	TableWidget(const AbstractMetaSet& set, QWidget* parent = Q_NULLPTR);

	void loadSettings();
	void saveSettings();

	void reload();

	void setColumnIndexes(const QList<quint8>& columns);
	void setColumns(const QStringList& names);
	void setCheckable();

	QTableView* table() { return table_; }
	ModelFilterWidget* filterWidget() {return modelFilterWidget_;}

	Ramio::Item* currentItem();
	void selectItem(Ramio::Item* item);

signals:
	void selectedChanged(const Item* item);
	void activated(const Item& item);

private:
	MetaItemsModel* model_;
	QTableView* table_;
	ModelFilterWidget* modelFilterWidget_;
};

} // Ramio::
