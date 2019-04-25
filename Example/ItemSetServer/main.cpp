/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio Examples, a Qt-based casual C++ classes for quick application writing.
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

#include "ItemSetServer.h"
#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include <Log/Log.h>
#include <Sets/Config.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ItemSetServer server;
	if (!server.openDatabase())
	{
		CLOG(QObject::tr("База данных не открыта"));
		ULOG(QObject::tr("Проверьте настройки в файле %1.\nПример:\n"
						 "[Database]\n"
						 "DatabaseName=DB\n"
						 "UserName=DBO\n"
						 "Password=pass1234\n"
						 "Host=127.0.0.1\n"
						 "Port=5432").arg(Ramio::config().filename()));
		return -1;
	}
	if (!server.startListening())
	{
		CLOG(QObject::tr("Сервер не открыт"));
		return -2;
	}

	MainWidget widget(server);
	widget.show();

	return a.exec();
}
