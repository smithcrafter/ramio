/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "ItemSetClient.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTimer>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ItemSetClient client;
	qsrand(uint(QDateTime::currentDateTime().time().msec()));
	client.showLoginForm();
	QTimer::singleShot(1000, &client, &ItemSetClient::autoLogin);
	return a.exec();
}
