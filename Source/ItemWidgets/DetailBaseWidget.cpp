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

#include "DetailBaseWidget.h"
// Ramio
#include <Ui/Global.h>
#include <Global/Text.h>

namespace Ramio {

DetailBaseWidget::DetailBaseWidget(const Item& item, const Meta::Description& metaDescription, const void* container,
								   QWidget* parent)
	: QWidget(parent),
	  item_(item),
	  metaDescription_(metaDescription),
	  container_(container)
{
	UI_CREATE_GLAUOUT(layout);
	int index = 0;
	QLabel* label;
	layout->addWidget(label = new QLabel(BOLD(tr("Элемент ") % metaDescription.itemName)), 0, 0, 1, 2);

	for (const Meta::Property& pr: metaDescription.properties)
	{
		layout->addWidget(label = new QLabel(pr.prettyname), ++index, 0);
		label->setWordWrap(true);

		const auto& data = static_cast<const MetaItemData&>(item.data());

		if (pr.type == Meta::Type::PKey)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey))), index, 1);
		else if (pr.type == Meta::Type::Int)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt))), index, 1);
		else if (pr.type == Meta::Type::Long)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong))), index, 1);
		else if (pr.type == Meta::Type::Uuid)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
			layout->addWidget(label = new QLabel(value.toString()), index, 1);
		}
		else if (pr.type == Meta::Type::String)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaString)), index, 1);
		else if (pr.type == Meta::Type::Double)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble))), index, 1);
		else if (pr.type == Meta::Type::Time)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
			layout->addWidget(label = new QLabel(value.toString(QStringLiteral(PRETTY_T_FORMAT))), index, 1);
		}
		else if (pr.type == Meta::Type::DateTime)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
			layout->addWidget(label = new QLabel(value.toString(QStringLiteral(PRETTY_DT_FORMAT))), index, 1);
		}
		else if (pr.type == Meta::Type::Money)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney))), index, 1);
		if (label->text().contains(QLatin1String(" ")))
			label->setWordWrap(true);
		else if (label->text().length() > 35)
			label->setText(label->text().mid(0, 32).append("..."));
	}
	layout->addWidget(new QWidget, ++index, 0, 1, 2);
	layout->setRowStretch(index, 1);
}

} // Ramio::
