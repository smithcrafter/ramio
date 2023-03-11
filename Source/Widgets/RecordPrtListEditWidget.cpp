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


#include "RecordPrtListEditWidget.h"
#include "DataEditWidget.h"
#include <Global/Text.h>
#include <Gui/Global.h>
// Qt5
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolButton>


namespace Ramio {

RecordPrtListEditWidget::RecordPrtListEditWidget(const Meta::Property& pr, const Meta::Description& meta, QWidget* parent)
	: QWidget(parent),
	  meta_(meta)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	auto* toplayout = new QHBoxLayout();
	toplayout->addWidget(new QLabel("Список элементов: " + BOLD(pr.prettyname)));
	layout->addLayout(toplayout);
	if (meta_.createDataFunction)
	{
		toplayout->addStretch();
		QToolButton* button;
		toplayout->addWidget(button = new QToolButton());
		button->setText("Добавить");
		connect(button, &QToolButton::clicked, this, &RecordPrtListEditWidget::onAddPressed);
	}
	layout->addLayout(elementLayouts_ = new QVBoxLayout());
}

RecordPrtListEditWidget::~RecordPrtListEditWidget()
{
	qDeleteAll(datalist_);
}

void RecordPrtListEditWidget::onAddPressed()
{
	auto widget = new DataEditWidget(meta_, this);
	connect(widget, &Ramio::DataEditWidget::canceled, widget, &QWidget::close);
	connect(widget, &Ramio::DataEditWidget::accepted, this, &RecordPrtListEditWidget::accepted);
	SHOW_MODAL_DIALOG_WIDGET(widget);
}

void RecordPrtListEditWidget::updateFromDataPtrList(const QList<const BaseItemData *>& datalist)
{
	if (meta_.createDataFunction)
	{
		for (const BaseItemData* rec: datalist)
		{
			BaseItemData* subdata = meta_.createDataFunction->operator()();
			Meta::copyData(meta_, *rec, *subdata);
			accepted(subdata);
		}
	}
}

QList<BaseItemData*> RecordPrtListEditWidget::takeRecords()
{
	QList<BaseItemData*> res = datalist_;
	qDeleteAll(labels_);
	labels_.clear();
	datalist_.clear();
	return res;
}

void RecordPrtListEditWidget::accepted(BaseItemData* newData)
{
	datalist_.append(newData);

	if (auto* widget = static_cast<QWidget*>(sender()))
		widget->close();

	QString text;
	for (int index = 1; index < meta_.properties.count(); index++)
		text += meta_.properties[index].prettyname + ": " + newData->valueToString(meta_.properties[index].type, meta_.properties[index].diff);
	text += " <a href=\"rem\">удалить</a>";

	QLabel* label;
	elementLayouts_->addWidget(label = new QLabel(text));
	labels_.append(label);
	connect(label, &QLabel::linkActivated, this, &RecordPrtListEditWidget::removeItem);
}

void RecordPrtListEditWidget::removeItem()
{
	if (auto label = static_cast<QLabel*>(sender()))
	{
		auto index = labels_.indexOf(label);
		delete datalist_[index];
		datalist_.removeAt(index);
		labels_.removeAt(index);
		delete label;
	}
}

} // Ramio::
