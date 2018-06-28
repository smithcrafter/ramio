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

#pragma once

#include <ramio.h>
#include <QStringBuilder>

#ifdef QT_GUI_LIB
#include <QDateTime>
#include <QListWidget>
#include <QtCore/QPointer>
#endif

namespace Ramio {

class DLL_EXPORT Log
{
public:
	const QString& log(const QString& str);
	const QString& ulog(const QString& str);
	const QString& plog(const QString& str);
	const QString& dlog(const QString& str);
	const QString& clog(const QString& str);

	static Log& instance();
private:
	Log() = default;

#ifdef QT_GUI_LIB
public:
	void setLogWidget(QListWidget* widget);

	struct LogRecord
	{
		QDateTime time;
		QString msg;
	};

private:
	QList<LogRecord> userLog_;
	QPointer<QListWidget> logWidget_;
#endif
};

} // Ramio::

// Просто лог
#define LOG(text) Ramio::Log::instance().log(text)
// Лог для пользователя
#define ULOG(text) Ramio::Log::instance().ulog(text)
// Информация о события в программе
#define PLOG(text) Ramio::Log::instance().plog(text)
// Информация об отладке
#define DLOG(text) Ramio::Log::instance().dlog(text)
// Критическое сообщение
#define CLOG(text) Ramio::Log::instance().сlog(text)
