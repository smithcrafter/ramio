/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <ramio.h>
#include <QtWidgets/QWidget>
#include <QtCore/QMap>

namespace Ramio {

class AbstractMetaSet;
class Item;

class DLL_EXPORT ItemEditBaseWidget: public QWidget
{
	Q_OBJECT
public:
	ItemEditBaseWidget(const AbstractMetaSet& set, const Item* item = Q_NULLPTR, QWidget* parent = Q_NULLPTR);

	void setItemData(const Item& item);

	const Item* originItem() const {return item_;}

signals:
	void accepted(Item* newItem);
	void canceled();

private:
	void onAcceptClicked();

private:
	const AbstractMetaSet& set_;
	const Item* item_ = Q_NULLPTR;
	QMap<ptrdiff_t, QWidget*> editWidgets_;
};

} // Ramio::
