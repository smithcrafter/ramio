/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Tests, a Qt-based casual C++ classes for quick application writing.
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

#include <SuperItem.h>
#include <Widgets/ContentWidget.h>
#include <Widgets/TableWidget.h>
#include <Widgets/ItemDetailWidget.h>

using SuperItemContentWidget = Ramio::ContentWidget<SuperItem, Ramio::TableWidget, Ramio::ItemDetailWidget>;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(MetaSuperItemSet& set, QWidget* parent = Q_NULLPTR);
	~Widget();

	SuperItemContentWidget* widget() {return Q_NULLPTR;}
	void createWidget();

private:
	MetaSuperItemSet& set_;
	SuperItemContentWidget* widget_ = Q_NULLPTR;
};
