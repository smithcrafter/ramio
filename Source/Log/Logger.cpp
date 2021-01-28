/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "Logger.h"
#include "Noticer.h"
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

Logger::Logger() = default;

Logger::~Logger() = default;

void Logger::log(const QString& text)
{
	std::cout << qPrintable(text) << std::endl;
}

void Logger::ulog(const QString& text)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), text, 0});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace() << timeFunction_() << GRAY << " [info] " << NC << text;
}

void Logger::nlog(const QString& title, const QString& text, int code)
{
	if (noticer_)
		noticer_->addNotice(QDateTime::currentDateTime(), title, text, code);
	qInfo().noquote().nospace() << timeFunction_() << CYAN << " [notice] " << NC << title << ": " <<text;
}

void Logger::jlog(int type, const QString& title, const QString& text)
{
	if (jlogger_)
		jlogger_->addNotice(QDateTime::currentDateTime(), title, text, type);
	qInfo().noquote().nospace() << timeFunction_() << GREEN << " [journal] " << NC << title << ": " <<text;
}

void Logger::wlog(const QString &text)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), text, 1});
	printLogRecord(userLog_.last());
#endif
	qInfo().noquote().nospace() << timeFunction_() << YELLOW << " [warning] " << NC << text;
}

void Logger::elog(const QString& text)
{
#ifdef QT_GUI_LIB
	userLog_.append(LogRecord{QDateTime::currentDateTime(), text, 2});
	printLogRecord(userLog_.last());
#endif
	qCritical().noquote().nospace() << timeFunction_() << RED << " [error] " << NC <<text;
}

void Logger::mlog(const QString& modulename, const QString &text)
{
	qInfo().noquote().nospace() << timeFunction_() << CYAN << " ["<<modulename<<"] " << NC <<text;
}

void Logger::plog(const QString& text, const QString& context)
{
	if (!noPlog_)
		qDebug().noquote().nospace() << timeFunction_() << BLUE << " [program] " << NC << context << text;
}

void Logger::dlog(const QString& text, const QString& context)
{
	if (!noDlog_)
		qWarning().noquote().nospace() << timeFunction_() << MAGENTA << " [debug] " << NC << context << text;
}

void Logger::clog(const QString& text, const QString& context)
{
	qCritical().noquote().nospace() << timeFunction_() << RED << " [critical] " << NC << context << text;
}

Logger& Logger::instance()
{
	static Logger log;
	return log;
}

void Logger::setNoticer(Noticer* noticer)
{
	noticer_ = noticer;
}

void Logger::setJLogger(Noticer* logger)
{
	jlogger_ = logger;
}

#ifdef QT_GUI_LIB

void Logger::setLogWidget(QListWidget* widget)
{
	logWidget_ = widget;
	if (logWidget_)
		for (const LogRecord& record: userLog_)
			printLogRecord(record);
}

void Logger::clearHistoryUWLog()
{
	userLog_.clear();
	if (logWidget_)
		logWidget_.clear();
}

void Logger::printLogRecord(const LogRecord& record)
{
	if (logWidget_)
		logWidget_->addItem(record.time.toString(Qt::ISODate) % ": " % record.msg);
}

Logger::LogRecord::LogRecord(QDateTime ptime, QString pmsg, int pwarning)
	: time(std::move(ptime)), msg(std::move(pmsg)), warning(pwarning)
{
}

#endif

} // Ramio::
