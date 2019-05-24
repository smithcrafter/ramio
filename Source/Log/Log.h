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
#include <QStringBuilder>
#ifdef QT_GUI_LIB
#include <QDateTime>
#include <QtCore/QPointer>
class QListWidget;
#endif

namespace Ramio {

class Noticer;
QString timeLogFormatStr();

class DLL_EXPORT Log
{
public:
	const QString& log(const QString& str);
	const QString& ulog(const QString& str);
	const QString& nlog(const QString& title, const QString& text);
	const QString& wlog(const QString& str);
	const QString& plog(const QString& str, const QString& context = emptyString);
	const QString& dlog(const QString& str, const QString& context = emptyString);
	const QString& clog(const QString& str, const QString& context = emptyString);

	static Log& instance();
	void setPlogEnable(bool value = false) {noPlog_ = !value;}
	void setDlogEnable(bool value = false) {noDlog_ = !value;}

private:
	Log();
	~Log();
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
