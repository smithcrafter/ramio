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

#include "UISets.h"
#include "Log/Log.h"
#include "Arg.h"
// All Qt gui classes
#include <QtWidgets>
#include <QStringBuilder>

namespace Ramio {

QString fullParentName(const QWidget* w)
{
	QString result = w->objectName();
	const QWidget* parent = w->parentWidget();
	while (parent)
	{
		result=parent->objectName().append("/").append(result);
		parent = parent->parentWidget();
	}
	return result;
}

#define FPN QString(fpn)

void UISets::saveWidget(const QWidget* w) const
{
	const QString fpn = fullParentName(w).append("/");

	if (const auto* splitter = dynamic_cast<const QSplitter*>(w))
		settings_->setValue(FPN.append("State"), splitter->saveState());
	else if  (const auto* table = dynamic_cast<const QTableView*>(w))
		settings_->setValue(FPN.append("HorizontalHeaderState"), table->horizontalHeader()->saveState());
	else if  (const auto* edit = dynamic_cast<const QLineEdit*>(w))
		settings_->setValue(FPN.append("Text"), edit->text());
	else if  (const auto* edit = dynamic_cast<const QTextEdit*>(w))
		settings_->setValue(FPN.append("Text"), edit->toPlainText());
	else if  (const auto* box = dynamic_cast<const QSpinBox*>(w))
		settings_->setValue(FPN.append("Value"), box->value());
	else if  (const auto* box = dynamic_cast<const QDoubleSpinBox*>(w))
		settings_->setValue(FPN.append("Value"), box->value());
	else if  (const auto* box = dynamic_cast<const QCheckBox*>(w))
		settings_->setValue(FPN.append("State"), box->checkState());
	else if  (const auto* box = dynamic_cast<const QComboBox*>(w))
		settings_->setValue(FPN.append("Index"), box->currentIndex());
	else if  (const auto* tabs = dynamic_cast<const QTabWidget*>(w))
		settings_->setValue(FPN.append("Index"), tabs->currentIndex());
	else if (const auto* dtedit = dynamic_cast<const QDateTimeEdit*>(w))
		settings_->setValue(FPN.append("Datetime"), dtedit->dateTime());
	else
		Q_ASSERT_X(0, "UISets", "type not support");
}

void UISets::loadWidget(QWidget* w) const
{
	const QString fpn = fullParentName(w).append("/");

	if (auto* splitter = dynamic_cast<QSplitter*>(w))
	{
		QByteArray data = settings_->value(FPN.append("State")).toByteArray();
		if (!data.isEmpty()) splitter->restoreState(data);
	}
	else if (auto* table = dynamic_cast<QTableView*>(w))
	{
		QByteArray data = settings_->value(FPN.append("HorizontalHeaderState")).toByteArray();
		if (!data.isEmpty()) table->horizontalHeader()->restoreState(data);
	}
	else if (auto* edit = dynamic_cast<QLineEdit*>(w))
	{
		QString data = settings_->value(FPN.append("Text")).toString();
		if (!data.isEmpty()) edit->setText(data);
	}
	else if (auto* edit = dynamic_cast<QTextEdit*>(w))
	{
		QString data = settings_->value(FPN.append("Text")).toString();
		if (!data.isEmpty()) edit->setText(data);
	}
	else if (auto* box = dynamic_cast<QSpinBox*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("Value")).toInt(&ok);
		if (ok) box->setValue(data);
	}
	else if (auto* box = dynamic_cast<QDoubleSpinBox*>(w))
	{
		bool ok = false;
		double data = settings_->value(FPN.append("Value")).toDouble(&ok);
		if (ok) box->setValue(data);
	}
	else if (auto* box = dynamic_cast<QCheckBox*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("State")).toInt(&ok);
		if (ok) box->setCheckState(Qt::CheckState(data));
	}
	else if (auto* box = dynamic_cast<QComboBox*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("Index")).toInt(&ok);
		if (ok && data >= 0) box->setCurrentIndex(data);
	}
	else if (auto* tabs = dynamic_cast<QTabWidget*>(w))
	{
		bool ok = false;
		int data = settings_->value(FPN.append("Index")).toInt(&ok);
		if (ok && data >= 0) tabs->setCurrentIndex(data);
	}
	else if (auto* dtedit = dynamic_cast<QDateTimeEdit*>(w))
	{
		QDateTime dt = settings_->value(FPN.append("Datetime")).toDateTime();
		dtedit->setDateTime(dt);
	}
	else
		Q_ASSERT_X(0, "UISets", "type not support");
}

void UISets::saveWidgetValue(const QWidget* widget, const QString &key, const QString &value) const
{
	const QString fpn = fullParentName(widget).append("/").append(key);
	settings_->setValue(fpn, value);
}

QString UISets::loadWidgetValue(QWidget* widget, const QString& key) const
{
	const QString fpn = fullParentName(widget).append("/").append(key);
	return settings_->value(fpn).toString();
}

void UISets::saveGeometry(const QWidget* w) const
{
	settings_->setValue(fullParentName(w).append("/Geometry"), w->saveGeometry());
}

void UISets::loadGeometry(QWidget* w) const
{
	QByteArray data = settings_->value(fullParentName(w).append("/Geometry")).toByteArray();
	if (!data.isEmpty()) w->restoreGeometry(data);
}

void UISets::sync() const
{
	const_cast<UISets*>(this)->settings_->sync();
}

QString UISets::filename(const QString& targetName) const
{
#ifdef Q_OS_ANDROID
	auto list = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
	if (!list.isEmpty())
		return list.first() % "/" % targetName % QStringLiteral(".ini");
#endif
	return appProfile() % QStringLiteral("/Config/") % targetName % QStringLiteral(".UISets.ini");
}


UISets::UISets(const QString& targetName)
{
	QString name = filename(targetName);
	settings_.reset(new QSettings(name, QSettings::IniFormat));
	settings_->sync();
	if (settings_->status() != QSettings::NoError)
		PLOG(QObject::tr("UISets error status: %1").arg(settings_->status()));
	else
		PLOG(QObject::tr("UISets init at: %1").arg(name));
}

UISets::~UISets()
{
	settings_->sync();
}

UISets& UISets::uiSets(const QString& targetName)
{
	static UISets result(targetName);
	return result;
}

const UISets& uiSets(const QString& targetName)
{
	return UISets::uiSets(targetName);
}

} // Ramio::
