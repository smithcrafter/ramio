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

#include "ModelFilterWidget.h"
#include <Ui/Global.h>
// Qt5
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtCore/QSortFilterProxyModel>

namespace Ramio {

ModelFilterWidget::ModelFilterWidget(QSortFilterProxyModel& model, QWidget* parent)
	: QWidget(parent),
	  model_(model)
{
	UI_CREATE_HLAUOUT(layout);
	layout->addWidget(new QLabel(tr("Filter"), this));
	layout->addWidget(filterEdit_ = new QLineEdit(this));

	connect(filterEdit_, &QLineEdit::textChanged, this, &ModelFilterWidget::updateFilter);
}

void ModelFilterWidget::updateFilter(const QString& text)
{
	model_.setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
	model_.setFilterKeyColumn(-1);
}

} // Ramio::
