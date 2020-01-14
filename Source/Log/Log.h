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

#pragma once

#include <ramio.h>
#include <QStringBuilder>
#ifdef QT_GUI_LIB
#include <QDateTime>
#include <QtCore/QPointer>
class QListWidget;
#endif

namespace Ramio {

class Noticer;
QString timeLogFormatStr();

using LogTimeFunction = QString (*)();

class RAMIO_LIB_EXPORT Log
{
public:
	void log(const QString& text);
	void ulog(const QString& text);
	void nlog(const QString& title, const QString& text);
	void wlog(const QString& text);
	void jlog(const QString& text, const QString& name = emptyString, const QString& description = emptyString);
	void plog(const QString& text, const QString& context = emptyString);
	void dlog(const QString& text, const QString& context = emptyString);
	void clog(const QString& text, const QString& context = emptyString);

	static Log& instance();
	void setPlogEnable(bool value = false) {noPlog_ = !value;}
	void setDlogEnable(bool value = false) {noDlog_ = !value;}

	LogTimeFunction timeFunction() {return timeFunction_;}
	void setTimeFunction(LogTimeFunction function) {timeFunction_ = function;}

private:
	Log();
	~Log();
	LogTimeFunction timeFunction_ = timeLogFormatStr;
	bool noPlog_ = true;
	bool noDlog_ = true;

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
	void setNoticer(Noticer* noticer);
	void clearHistoryUWLog();
	void printLogRecord(const LogRecord& record);

private:
	QList<LogRecord> userLog_;
	QPointer<Noticer> noticer_;
	QPointer<QListWidget> logWidget_;
#endif
};

#ifdef QT_GUI_LIB
class Noticer : public QObject
{
	Q_OBJECT
public:
	Noticer(QObject* parent = Q_NULLPTR) : QObject(parent) {}
signals:
	void notice(const QDateTime& datetime, const QString& title, const QString& text);
};
#endif


} // Ramio::

// Просто лог
#define LOG(text) Ramio::Log::instance().log(text)
#define LOG_T(text) Ramio::Log::instance().log(Ramio::timeLogFormatStr() % " " % text)
// Лог для пользователя
#define ULOG(text) Ramio::Log::instance().ulog(text)
// Уведомления
#define NLOG(title, text) Ramio::Log::instance().nlog(title, text)
// Лог для пользователя (варнинги)
#define WLOG(text) Ramio::Log::instance().wlog(text)
// Информация о события в программе
#define PLOG(text) Ramio::Log::instance().plog(text, QStringLiteral("<") % __func__ % QStringLiteral("> "))
// Информация об отладке
#define DLOG(text) Ramio::Log::instance().dlog(text, QStringLiteral("(") % __FILE__ % ":" %  QString::number(__LINE__) % ":" % __func__ % ") " )
#define DLOG_POINT DLOG("")
// Критическое сообщение
#define CLOG(text) Ramio::Log::instance().clog(text, QStringLiteral("(") % __FILE__ % ":" %  QString::number(__LINE__) % ":" % __func__ % ") ")
