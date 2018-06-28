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

#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QMap>
#include <QtCore/QPointer>
class QLabel;
class QLineEdit;
class QVBoxLayout;
class Task;
class MetaTaskSet;
class TaskSimpleWidget;

class TasksSimpleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TasksSimpleWidget(const MetaTaskSet& tasks, QWidget* parent = Q_NULLPTR);
	void refreshAll();

	void onErrorCreate(const QString& error);

signals:
	void requestCreate(QString text, QColor color);
	void requestChangeCompleteStatus(const Task& task);
	void requestChangeArhiveStatus(const Task& task);

private:
	bool eventFilter(QObject* obj, QEvent* event) Q_DECL_OVERRIDE;
	void onClickCreateAction();

private:
	const MetaTaskSet& tasks_;
	QVBoxLayout* tasksLayout_;
	QMap<const Task*, TaskSimpleWidget*> taskWidgets_;
	QPointer<TaskSimpleWidget> activeTaskSimpleWidget_;
	QLineEdit* newTaskEdit_;
	QLabel* errorLabel_;
};
