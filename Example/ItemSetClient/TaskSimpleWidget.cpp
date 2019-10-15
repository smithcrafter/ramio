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

#include "TaskSimpleWidget.h"
#include <../ItemSetServer/Tasks.h>
#include <Gui/Global.h>
// Qt
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QHBoxLayout>
#include <QtGui/QPainter>

TaskSimpleWidget::TaskSimpleWidget(const Task& task, QWidget* parent)
	:  QWidget(parent),
	  task_(task)
{
	this->setObjectName(QStringLiteral("TaskSimpleWidget"));

	auto* layout = new QHBoxLayout(this);
	label_ = new QLabel(task.data().text,this);
	miniwid_ = new QWidget;
	miniwid_->setFixedWidth(4);
	layout->addWidget(miniwid_);
	layout->addWidget(label_);
	layout->addStretch();
	checkBox_ = new QCheckBox();
	layout->addWidget(checkBox_);
	checkBox_->setChecked(task.isFinished());
	layout->setSpacing(0);
	layout->setMargin(0);
	updateStyleSheet();
	connect(checkBox_, &QCheckBox::stateChanged, this, &TaskSimpleWidget::onCheckboxChecked);
}

void TaskSimpleWidget::onCheckboxChecked()
{
	if ((checkBox_->checkState() == Qt::CheckState::Checked) != task_.isFinished())
		emit requestChangeCompleteStatus(task_);
	checkBox_->setCheckState(task_.isFinished() ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void TaskSimpleWidget::updateStyleSheet()
{
	QColor color_(task_.data().color);

	static QString style("QWidget#TaskSimpleWidget{border-bottom: 1px solid #000; background-color:rgba(%1, %2, %3, %4); %5}");
	setStyleSheet(style.arg(color_.red()).arg(color_.green()).arg(color_.blue()).arg(selected_?220:120)
				  .arg(selected_?("border: 5px solid "+color_.name()+";"):""));
	label_->setStyleSheet("font-size:18pt; margin:5px;");
	miniwid_->setStyleSheet(QString("border:0px;border-left: 4px solid %1;margin:2 0 2 0;").arg(color_.name()));
	checkBox_->setStyleSheet("QCheckBox {spacing: 4px;} "
							 "QCheckBox::indicator {width: 24px; height: 24px;border:1px solid #888;} "
							 "QCheckBox::indicator:checked {image: url(://Images/check.png);} ");
}

void TaskSimpleWidget::paintEvent(QPaintEvent*)
{
	QStyleOption styleOption;
	styleOption.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}
