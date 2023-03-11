/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#define CREATE_EXIT_ACTION(widget) \
	auto* exitAction = new QAction(widget); \
	exitAction->setShortcut(QKeySequence("Alt+X")); \
	connect(exitAction, &QAction::triggered, widget, &QWidget::close); \
	widget->addAction(exitAction);

#define CREATE_FULLSCREEN_ACTION(widget) \
	auto* fullScreenAction = new QAction(widget); \
	bool widgetIsMaximized = widget->isMaximized(); \
	fullScreenAction->setShortcut(QKeySequence("F11")); \
	connect(fullScreenAction, &QAction::triggered, [widget, &widgetIsMaximized](bool) { \
		if (widget->isFullScreen()) \
			widgetIsMaximized ? widget->showMaximized() : widget->showNormal(); \
		else { \
			widgetIsMaximized = widget->isMaximized(); widget->showFullScreen();}});\
	widget->addAction(fullScreenAction);

