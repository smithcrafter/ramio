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

#pragma once

#include <ramio.h>
#include <QtCore/QtDebug>
#include <qlogging.h>

namespace Ramio {

/*
 * App to file logger
 * use: qInstallMessageHandler(log2fileMessageHandler);
 */
void RAMIO_LIB_EXPORT log2fileMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

} // Ramio::

/*
 * use: qSetMessagePattern(DEBUG_MESSAGE_PATTERN);
 */
#define DEBUG_MESSAGE_PATTERN "%{time yyyy-MM-dd h:mm:ss.zzz} [%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif} %{function}:%{line}]: %{message}"
#define DEBUG_MESSAGE_BACKTRACE "%{backtrace depth=3} %{message}"
