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

#include "Exit.h"
#include <signal.h>
#include <QtCore/QCoreApplication>

namespace Ramio {

namespace Consts {
const int AppNormalExitCode = 200;
const int AppRestartExitCode = 201;
const int AppUpdateExitCode = 202;
} // Consts::

void signalHandler(int sig)
{
	int exitCode = 0;
#ifdef Q_OS_LINUX
	if (sig == SIGINT || sig == SIGTERM)
		exitCode = Consts::AppNormalExitCode;
	else if (sig == SIGUSR1)
		exitCode = Consts::AppUpdateExitCode;
#endif
	qApp->exit(exitCode);
}


ExitHelper::ExitHelper(QCoreApplication& app)
	: QObject(&app)
{
#ifdef Q_OS_LINUX
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGUSR1, signalHandler);
#endif
}

} // Ramio::
