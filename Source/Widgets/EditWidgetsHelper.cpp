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

#include "EditWidgetsHelper.h"
#include "RecordPrtListEditWidget.h"
#include <Items/AbstractListSet.h>
#include <Items/AbstractMetaSet.h>
#include <Global/Text.h>
// Qt5
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

namespace Ramio {

QWidget* createEditWidget(const Meta::Description& meta, const Meta::Property& pr, const AbstractMetaSet* set, QWidget* parent)
{
	if (pr.role == Meta::FieldRole::Value || pr.role == Meta::FieldRole::Function)
		return Q_NULLPTR;
	else if (pr.type == Meta::Type::PKey && pr.role != Meta::FieldRole::PKey)
	{
		if (set && set->meta().relations[pr.name] && set->relations()[pr.name])
		{
			auto* widget = new QComboBox(parent);
			widget->addItem(QObject::tr("Не задан"));
			for (const Ramio::Item* item: set->relations()[pr.name]->metaItems())
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
	else if (pr.role == Meta::FieldRole::Type)
	{
		if (set && set->meta().typeDescription && set->meta().typeDescription->fixedTypeCount)
		{
			auto* widget = new QComboBox(parent);
			widget->addItems(set->meta().typeDescription->supportedTypeNames());
			return widget;
		}
		else
		{
			auto* widget = new QSpinBox(parent);
			widget->setRange(INT_MIN, INT_MAX);
			return widget;
		}
	}
	else if (pr.type == Meta::Type::Bool)
	{
		return new QCheckBox(parent);
	}
	else if (pr.type == Meta::Type::Short || pr.type == Meta::Type::Int || pr.type == Meta::Type::Long
			 || pr.type == Meta::Type::UShort || pr.type == Meta::Type::UInt || pr.type == Meta::Type::ULong
			 || pr.type == Meta::Type::Byte)
	{
		auto* widget = new QSpinBox(parent);
		widget->setRange(INT_MIN, INT_MAX);
		return widget;
	}
	else if (pr.type == Meta::Type::StdString || pr.type == Meta::Type::String)
	{
		return new QLineEdit(parent);
	}
	else if (pr.type == Meta::Type::Double || pr.type == Meta::Type::Float)
	{
		auto* widget = new QDoubleSpinBox(parent);
		if (pr.type == Meta::Type::Double)
			widget->setRange(std::numeric_limits<RMDouble>::min(), std::numeric_limits<RMDouble>::max());
		else
			widget->setRange(std::numeric_limits<RMFloat>::min(), std::numeric_limits<RMFloat>::max());
		return widget;
	}
	else if (pr.type == Meta::Type::Time)
	{
		auto* widget = new QTimeEdit(parent);
		widget->setDisplayFormat(PRETTY_T_FORMAT);
		widget->setTime(QTime::currentTime());
		widget->setCalendarPopup(true);
		return widget;
	}
	else if (pr.type == Meta::Type::Date)
	{
		auto* widget = new QDateEdit(parent);
		widget->setDisplayFormat(PRETTY_D_FORMAT);
		widget->setDate(QDate::currentDate());
		widget->setCalendarPopup(true);
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
		auto* widget = new QDoubleSpinBox(parent);
		widget->setRange(std::numeric_limits<RMFloat>::min(), std::numeric_limits<RMFloat>::max());
		return widget;
	}
	else if (pr.type == Meta::Type::RecordPrtList)
	{
		if (meta.relations[pr.name])
		{
			auto* widget = new RecordPrtListEditWidget(pr, *meta.relations[pr.name], parent);
			return widget;
		}
	}
	return Q_NULLPTR;
}

void updateEditWidgetFromData(const Data& data, const Meta::Property& pr, const AbstractMetaSet* set, QWidget* widget)
{
	if (pr.type == Meta::Type::PKey && pr.role != Meta::FieldRole::PKey)
	{
		auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
		if (set && set->meta().relations[pr.name] && set->relations()[pr.name])
		{
			if (value > 0)
			{
				int index = set->relations()[pr.name]->aSet()->items().indexOf(set->relations()[pr.name]->aSet()->itemById(value))+1;
				static_cast<QComboBox*>(widget)->setCurrentIndex(index);
			}
			else
				static_cast<QComboBox*>(widget)->setCurrentIndex(0);
		}
		else
			static_cast<QSpinBox*>(widget)->setValue(int(value));
	}
	else if (pr.role == Meta::FieldRole::Type)
	{
		auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
		if (set && set->meta().typeDescription && set->meta().typeDescription->fixedTypeCount)
			static_cast<QComboBox*>(widget)->setCurrentIndex(set->meta().typeDescription->supportedTypes().indexOf(value));
		else
			static_cast<QSpinBox*>(widget)->setValue(value);
	}
	else if (pr.type == Meta::Type::Bool)
		static_cast<QCheckBox*>(widget)->setChecked(CAST_CONST_DATAREL_TO_TYPEREL(RMBool));
	else if (pr.type == Meta::Type::Char)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMChar));
	else if (pr.type == Meta::Type::Short)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMShort));
	else if (pr.type == Meta::Type::UShort)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMUShort));
	else if (pr.type == Meta::Type::Int)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMInt));
	else if (pr.type == Meta::Type::UInt)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMUInt));
	else if (pr.type == Meta::Type::Long)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMLong));
	else if (pr.type == Meta::Type::ULong)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMULong));
	else if (pr.type == Meta::Type::Float)
		static_cast<QDoubleSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMFloat));
	else if (pr.type == Meta::Type::Double)
		static_cast<QDoubleSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMDouble));
	else if (pr.type == Meta::Type::StdString)
		static_cast<QLineEdit*>(widget)->setText(QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMStdString)));
	else if (pr.type == Meta::Type::String)
		static_cast<QLineEdit*>(widget)->setText(CAST_CONST_DATAREL_TO_TYPEREL(RMString));
	else if (pr.type == Meta::Type::Time)
		static_cast<QTimeEdit*>(widget)->setTime(CAST_CONST_DATAREL_TO_TYPEREL(RMTime));
	else if (pr.type == Meta::Type::Date)
		static_cast<QDateEdit*>(widget)->setDate(CAST_CONST_DATAREL_TO_TYPEREL(RMDate));
	else if (pr.type == Meta::Type::DateTime)
		static_cast<QDateTimeEdit*>(widget)->setDateTime(CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime));
	else if (pr.type == Meta::Type::Byte)
		static_cast<QSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMByte));
	else if (pr.type == Meta::Type::Money)
		static_cast<QDoubleSpinBox*>(widget)->setValue(CAST_CONST_DATAREL_TO_TYPEREL(RMMoney));
	else if (pr.type == Meta::Type::RecordPrtList)
	{
		auto& listptr = (*reinterpret_cast<const QList<const BaseItemData*>*>(reinterpret_cast<const std::byte*>(&data)+pr.diff));
		static_cast<RecordPrtListEditWidget*>(widget)->updateFromDataPtrList(listptr);
	}
}

