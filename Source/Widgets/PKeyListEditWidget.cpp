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


#include "PKeyListEditWidget.h"
#include "TableWidget.h"
#include <Global/Text.h>
#include <Gui/Global.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolButton>

namespace Ramio {

PKeyListEditWidget::PKeyListEditWidget(const Meta::Property& pr, const AbstractMetaSet* set, QWidget* parent)
	: QWidget(parent),
	  set_(set)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	auto* toplayout = new QHBoxLayout();
	toplayout->addWidget(new QLabel("Список ключей: " + BOLD(pr.prettyname)));
	layout->addLayout(toplayout);
	layout->addLayout(elementLayouts_ = new QVBoxLayout());
	if (set)
	{
		toplayout->addStretch();
		QToolButton* button;
		toplayout->addWidget(button = new QToolButton());
		button->setText("Добавить");
		connect(button, &QToolButton::clicked, this, &PKeyListEditWidget::onAddPressed);
	}
	else
		elementLayouts_->addWidget(keyList_ = new QLabel());
}

PKeyListEditWidget::~PKeyListEditWidget()
{
}

void PKeyListEditWidget::updateFromData(const RMPKeyList& list)
{
	values_ = list;
	if (keyList_)
	{
		QString text = "{";
		for (auto id: list)
		{
			if (text.length()==1)
				text += ", ";
			text += QString::number(id);
		}
		text += "}";
		keyList_->setText(text);
	}
	else if (set_ && set_->aSet())
	{
		for (auto id: list)
			if (auto item = set_->aSet()->itemById(id))
				accepted(*item);
	}
}

void PKeyListEditWidget::onAddPressed()
{
	auto widget = new TableWidget(*set_, this);
	connect(widget, &Ramio::TableWidget::activated, this, &PKeyListEditWidget::accepted);
	SHOW_MODAL_DIALOG_WIDGET(widget);
}

void PKeyListEditWidget::accepted(const Item& item)
{
	values_.append(item.id());

	QString text;
	for (int index = 1; index < set_->meta().properties.count(); index++)
		text += set_->meta().properties[index].prettyname + ": " + item.data().valueToString(set_->meta().properties[index].type, set_->meta().properties[index].diff);
	text += " <a href=\"rem\">удалить</a>";

	QLabel* label;
	elementLayouts_->addWidget(label = new QLabel(text));
	labels_.append(label);
	connect(label, &QLabel::linkActivated, this, &PKeyListEditWidget::removeItem);
}

void PKeyListEditWidget::removeItem()
{
	if (auto label = static_cast<QLabel*>(sender()))
	{
		auto index = labels_.indexOf(label);
		values_.removeAt(index);
		labels_.removeAt(index);
		delete label;
	}
}

} // Ramio::
