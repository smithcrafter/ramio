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

#include "CreateBaseWidget.h"
#include "ItemWidgetHelper.h"
// Ramio
#include <Ui/Global.h>
#include <Items/MetaItemSet.h>
#include <Global/Text.h>
// Qt
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

namespace Ramio {

CreateBaseWidget::CreateBaseWidget(const AbstractMetaSet& set, QWidget* parent)
	: QWidget(parent),
	  set_(set)
{
	UI_CREATE_GLAUOUT(layout);
	int index = 1;

	QLabel* label;
	layout->addWidget(label = new QLabel(BOLD(tr("Создание элемента ") % set.meta().itemName), this), 0, 0, 1, 2);
	for (const Meta::Property& pr: set_.meta().properties)
		if (QWidget* widget = createEditWidget(pr, set_, this))
		{
			layout->addWidget(widget, index, 1);
			layout->addWidget(label = new QLabel(pr.prettyname), index++, 0);
			label->setWordWrap(true);
			editWidgets_.append(widget);
		}

	layout->addWidget(new QWidget(this), ++index, 0, 1, 2);
	layout->setRowStretch(index, 1);

	auto* buttonLayout = new QHBoxLayout();
	QPushButton* button;
	buttonLayout->addWidget(button = new QPushButton(tr("Сохранить"), this));
	connect(button, &QPushButton::clicked, this, &CreateBaseWidget::onAcceptClicked);
	buttonLayout->addWidget(button = new QPushButton(tr("Отмена"), this));
	connect(button, &QPushButton::clicked, this, &CreateBaseWidget::canceled);
	layout->addLayout(buttonLayout, ++index, 0, 1, 2);
}

void CreateBaseWidget::onAcceptClicked()
{
	auto* item = set_.createMetaItem();
	int counter = 0;
	for(const Meta::Property& pr: set_.meta().properties)
	{
		auto& data = static_cast<MetaItemData&>(item->data());

		if (pr.type == Meta::Type::PKey && pr.relationtype != Meta::FieldType::PKey)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (set_.meta().relations[pr.name] && set_.relations()[pr.name])
			{
				int index = static_cast<QComboBox*>(editWidgets_[counter])->currentIndex();
				if (index > 0)
					value = set_.relations()[pr.name]->items()[index-1]->id();
				else
					value = 0;
			}
			else
				value = RMetaPKey(static_cast<QSpinBox*>(editWidgets_[counter])->value());
		}
		else if (pr.type == Meta::Type::Int)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaInt);
			value = static_cast<QSpinBox*>(editWidgets_[counter])->value();
		}
		else if (pr.type == Meta::Type::String)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaString);
			value = static_cast<QLineEdit*>(editWidgets_[counter])->text();
		}
		else if (pr.type == Meta::Type::Double)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDouble);
			value = static_cast<QDoubleSpinBox*>(editWidgets_[counter])->value();
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaDateTime);
			value = static_cast<QDateTimeEdit*>(editWidgets_[counter])->dateTime();
		}
		else if (pr.type == Meta::Type::Money)
		{
			auto& value = CAST_DATAREL_TO_TYPEREL(RMetaMoney);
			value = static_cast<QDoubleSpinBox*>(editWidgets_[counter])->value();
		}
		else
			continue;
		counter++;
	}
	emit accepted(item);
}

} // Ramio::
