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
#include "ItemSetServer.h"
// Ramio
#include <ItemWidgets/ContentBaseWidget.h>
#include <ItemWidgets/ContentDetailWidget.h>
#include <ItemWidgets/DetailBaseWidget.h>
#include <ItemWidgets/CreateBaseWidget.h>
#include <Ui/Global.h>
#include <Sets/UISets.h>


MainWidget::MainWidget(ItemSetServer& server, QWidget* parent)
	: QWidget(parent),
	  server_(server)
{
	auto* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	layout->addWidget(userWidget = new QWidget(this));
	auto* userLayout = new QVBoxLayout(userWidget);
	userLayout->addWidget(usersWidget_ = new Ramio::ContentBaseWidget(server_.users(), server_.users().meta(), userWidget));
	static_cast<Ramio::ContentBaseWidget*>(usersWidget_)->setColumns(QList<quint8>()<<2<<3<<4);

	layout->addWidget(taskWidget = new QWidget(this));
	auto* taskLayout = new QVBoxLayout(taskWidget);
	taskLayout->addWidget(tasksWidget_ = new Ramio::ContentBaseWidget(server_.tasks(), server_.tasks().meta(), userWidget));

	taskWidget->setHidden(true);

	connect(&server_.currentUser(), &Ramio::ItemWatcher::added, this, &MainWidget::onLogined);
	connect(&server_.currentUser(), &Ramio::ItemWatcher::deleted, this, &MainWidget::onLogout);

	loadSettings();
}

MainWidget::~MainWidget()
{
	saveSettings();
}

void MainWidget::loadSettings()
{
	LOAD_SETTINGS(static_cast<Ramio::ContentBaseWidget*>(usersWidget_));
	LOAD_SETTINGS(static_cast<Ramio::ContentBaseWidget*>(tasksWidget_));
	LOAD_GEOMETRY(this);
}

void MainWidget::saveSettings()
{
	SAVE_GEOMETRY(this);
	SAVE_SETTINGS(static_cast<Ramio::ContentBaseWidget*>(usersWidget_));
	SAVE_SETTINGS(static_cast<Ramio::ContentBaseWidget*>(tasksWidget_));
}

void MainWidget::onLogined()
{
	userWidget->setHidden(true);
	taskWidget->setHidden(false);
}

void MainWidget::onLogout()
{
	userWidget->setHidden(false);
	taskWidget->setHidden(true);
}
