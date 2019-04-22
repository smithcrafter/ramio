/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
#include <../../Smitto/Source/Widgets/MenuStackedWidget.h>
#include <Widgets/ContentBaseWidget.h>
#include <Gui/Global.h>
#include <Global/Text.h>
#include <Log/Log.h>
#include <Sets/UISets.h>
// Qt
#include <QtWidgets/QLabel>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

MainWidget::MainWidget(ItemSetClient& itemSetClient, QWidget* parent)
	: QWidget(parent),
	  client_(itemSetClient)
{
	UI_CREATE_HLAUOUT(layout);
	layout->addWidget(menuStackedWidget_ = new MenuStackedWidget(l1StyleSheet, l2StyleSheet));

	auto* label = new QLabel(H1(tr("Задачи")));
	label->setMinimumHeight(120);
	menuStackedWidget_->insertMenuWidget(label, tasksSimpleWidget_ = new TasksSimpleWidget(client_.tasks()));
	menuStackedWidget_->selectMenuItem(label);

	label = new QLabel(H1(tr("Архив")));
	label->setMinimumHeight(120);
	menuStackedWidget_->insertMenuWidget(label, tasksWidget_ =
			new Ramio::ContentBaseWidget(client_.arhiveTasks(), client_.tasks().meta()));
	tasksWidget_->setColumns(QList<quint8>()<<6<<4<<3);

	label = new QLabel(H1(tr("Журнал")));
	label->setMinimumHeight(120);
	auto* logWidget = new QListWidget(this);
	menuStackedWidget_->insertMenuWidget(label, logWidget);
	Ramio::Log::instance().setLogWidget(logWidget);

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
