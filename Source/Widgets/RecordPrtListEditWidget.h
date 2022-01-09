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
class QLabel;
class QVBoxLayout;

namespace Ramio {

class RAMIO_LIB_EXPORT RecordPrtListEditWidget : public QWidget
{
public:
	RecordPrtListEditWidget(const Meta::Property& pr, const Meta::Description& meta, QWidget* parent = Q_NULLPTR);
	~RecordPrtListEditWidget() Q_DECL_OVERRIDE;

	void onAddPressed();

	void updateFromDataPtrList(const QList<const BaseItemData*>& datalist);

	QList<BaseItemData*> takeRecords();
	const QList<BaseItemData*>& records() {return datalist_;}

private:
	void accepted(BaseItemData* newData);
	void removeItem();

private:
	const Meta::Description& meta_;
	QVBoxLayout* elementLayouts_;
	QList<BaseItemData*> datalist_;
	QList<QLabel*> labels_;
};

} // Ramio::
