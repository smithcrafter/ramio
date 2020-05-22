/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Examples, a Qt-based casual C++ classes for quick application writing.
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

#include "MainWidget.h"
#include "ItemSetClient.h"
#include "TasksSimpleWidget.h"
#include <Widgets/TableWidget.h>
#include <Gui/Global.h>
#include <Global/Text.h>
#include <Log/Log.h>
#include <Sets/UISets.h>
// Qt
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTabWidget>

MainWidget::MainWidget(ItemSetClient& itemSetClient, QWidget* parent)
	: QWidget(parent),
	  client_(itemSetClient)
{
	UI_CREATE_HLAYOUT(layout);
	layout->addWidget(tabWidget_ = new QTabWidget(this));

	tabWidget_->addTab(tasksSimpleWidget_ = new TasksSimpleWidget(client_.tasks()), tr("Задачи"));
	tabWidget_->addTab(tasksWidget_ = new Ramio::TableWidget(client_.arhiveTasks(), client_.tasks().meta()), tr("Архив"));
	tasksWidget_->setColumns({"time", "stateStr", "text"});

	auto* logWidget = new QListWidget(this);
	tabWidget_->addTab(logWidget, tr("Журнал"));
	Ramio::Logger::instance().setLogWidget(logWidget);

	connect(tasksSimpleWidget_, &TasksSimpleWidget::requestCreate, &itemSetClient, &ItemSetClient::requestCreate);
	connect(tasksSimpleWidget_, &TasksSimpleWidget::requestChangeCompleteStatus,
			&itemSetClient, &ItemSetClient::requestChangeCompleteStatus);
	connect(tasksSimpleWidget_, &TasksSimpleWidget::requestChangeArhiveStatus,
			&itemSetClient, &ItemSetClient::requestChangeArhiveStatus);

	connect(tasksWidget_->table(), &QTableView::doubleClicked, this, &MainWidget::onTaskDoubleClicked);

	PREPARE_TABLE(tasksWidget_->table());
}

void MainWidget::onTaskDoubleClicked(const QModelIndex &index)
{
	if (auto* task = static_cast<Task*>(index.data(Qt::UserRole).value<void*>()))
		client_.requestDelete(*task);
}
