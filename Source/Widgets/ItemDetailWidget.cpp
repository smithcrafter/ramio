/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ItemDetailWidget.h"
// Ramio
#include <Gui/Global.h>
#include <Global/Text.h>
// Qt5
#include <QtCore/QDateTime>

namespace Ramio {

ItemDetailWidget::ItemDetailWidget(const Item& item, const Meta::Description& metaDescription, QWidget* parent)
	: QWidget(parent),
	  item_(item),
	  metaDescription_(metaDescription)
{
	UI_CREATE_GLAYOUT(layout);
	int index = 0;
	QLabel* label;
	layout->addWidget(label = new QLabel(BOLD(tr("Элемент ") % metaDescription_.itemName)), 0, 0, 1, 2);

	for (const Meta::Property& pr: metaDescription_.properties)
	{
		if (pr.role == Meta::FieldRole::Function)
			continue;

		layout->addWidget(label = new QLabel(pr.prettyname), ++index, 0);
		label->setWordWrap(true);

		const auto& data = static_cast<const MetaItemData&>(item_.data());

		if (pr.type == Meta::Type::PKey)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey))), index, 1);
		else if (pr.type == Meta::Type::Bool)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaBool) ? QStringLiteral("True") : QStringLiteral("False")), index, 1);
		else if (pr.type == Meta::Type::Short)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaShort))), index, 1);
		else if (pr.type == Meta::Type::UShort)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaUShort))), index, 1);
		else if (pr.type == Meta::Type::Int)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt))), index, 1);
		else if (pr.type == Meta::Type::UInt)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaUInt))), index, 1);
		else if (pr.type == Meta::Type::Long)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong))), index, 1);
		else if (pr.type == Meta::Type::ULong)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaULong))), index, 1);
		else if (pr.type == Meta::Type::Float)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaFloat))), index, 1);
		else if (pr.type == Meta::Type::Double)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble))), index, 1);
		else if (pr.type == Meta::Type::String)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaString)), index, 1);
		else if (pr.type == Meta::Type::Uuid)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid).toString()), index, 1);
		else if (pr.type == Meta::Type::Time)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime).toString(QStringLiteral(PRETTY_T_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::Date)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate).toString(QStringLiteral(PRETTY_D_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::DateTime)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime).toString(QStringLiteral(PRETTY_DT_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::Byte)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMetaByte))), index, 1);
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
