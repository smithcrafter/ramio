/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include <QtWidgets/QWidget>
#include <Items/StructItemSet.h>
#include <Items/AbstractMetaSet.h>
class QLabel; class QVBoxLayout;

namespace Ramio {

class RAMIO_LIB_EXPORT PKeyListEditWidget : public QWidget
{
public:
	PKeyListEditWidget(const Meta::Property& pr, const AbstractMetaSet* set, QWidget* parent = Q_NULLPTR);
	~PKeyListEditWidget() Q_DECL_OVERRIDE;

	const RMPKeyList& values() const {return values_;}

	void updateFromData(const RMPKeyList& list);

private:
	void onAddPressed();
	void accepted(const Item& item);
	void removeItem();

private:
	const AbstractMetaSet* set_;
	QVBoxLayout* elementLayouts_;
	QList<QLabel*> labels_;
	QLabel* keyList_ = Q_NULLPTR;
	RMPKeyList values_;
};

} // Ramio::
