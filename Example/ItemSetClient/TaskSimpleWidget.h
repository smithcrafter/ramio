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
class QCheckBox;
class QLabel;
class Task;

class TaskSimpleWidget : public QWidget
{
	Q_OBJECT
public:
	explicit TaskSimpleWidget(const Task& task, QWidget* parent = Q_NULLPTR);

	void changeSelected(bool value) {selected_ = value; updateStyleSheet();}

signals:
	void requestChangeCompleteStatus(const Task& task);

private:
	void onCheckboxChecked();
	void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
	void updateStyleSheet();

private:
	const Task& task_;
	bool selected_ = false;
	QLabel* label_;
	QWidget* miniwid_;
	QCheckBox* checkBox_;
};
