/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ModelFilterWidget.h"
#include <Global/Text.h>
#include <Gui/Global.h>
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
	UI_CREATE_HLAYOUT_ZERO_MARGINSPACING(layout);
	layout->addWidget(filterLabel_ = new QLabel(filterText_ = tr("Фильтр"), this));
	layout->addSpacing(5);
	layout->addWidget(filterEdit_ = new QLineEdit(this));
	connect(filterEdit_, &QLineEdit::textChanged, this, &ModelFilterWidget::updateFilter);
	auto* focusAction = new QAction(this);
	focusAction->setShortcut(QKeySequence("Ctrl+F"));
	connect(focusAction, &QAction::triggered, filterEdit_, static_cast<void (QLineEdit::*)()>(&QLineEdit::setFocus));
	this->addAction(focusAction);
}

void ModelFilterWidget::setFilter(const QString& text)
{
	filterEdit_->setText(text);
}

void ModelFilterWidget::updateFilter(const QString& text)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	model_.setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
#else
	model_.setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
#endif
	model_.setFilterKeyColumn(-1);
	filterLabel_->setText(text.isEmpty() ? filterText_ : BOLD(filterText_));
}

} // Ramio::
