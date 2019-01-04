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

#include "ItemEditBaseWidget.h"
#include "ItemWidgetHelper.h"
// Ramio
#include <Ui/Global.h>
#include <Items/MetaItemSet.h>
#include <Global/Text.h>
// Qt
#include <QtWidgets/QPushButton>

namespace Ramio {

ItemEditBaseWidget::ItemEditBaseWidget(const AbstractMetaSet& set, const Item* item, QWidget* parent)
	: QWidget(parent),
	  set_(set),
	  item_(item)
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
			editWidgets_.insert(pr.dif, widget);
		}

	layout->addWidget(new QWidget(this), ++index, 0, 1, 2);
	layout->setRowStretch(index, 1);

	auto* buttonLayout = new QHBoxLayout();
	QPushButton* button;
	buttonLayout->addWidget(button = new QPushButton(tr("Сохранить"), this));
	connect(button, &QPushButton::clicked, this, &ItemEditBaseWidget::onAcceptClicked);
	buttonLayout->addWidget(button = new QPushButton(tr("Отмена"), this));
	connect(button, &QPushButton::clicked, this, &ItemEditBaseWidget::canceled);
	layout->addLayout(buttonLayout, ++index, 0, 1, 2);

	if (item_)
	{
		this->setItemData(*item_);
		// TODO add item watcher
	}
}

void ItemEditBaseWidget::setItemData(const Item &item)
{
	for (const Meta::Property& pr: set_.meta().properties)
		if (editWidgets_.contains(pr.dif))
		{
			auto& data = static_cast<const MetaItemData&>(item.data());
			updateEditWidgetFromData(data, pr, set_, editWidgets_[pr.dif]);
		}
}

void ItemEditBaseWidget::onAcceptClicked()
{
	auto* item = set_.createMetaItem();

	if (item_)
	{
		item->data().id = item_->id();
		item->data().uuid = item_->uuid();
		item->data().type = item_->type();
	}

	for (const Meta::Property& pr: set_.meta().properties)
		if (editWidgets_.contains(pr.dif))
		{
			auto& data = static_cast<MetaItemData&>(item->data());
			updateDataFromEditWidget(data, pr, set_, editWidgets_[pr.dif]);

		}

	emit accepted(item);
}

} // Ramio::
