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

#include "TasksSimpleWidget.h"
#include "TaskSimpleWidget.h"
#include <../ItemSetServer/Tasks.h>
#include <Ui/Global.h>
#include <Global/Text.h>
// Qt
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QEvent>
#include <QtCore/QTimer>

TasksSimpleWidget::TasksSimpleWidget(const MetaTaskSet& tasks, QWidget* parent)
	: QWidget(parent),
	  tasks_(tasks)
{
	auto* layout = new QVBoxLayout(this);
	auto* hlayout = new QHBoxLayout();
	hlayout->setMargin(15);
	hlayout->setSpacing(15);
	layout->addLayout(hlayout);
	hlayout->addWidget(newTaskEdit_ = new QLineEdit());
	newTaskEdit_->setPlaceholderText(tr("Пишите новую задачу"));
	auto* addButton = new QPushButton(tr("Добавить"));
	hlayout->addWidget(addButton);
	connect(addButton, &QPushButton::clicked, this, &TasksSimpleWidget::onClickCreateAction);

	QFont font = this->font();
	font.setPointSize(font.pointSize()+10);
	newTaskEdit_->setFont(font);
	addButton->setFont(font);

	layout->addWidget(errorLabel_ = new QLabel(this));

	auto* taskInnerWidget = new QWidget(this);
	auto* taskInnerLayout = new QVBoxLayout(taskInnerWidget);
	taskInnerLayout->setMargin(0);
	taskInnerLayout->addLayout(tasksLayout_ = new QVBoxLayout());
	taskInnerLayout->addStretch();
	auto* area = new QScrollArea(this);
	area->setWidget(taskInnerWidget);
	area->setWidgetResizable(true);

	layout->addWidget(area, 1);
	this->refreshAll();
	layout->setMargin(0);
	layout->setSpacing(0);
	tasksLayout_->setMargin(0);
	tasksLayout_->setSpacing(0);
	connect(&tasks, &MetaTaskSet::added, this, &TasksSimpleWidget::refreshAll);
	connect(&tasks, &MetaTaskSet::changed, this, &TasksSimpleWidget::refreshAll);
	connect(&tasks, &MetaTaskSet::deleted, this, &TasksSimpleWidget::refreshAll);
	connect(&tasks, &MetaTaskSet::reloaded, this, &TasksSimpleWidget::refreshAll);
}

void TasksSimpleWidget::refreshAll()
{
	taskWidgets_.clear();

	while (tasksLayout_->count()) {
		QWidget *w = tasksLayout_->itemAt(0)->widget();
		tasksLayout_->removeWidget(w);
		w->deleteLater();
	}
	for (auto* task : tasks_.items())
		if (!task->isArhived())
		{
			auto* widget = new TaskSimpleWidget(*task);
			tasksLayout_->addWidget(widget);
			taskWidgets_.insert(task, widget);
			connect(widget, &TaskSimpleWidget::requestChangeCompleteStatus, this, &TasksSimpleWidget::requestChangeCompleteStatus);
			widget->installEventFilter(this);
		}
}

void TasksSimpleWidget::onErrorCreate(const QString& error)
{
	errorLabel_->setText(REDTEXT(error));
	QTimer::singleShot(2000, errorLabel_, &QLabel::clear);
}

bool TasksSimpleWidget::eventFilter(QObject* obj, QEvent* event)
{
	if (obj && event->type() == QEvent::MouseButtonPress)
	{
		if (activeTaskSimpleWidget_.data() == obj)
		{
			activeTaskSimpleWidget_->changeSelected(false);
			activeTaskSimpleWidget_ = Q_NULLPTR;
			return true;
		}

		if (activeTaskSimpleWidget_)
			activeTaskSimpleWidget_->changeSelected(false);
		activeTaskSimpleWidget_ = static_cast<TaskSimpleWidget*>(obj);
		activeTaskSimpleWidget_->changeSelected(true);
		return true;
	}
	else if (obj && event->type() == QEvent::MouseButtonDblClick)
	{
		if (const Task* task = taskWidgets_.key(static_cast<TaskSimpleWidget*>(obj), Q_NULLPTR))
			emit requestChangeArhiveStatus(*task);
		return true;
	}
	else
		return QObject::eventFilter(obj, event);
}

void TasksSimpleWidget::onClickCreateAction()
{
	if (!newTaskEdit_->text().isEmpty())
		emit requestCreate(newTaskEdit_->text(), QColor(qrand()%256, qrand()%256, qrand()%256));
}
