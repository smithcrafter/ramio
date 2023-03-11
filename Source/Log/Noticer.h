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

#pragma once

#include <ramio.h>
#include <QtCore/QObject>

namespace Ramio {

class Noticer : public QObject
{
	Q_OBJECT
public:
	Noticer(QObject* parent = Q_NULLPTR) : QObject(parent) {}

	virtual void addNotice(const QDateTime& datetime, const QString& title, const QString& text, int code = 0) {
		emit notice(datetime, title, text, code); }

signals:
	void notice(const QDateTime& datetime, const QString& title, const QString& text, int code);
};

} // Ramio::
