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

#include "ContentBaseWidget.h"
#include <Models/MetaItemsModel.h>
#include <Models/MetaItemsSortFilterModel.h>
#include <Gui/Global.h>
#include <Gui/ModelFilterWidget.h>
#include <Sets/UISets.h>
// Qt5
#include <QtWidgets/QTableView>
#include <QtWidgets/QHeaderView>

namespace Ramio {

ContentBaseWidget::ContentBaseWidget(const AbstractSet& set, const Meta::Description& metaDescription, QWidget* parent)
	: QWidget(parent)
{
	UI_CREATE_VLAYOUT(layout)

	table_ = new QTableView();
	layout->addWidget(table_);
	model_ = new MetaItemsModel(set, metaDescription, table_);
	auto* proxyModel = new MetaItemsSortFilterModel(table_);
	proxyModel->setSourceModel(model_);
	table_->setModel(proxyModel);

	layout->addWidget(new ModelFilterWidget(*proxyModel, this));

	QTableView* table = table_;
	QObject::connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged,
					 [this, table](const QModelIndex& current, const QModelIndex& previous)
	{
		table->scrollTo(current, QAbstractItemView::EnsureVisible);
		const auto* last = static_cast<Item*>(previous.data(Qt::UserRole).value<void*>());
		const auto* curr = static_cast<Item*>(current.data(Qt::UserRole).value<void*>());
		if (last != curr)
			emit selectedChanged(curr);
	});
}

ContentBaseWidget::ContentBaseWidget(const AbstractMetaSet& set, QWidget* parent)
	: ContentBaseWidget(*set.aSet(), set.meta(), parent)
{
	Q_ASSERT(set.aSet());
}

void ContentBaseWidget::setColumns(const QList<quint8>& columns)
{
	model_->setColumns(columns);
}

Item* ContentBaseWidget::currentItem()
{
	return static_cast<Ramio::Item*>(table_->currentIndex().data(Qt::UserRole).value<void*>());
}

void ContentBaseWidget::selectItem(Item* item)
{
	if (!item)
		table_->selectRow(-1);
	else
		for(int i = 0; i < table_->model()->rowCount(); i++)
			if (table_->model()->index(i, 0).data(Qt::UserRole).value<void*>() == item)
			{
				table_->selectRow(i);
				return;
			}
}

void ContentBaseWidget::reload()
{
	model_->resetModel();
}

void ContentBaseWidget::loadSettings()
{
	PREPARE_TABLE(table_);
}

void ContentBaseWidget::saveSettings()
{
	SAVE_WIDGET(table_);
}

} // Ramio::
