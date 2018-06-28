/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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

#include "LogMessageHandler.h"
// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDateTime>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

namespace Ramio {

const QStringList typeName {"[D]", "[W]", "[C]", "[F]", "[I]"};
const QList<FILE*> typeDevice {stdout, stderr, stderr, stderr, stdout};

void log2fileMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QString time = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz");
	QString codeContext;
	if (type != QtInfoMsg)
		codeContext = QStringLiteral(" (%1:%2)").arg(context.function).arg(context.line);

	QString txt = time.append(typeName[type]).append(codeContext).append(": ").append(msg);

	QFile outFile(QCoreApplication::applicationDirPath() + "/Logs/" + QCoreApplication::applicationName() + ".log");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
	outFile.close();
	QTextStream out(typeDevice[type]);
	out << txt;
}

} // Ramio::
