/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

#include "MenuStackedWidget.h"
#include <Ui/Global.h>
#include <QtWidgets/QStackedWidget>
#include <QtCore/QEvent>

const QString emptyStyleSheet;
const QString l1StyleSheet("QWidget{background: #C4CACA;}"); // C4CACA, текст D9D9D9
const QString l2StyleSheet("QWidget{background: #E3E3E3;}"); // E3E3E3, текст EEEEEE
const QString l3StyleSheet("QWidget{background: #F2F2F2;}"); // F2F2F2
const QString l4StyleSheet("QWidget{background: #FEFEFE;}"); // FEFEFE

MenuStackedWidget::MenuStackedWidget(const QString& activeStyleSheet, const QString& backgroundStyleSheet, QWidget* parent)
	: QWidget(parent),
	  activeStyleSheet_(activeStyleSheet),
	  backgroundStyleSheet_(backgroundStyleSheet)
{
	auto* layout = new QHBoxLayout(this);
	UI_SET_ZERO_MARGINSPACING(layout);

	baseMenuWidget_ = new QWidget(this);
	baseMenuWidget_->setStyleSheet(backgroundStyleSheet);
	auto* baseMenuLayout = new QVBoxLayout(baseMenuWidget_);
	UI_SET_ZERO_MARGINSPACING(baseMenuLayout);
	baseMenuLayout->addLayout(menuLayout_ = new QVBoxLayout());
	baseMenuLayout->addStretch();

	layout->addWidget(baseMenuWidget_);
	layout->addWidget(stackedWidget_ = new QStackedWidget(this));
}

void MenuStackedWidget::selectMenuItem(QObject* watched)
{
	QWidget* content = widgets_[static_cast<QWidget*>(watched)];
	int index = stackedWidget_->indexOf(content);
	if (index == -1)
	{
		content->setHidden(false);
		index = stackedWidget_->addWidget(content);
	}

	stackedWidget_->setCurrentIndex(index);

	if (lastActiveMenu_)
		lastActiveMenu_->setStyleSheet(emptyStyleSheet);
	lastActiveMenu_ = static_cast<QWidget*>(watched);
	lastActiveMenu_ ->setStyleSheet(activeStyleSheet_);
}

void MenuStackedWidget::insertMenuWidget(QWidget* menu, QWidget* content)
{
	widgets_.insert(menu, content);
	menuLayout_->addWidget(menu);
	menu->installEventFilter(this);
	content->setParent(this);
	content->setHidden(true);
}

void MenuStackedWidget::insertMenuStretch()
{
	menuLayout_->addStretch();
}

bool MenuStackedWidget::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		selectMenuItem(watched);
		return true;
	}
	return QWidget::eventFilter(watched, event);
}
