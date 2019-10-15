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

#include "Log.h"
// Qt5
#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#ifdef QT_GUI_LIB
#include <QtWidgets/QListWidget>
#endif
// C++ STL
#include <iostream>

#define CUR_DT_STR QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs)

#define RED "\033[031m"
#define GREEN "\033[032m"
#define YELLOW "\033[033m"
#define BLUE "\033[034m"
#define MAGENTA "\033[035m"
#define CYAN "\033[036m"
#define GRAY "\033[037m"
#define NC "\033[0m"

namespace Ramio {

QString timeLogFormatStr()
{
	return CUR_DT_STR;
}

Log::Log() = default;

Log::~Log() = default;

const QString& Log::log(const QString& str)
{
	std::cout<<qPrintable(str)<<std::endl;
	return str;
}

const QString& Log::ulog(const QString& str)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), str, 0});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace()<<CUR_DT_STR<<GRAY<<" [info] "<<NC<<str;
	return str;
}

const QString& Log::nlog(const QString& title, const QString& text)
{
#ifdef QT_GUI_LIB
	if (noticer_)
		noticer_->notice(QDateTime::currentDateTime(), title, text);
#endif
	qInfo().noquote().nospace()<<CUR_DT_STR<<CYAN<<" [notice] "<<NC << title << ": " <<text;
	return text;
}

const QString& Log::wlog(const QString &str)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), str, 1});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace()<<CUR_DT_STR<<YELLOW<<" [warning] "<<NC<<str;
	return str;
}

const QString& Log::plog(const QString& str, const QString& context)
{
	if (noPlog_)
		return emptyString;
	qDebug().noquote().nospace()<<CUR_DT_STR<<BLUE<<" [program] "<<NC<<context<<str;
	return str;
}

const QString& Log::dlog(const QString& str, const QString& context)
{
	if (noDlog_)
		return emptyString;
	qWarning().noquote().nospace()<<CUR_DT_STR<<MAGENTA<<" [debug] "<<NC<<context<<str;
	return str;
}

const QString& Log::clog(const QString& str, const QString& context)
{
	qCritical().noquote().nospace()<<CUR_DT_STR<<RED<<" [critical] "<<NC<<context<<str;
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
			printLogRecord(record);
}

void Log::setNoticer(Noticer* noticer)
{
	noticer_ = noticer;
}

void Log::clearHistoryUWLog()
{
	userLog_.clear();
	if (logWidget_)
		logWidget_.clear();
}

void Log::printLogRecord(const LogRecord& record)
{
	if (logWidget_)
		logWidget_->addItem(record.time.toString(Qt::ISODate) % ": " % record.msg);
}

Log::LogRecord::LogRecord(QDateTime ptime, QString pmsg, int pwarning)
	: time(std::move(ptime)), msg(std::move(pmsg)), warning(pwarning)
{
}

#endif

} // Ramio::
