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
	return QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs);
}

Log::Log() = default;

Log::~Log() = default;

void Log::log(const QString& text)
{
	std::cout << qPrintable(text) << std::endl;
}

void Log::ulog(const QString& text)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), text, 0});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace() << timeFunction_() << GRAY << " [info] " << NC << text;
}

void Log::nlog(const QString& title, const QString& text)
{
	if (noticer_)
		noticer_->addNotice(QDateTime::currentDateTime(), title, text);
	qInfo().noquote().nospace() << timeFunction_() << CYAN << " [notice] " << NC << title << ": " <<text;
}

void Log::wlog(const QString &text)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), text, 1});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace() << timeFunction_() << YELLOW << " [warning] " << NC << text;
}

void Log::plog(const QString& text, const QString& context)
{
	if (!noPlog_)
		qDebug().noquote().nospace() << timeFunction_() << BLUE << " [program] " << NC << context << text;
}

void Log::dlog(const QString& text, const QString& context)
{
	if (!noDlog_)
		qWarning().noquote().nospace() << timeFunction_() << MAGENTA << " [debug] " << NC << context << text;
}

void Log::clog(const QString& text, const QString& context)
{
	qCritical().noquote().nospace() << timeFunction_() << RED << " [critical] " << NC << context << text;
}

void Log::jlog(const QString&, const QString&, const QString&)
{
 // TODO to database
}

Log& Log::instance()
{
	static Log log;
	return log;
}

void Log::setNoticer(Noticer* noticer)
{
	noticer_ = noticer;
}

#ifdef QT_GUI_LIB

void Log::setLogWidget(QListWidget* widget)
{
	logWidget_ = widget;
	if (logWidget_)
		for (const LogRecord& record: userLog_)
			printLogRecord(record);
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
