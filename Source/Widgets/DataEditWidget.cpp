/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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


#include "DataEditWidget.h"
#include "EditWidgetsHelper.h"
#include "Items/MetaDescription.h"
// Qt5
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

namespace Ramio {

DataEditWidget::DataEditWidget(const Meta::Description& meta, QWidget* parent)
	: QWidget(parent),
	  meta_(meta)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	for (const Meta::Property& pr2: meta.properties)
		if (QWidget* widget2 = createEditWidget(meta, pr2, Q_NULLPTR, this))
		{
			QLabel* label;
			QHBoxLayout* layout3 = new QHBoxLayout();
			layout3->addWidget(label = new QLabel(pr2.prettyname), 0);
			layout3->addWidget(widget2);
			layout->addLayout(layout3);
			label->setWordWrap(true);
			editWidgets_.insert(pr2.diff, widget2);
		}

	auto* buttonLayout = new QHBoxLayout();
	QPushButton* button;
	buttonLayout->addWidget(button = new QPushButton(tr("Добавить"), this));
	connect(button, &QPushButton::clicked, this, &DataEditWidget::onAcceptClicked);
	button->setShortcut(QKeySequence(Qt::Key_Return));

	buttonLayout->addWidget(button = new QPushButton(tr("Отмена"), this));
	connect(button, &QPushButton::clicked, this, &DataEditWidget::canceled);
	button->setShortcut(QKeySequence(Qt::Key_Escape));
	layout->addLayout(buttonLayout);
}

DataEditWidget::~DataEditWidget()
{
}

void DataEditWidget::onAcceptClicked()
{
	auto dataPtr = meta_.createDataFunction->operator()();
	for (const Meta::Property& pr: meta_.properties)
		if (editWidgets_.contains(pr.diff))
		{
			auto& data = *dataPtr;
			updateDataFromEditWidget(data, pr, Q_NULLPTR, editWidgets_[pr.diff]);
		}
	emit accepted(dataPtr);
}

} // Ramio::
