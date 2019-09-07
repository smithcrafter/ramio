/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#pragma once

#include <ramio.h>
#include <QtCore/QSettings>

namespace Ramio {

class DLL_EXPORT UISets
{
public:
	void saveWidget(const QWidget* widget) const;
	void loadWidget(QWidget* w) const;

	void saveGeometry(const QWidget* widget) const;
	void loadGeometry(QWidget* widget) const;

	void sync() const;

private:
	UISets(const QString& targetName);
	~UISets();
	friend const UISets& uiSets(const QString& targetName);
	static UISets& uiSets(const QString& targetName);
	QScopedPointer<QSettings> settings_;

};

DLL_EXPORT const UISets& uiSets(const QString& targetName = TARGET_NAME);

} // Ramio::

#define SAVE_GEOMETRY(w) Ramio::uiSets().saveGeometry(w)
#define LOAD_GEOMETRY(w) Ramio::uiSets().loadGeometry(w)

#define SAVE_CHECK_WIDGET(w, actions) if ((w)) \
	{if ((w)->objectName().isEmpty()) (w)->setObjectName(QStringLiteral(#w)); Ramio::uiSets().saveWidget(w); actions}
#define LOAD_CHECK_WIDGET(w, actions) if (w) \
	{if ((w)->objectName().isEmpty()) (w)->setObjectName(QStringLiteral(#w)); Ramio::uiSets().loadWidget(w); actions}

#define SAVE_WIDGET(w) SAVE_CHECK_WIDGET(w, )
#define LOAD_WIDGET(w) LOAD_CHECK_WIDGET(w, )

#define SAVE_SETTINGS(w) {if (w->objectName().isEmpty()) w->setObjectName(QStringLiteral(#w)); w->saveSettings();}
#define LOAD_SETTINGS(w) {if (w->objectName().isEmpty()) w->setObjectName(QStringLiteral(#w)); w->loadSettings();}
