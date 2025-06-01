/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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
#include <QtCore/QPointer>
#ifdef QT_GUI_LIB
#include <QDateTime>
class QListWidget;
#endif

#define RC_BOLD "\033[1m"

#define RC_RED "\033[031m"
#define RC_GREEN "\033[032m"
#define RC_YELLOW "\033[033m"
#define RC_BLUE "\033[034m"
#define RC_MAGENTA "\033[035m"
#define RC_CYAN "\033[036m"
#define RC_GRAY "\033[037m"
#define RC_NC "\033[0m"

#define RC_TERM_GRAY(text) (RC_GRAY % QString("> " % text.trimmed().replace("\n", "\n> ")) % RC_NC)

namespace Ramio {

class Noticer;
QString timeLogFormatStr();

using LogTimeFunction = QString (*)();

QString prepareTextToConsole(const QString& text);

class RAMIO_LIB_EXPORT Logger
{
public:
	void log(const QString& text);
	void ulog(const QString& text);
	void wlog(const QString& text);
	void elog(const QString& text);
	void emlog(const QString& modulename, const QString& text);
	void mlog(const QString& modulename, const QString& text);
	void nlog(const QString& title, const QString& text, int code = 0);
	void jlog(int type, const QString& title, const QString& text = emptyString);
	void plog(const QString& text, const QString& context = emptyString);
	void dlog(const QString& text, const QString& context = emptyString);
	void dwlog(const QString& text, const QString& context = emptyString);
	void clog(const QString& text, const QString& context = emptyString);

	static Logger& instance();
	void setPlogEnable(bool value = false) {noPlog_ = !value;}
	void setDlogEnable(bool value = false) {noDlog_ = !value;}

	LogTimeFunction timeFunction() {return timeFunction_;}
	void setTimeFunction(LogTimeFunction function) {timeFunction_ = function;}

	void setNoticer(Noticer* noticer);
	void setJLogger(Noticer* logger);

private:
	Logger();
	~Logger();
	LogTimeFunction timeFunction_ = timeLogFormatStr;
	bool noPlog_ = true;
	bool noDlog_ = true;
	QPointer<Noticer> noticer_;
	QPointer<Noticer> jlogger_;

#ifdef QT_GUI_LIB
	struct LogRecord
	{
		QDateTime time;
		QString msg;
		int warning = 1;
		LogRecord(QDateTime time, QString msg, int warning);
	};
public:
	void setLogWidget(QListWidget* widget);
	void clearHistoryUWLog();
	void printLogRecord(const LogRecord& record);

private:
	QList<LogRecord> userLog_;
	QPointer<QListWidget> logWidget_;
#endif
};

} // Ramio::
