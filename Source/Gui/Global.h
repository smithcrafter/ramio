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

#include <QtWidgets/QToolBar>
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>
#include <ramio/global/text.h>

#define UI_MARGIN_PX 2
#define UI_SPACING_PX 1

#define UI_SET_MARGINSPACING(layout) \
	layout->setContentsMargins(UI_MARGIN_PX, UI_MARGIN_PX, UI_MARGIN_PX, UI_MARGIN_PX); \
	layout->setSpacing(UI_SPACING_PX);

#define UI_SET_ZERO_MARGINSPACING(layout) \
	layout->setContentsMargins(0, 0, 0, 0); \
	layout->setSpacing(0);

#define UI_CREATE_VLAYOUT(layout) \
	auto* layout = new QVBoxLayout(this); \
	UI_SET_MARGINSPACING(layout)

#define UI_CREATE_HLAYOUT(layout) \
	auto* layout = new QHBoxLayout(this); \
	UI_SET_MARGINSPACING(layout)

#define UI_CREATE_VLAYOUT_ZERO_MARGINSPACING(layout) \
	auto* layout = new QVBoxLayout(this); \
	UI_SET_ZERO_MARGINSPACING(layout)

#define UI_CREATE_HLAYOUT_ZERO_MARGINSPACING(layout) \
	auto* layout = new QHBoxLayout(this); \
	UI_SET_ZERO_MARGINSPACING(layout)

#define UI_CREATE_GLAYOUT(layout) \
	auto* layout = new QGridLayout(this); \
	UI_SET_MARGINSPACING(layout)


#define UI_CREATE_TOOLBAR_IN_WIDGET(toolbar, widget, layout, text) \
	auto* toolbar = new QToolBar(widget); \
	auto* toolbar##Label = new QLabel(text, toolbar); \
	toolbar->addWidget(toolbar##Label); \
	layout->setMenuBar(toolbar);

#define UI_CREATE_TOOLBAR(layout, text) \
	UI_CREATE_TOOLBAR_IN_WIDGET(toolbar, this, layout, text)

#define UI_CREATE_TOOLBAR_STRECH(toolbar) \
	{ auto* strechWidget = new QWidget(); \
	strechWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); \
	toolbar->addWidget(strechWidget); }


#define UI_CREATE_SYSTEM_TRAY(icon) \
	auto* systemTrayIcon = new QSystemTrayIcon(this); \
	systemTrayIcon->setIcon(icon); \
	systemTrayIcon->show(); \
	auto* systemTrayMenu = new QMenu(this); \
	systemTrayIcon->setContextMenu(systemTrayMenu); \

#define UI_CREATE_SYSTEM_TRAY_ACTIVATION_SHOWMAXIMIZED \
	connect(systemTrayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason){ \
		if (reason == QSystemTrayIcon::ActivationReason::Trigger){this->showMaximized();this->activateWindow();} \
	});

#define UI_CREATE_SYSTEM_TRAY_NOTICER_MESSAGE(noticerPtr, logWidgetPrt) \
	connect(noticerPtr, &Ramio::Noticer::notice, [logWidgetPrt, systemTrayIcon] \
		(const QDateTime& datetime, const QString& title, const QString& str) { \
		systemTrayIcon->showMessage(title, datetime.toString(Qt::ISODate) % ": " % str,  QSystemTrayIcon::Critical, 5*1000); \
		logWidgetPrt->addItem(datetime.toString(Qt::ISODate) % " " % BOLD(title) % " " % str); \
	});


#define SHOW_WIDGET_GLOBAL_MODAL(widget) \
	widget->setAttribute(Qt::WA_DeleteOnClose, true); \
	widget->setWindowModality(Qt::ApplicationModal); \
	if (widget->windowState() == Qt::WindowMaximized) widget->showMaximized(); else widget->show();

#define SHOW_MODAL_DIALOG_WIDGET(widget) \
	widget->setWindowModality(Qt::ApplicationModal); \
	widget->setWindowFlags(Qt::Dialog); \
	widget->setAttribute(Qt::WA_DeleteOnClose); \
	widget->show();

#define PREPARE_TABLE(table) LOAD_CHECK_WIDGET(table, \
	table->setSortingEnabled(true); \
	table->setAutoScroll(false); \
	table->setSelectionBehavior(QAbstractItemView::SelectRows); \
	table->setSelectionMode(QAbstractItemView::SingleSelection); \
	table->horizontalHeader()->setHighlightSections(false); \
	table->horizontalHeader()->setStretchLastSection(true); \
	table->setTabKeyNavigation(false); \
	)

namespace Ramio {

QString appPath();

} // Ramio::
