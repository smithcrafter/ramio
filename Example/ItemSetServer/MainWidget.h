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

#pragma once

#include <QtWidgets/QWidget>
class ItemSetServer;

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(ItemSetServer& server, QWidget* parent = Q_NULLPTR);
	~MainWidget() Q_DECL_OVERRIDE;

	void loadSettings();
	void saveSettings();

private:
	void addUser();
	void onLogined();
	void onLogout();

private:
	ItemSetServer& server_;
	QWidget* userWidget;
	QWidget* usersWidget_;
	QWidget* taskWidget;
	QWidget* tasksWidget_;
};