void updateDataFromEditWidget(Data& data, const Meta::Property& pr, const AbstractMetaSet* set, const QWidget* widget)
{
	if (pr.type == Meta::Type::PKey && pr.role != Meta::FieldRole::PKey)
	{
		auto& value = CAST_DATAREL_TO_TYPEREL(RMPKey);
		if (set && set->meta().relations[pr.name] && set->relations()[pr.name])
		{
			int index = static_cast<const QComboBox*>(widget)->currentIndex();
			if (index > 0)
				value = set->relations()[pr.name]->metaItems()[index-1]->id();
			else
				value = 0;
		}
		else
			value = RMPKey(static_cast<const QSpinBox*>(widget)->value());
	}
	else if (pr.role == Meta::FieldRole::Type)
	{
		auto& value = CAST_DATAREL_TO_TYPEREL(RMInt);
		if (set && set->meta().typeDescription && set->meta().typeDescription->fixedTypeCount)
		{
				int index = static_cast<const QComboBox*>(widget)->currentIndex();
				if (index < set->meta().typeDescription->supportedTypes().count() && index >= 0)
					value = set->meta().typeDescription->supportedTypes()[index];
				else
					value = 0;
		}
		else
			value = static_cast<const QSpinBox*>(widget)->value();
	}
	else if (pr.type == Meta::Type::Bool)
		CAST_DATAREL_TO_TYPEREL(RMBool) = static_cast<const QCheckBox*>(widget)->isChecked();
	else if (pr.type == Meta::Type::Char)
		CAST_DATAREL_TO_TYPEREL(RMChar) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Short)
		CAST_DATAREL_TO_TYPEREL(RMShort) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::UShort)
		CAST_DATAREL_TO_TYPEREL(RMUShort) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Int)
		CAST_DATAREL_TO_TYPEREL(RMInt) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::UInt)
		CAST_DATAREL_TO_TYPEREL(RMUInt) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Long)
		CAST_DATAREL_TO_TYPEREL(RMLong) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::ULong)
		CAST_DATAREL_TO_TYPEREL(RMULong) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Float)
		CAST_DATAREL_TO_TYPEREL(RMFloat) = static_cast<const QDoubleSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Double)
		CAST_DATAREL_TO_TYPEREL(RMDouble) = static_cast<const QDoubleSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::StdString)
		CAST_DATAREL_TO_TYPEREL(RMStdString) = static_cast<const QLineEdit*>(widget)->text().toStdString();
	else if (pr.type == Meta::Type::String)
		CAST_DATAREL_TO_TYPEREL(RMString) = static_cast<const QLineEdit*>(widget)->text();
	else if (pr.type == Meta::Type::Time)
		CAST_DATAREL_TO_TYPEREL(RMTime) = static_cast<const QTimeEdit*>(widget)->time();
	else if (pr.type == Meta::Type::Date)
		CAST_DATAREL_TO_TYPEREL(RMDate) = static_cast<const QDateEdit*>(widget)->date();
	else if (pr.type == Meta::Type::DateTime)
		CAST_DATAREL_TO_TYPEREL(RMDateTime) = static_cast<const QDateTimeEdit*>(widget)->dateTime();
	else if (pr.type == Meta::Type::Byte)
		CAST_DATAREL_TO_TYPEREL(RMByte) = static_cast<const QSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::Money)
		CAST_DATAREL_TO_TYPEREL(RMMoney) = static_cast<const QDoubleSpinBox*>(widget)->value();
	else if (pr.type == Meta::Type::RecordPrtList)
	{
		auto& listptr = (*reinterpret_cast<QList<BaseItemData*>*>(reinterpret_cast<std::byte*>(&data)+pr.diff));
		listptr = const_cast<RecordPrtListEditWidget*>(static_cast<const RecordPrtListEditWidget*>(widget))->takeRecords();
	}
}

} // Ramio::
