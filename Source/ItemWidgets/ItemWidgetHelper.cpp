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

#include "ItemWidgetHelper.h"
#include <Items/AbstractMetaSet.h>
// Qt
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

namespace Ramio {

QWidget* createEditWidget(const Meta::Property& pr, const AbstractMetaSet& set, QWidget* parent)
{
	if (pr.type == Meta::Type::PKey && pr.relationtype != Meta::FieldType::PKey)
	{
		if (set.meta().relations[pr.name] && set.relations()[pr.name])
		{
			auto* widget = new QComboBox(parent);
			widget->addItem(QObject::tr("Не задан"));
			for (const Ramio::Item* item: set.relations()[pr.name]->items())
				widget->addItem(item->shortDesc());
			return widget;
		}
		else
		{
			auto* widget = new QSpinBox(parent);
			widget->setRange(0, INT_MAX);
			return widget;
		}
	}
	else if (pr.type == Meta::Type::Int)
	{
		auto* widget = new QSpinBox(parent);
		widget->setRange(INT_MIN, INT_MAX);
		return widget;
	}
	else if (pr.type == Meta::Type::String)
	{
		return new QLineEdit(parent);
	}
	else if (pr.type == Meta::Type::Double)
	{
		auto* widget = new QDoubleSpinBox(parent);
		widget->setRange(std::numeric_limits<RMetaDouble>::min(), std::numeric_limits<RMetaDouble>::max());
		return widget;
	}
	else if (pr.type == Meta::Type::DateTime)
	{
		auto* widget = new QDateTimeEdit(parent);
		widget->setDateTime(QDateTime::currentDateTime());
		widget->setCalendarPopup(true);
		return widget;
	}
	else if (pr.type == Meta::Type::Money)
	{
		return new QDoubleSpinBox(parent);
	}
	return Q_NULLPTR;
}

}
