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

#include "Log.h"
// Qt5
#include <QtCore/QDebug>
// C++ STL
#include <iostream>

namespace Ramio {

const QString& Log::log(const QString& str)
{
	std::cout<<qPrintable(str)<<std::endl;
	return str;
}

const QString& Log::ulog(const QString& str)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), str});
	if (logWidget_)
		logWidget_->addItem(userLog_.last().time.toString(Qt::ISODate) % ": " % str);
#endif
	qInfo().noquote().nospace()<<"[info] "<<str;
	return str;
}

const QString& Log::plog(const QString& str, const QString& context)
{
	qDebug().noquote().nospace()<<"[program] "<<context<<str;
	return str;
}

const QString& Log::dlog(const QString& str, const QString& context)
{
	qWarning().noquote().nospace()<<"[debug] "<<context<<str;
	return str;
}

const QString& Log::clog(const QString& str, const QString& context)
{
	qCritical()<<"[critical] "<<context<<str;
	return str;
}

Log& Log::instance()
{
	static Log log;
	return log;
}

#ifdef QT_GUI_LIB

void Log::setLogWidget(QListWidget* widget)
{
	logWidget_ = widget;
	if (logWidget_)
		for (const LogRecord& record: userLog_)
			logWidget_->addItem(record.time.toString(Qt::ISODate) % ": " % record.msg);
}

#endif

} // Ramio::
