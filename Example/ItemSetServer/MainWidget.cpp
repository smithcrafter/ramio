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
#include <Widgets/ContentBaseWidget.h>
#include <Widgets/ContentDetailWidget.h>
#include <Widgets/DetailBaseWidget.h>
#include <Widgets/ItemEditBaseWidget.h>
#include <Gui/Global.h>
#include <Sets/UISets.h>

MainWidget::MainWidget(ItemSetServer& server, QWidget* parent)
	: QWidget(parent),
	  server_(server)
{
	UI_CREATE_VLAYOUT(layout);
	UI_CREATE_TOOLBAR(layout, H3(tr("Список пользователей")));
	UI_CREATE_TOOLBAR_STRECH;
	toolbar->addAction(tr("Добавить пользователя"), this, &MainWidget::addUser);

	layout->addWidget(userWidget = new QWidget(this));
	auto* userLayout = new QVBoxLayout(userWidget);
	userLayout->addWidget(usersWidget_ = new Ramio::ContentBaseWidget(
				server_.users(), server_.users().meta(), userWidget));
	static_cast<Ramio::ContentBaseWidget*>(usersWidget_)->setColumns(
				server_.users().meta().fieldIndexes(QStringList()<<"login"<<"password"));

	layout->addWidget(taskWidget = new QWidget(this));
	auto* taskLayout = new QVBoxLayout(taskWidget);
	taskLayout->addWidget(tasksWidget_ = new Ramio::ContentBaseWidget(
				server_.tasks(), server_.tasks().meta(), userWidget));

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

void MainWidget::addUser()
{
	auto* widget = new Ramio::ItemEditBaseWidget(server_.users(), Q_NULLPTR, this);
	connect(widget, &Ramio::ItemEditBaseWidget::accepted, [this, widget](Ramio::Item* newItem)
	{
		server_.addUser(*static_cast<User*>(newItem));
		widget->close();
	});
	connect(widget, &Ramio::ItemEditBaseWidget::canceled, widget, &QWidget::close);

	SHOW_MODAL_DIALOG_WIDGET(widget);
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
