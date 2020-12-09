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

		const auto& data = static_cast<const Ramio::Data&>(item_.data());

		if (pr.type == Meta::Type::PKey)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMPKey))), index, 1);
		else if (pr.type == Meta::Type::Bool)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMBool) ? QStringLiteral("True") : QStringLiteral("False")), index, 1);
		else if (pr.type == Meta::Type::Char)
			layout->addWidget(label = new QLabel(QString(CAST_CONST_DATAREL_TO_TYPEREL(RMChar))), index, 1);
		else if (pr.type == Meta::Type::Short)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMShort))), index, 1);
		else if (pr.type == Meta::Type::UShort)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMUShort))), index, 1);
		else if (pr.type == Meta::Type::Int)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMInt))), index, 1);
		else if (pr.type == Meta::Type::UInt)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMUInt))), index, 1);
		else if (pr.type == Meta::Type::Long)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMLong))), index, 1);
		else if (pr.type == Meta::Type::ULong)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMULong))), index, 1);
		else if (pr.type == Meta::Type::Float)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMFloat))), index, 1);
		else if (pr.type == Meta::Type::Double)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMDouble))), index, 1);
		else if (pr.type == Meta::Type::StdString)
			layout->addWidget(label = new QLabel(QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMStdString))), index, 1);
		else if (pr.type == Meta::Type::String)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMString)), index, 1);
		else if (pr.type == Meta::Type::Uuid)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMUuid).toString()), index, 1);
		else if (pr.type == Meta::Type::Time)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMTime).toString(QStringLiteral(PRETTY_T_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::Date)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMDate).toString(QStringLiteral(PRETTY_D_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::DateTime)
			layout->addWidget(label = new QLabel(CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime).toString(QStringLiteral(PRETTY_DT_FORMAT))), index, 1);
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			auto str =  QString("[%1] %2%3").arg(value.size()).arg(QString(value.mid(32).toHex())).arg(value.size() > 32 ? "..." : "");
			layout->addWidget(label = new QLabel(str), index, 1);
		}
		else if (pr.type == Meta::Type::Byte)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMByte))), index, 1);
		else if (pr.type == Meta::Type::Money)
			layout->addWidget(label = new QLabel(QString::number(CAST_CONST_DATAREL_TO_TYPEREL(RMMoney))), index, 1);

		if (label->text().contains(QLatin1String(" ")))
			label->setWordWrap(true);
		else if (label->text().length() > 35)
			label->setText(label->text().mid(0, 32).append("..."));
	}
	layout->addWidget(new QWidget, ++index, 0, 1, 2);
	layout->setRowStretch(index, 1);
}

} // Ramio::
