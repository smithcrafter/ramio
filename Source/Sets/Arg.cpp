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

#include "Arg.h"
#include <QtCore/QCoreApplication>
#include <Log/Log.h>

namespace Ramio {

void initLogFromArguments()
{
	bool logall = containsArgument("FULLLOG");
	Logger::instance().setPlogEnable(logall | containsArgument("PLOG"));
	Logger::instance().setDlogEnable(logall | containsArgument("DLOG"));
}

bool containsArgument(const QString& arg)
{
	return qApp->arguments().contains(arg);
}

QString argumentValue(const QString& arg)
{
	auto index = qApp->arguments().indexOf(arg);
	if (index > 0 && (index+1) < qApp->arguments().count())
		return qApp->arguments()[index+1];
	return QString();
}

} // Ramio::
