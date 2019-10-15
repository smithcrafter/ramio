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

#include "KeyValueRecord.h"
#include "Strings.h"
#include <QStringBuilder>

namespace Ramio {

KeyValueRecord::KeyValueRecord(const QString& str)
{
	if (str.isEmpty())
		return;

	QStringList list;
	qint32 pos = 0, splitLIndex = -1;
	do {
		splitLIndex = str.indexOf(QRegExp("[;]"), splitLIndex+1);
		if (splitLIndex+1 != str.length() && str[splitLIndex+1] == QChar(';'))
			splitLIndex++;
		else
		{
			qint32 size = (splitLIndex == -1) ? -1 : splitLIndex - pos;
			list.append(str.mid(pos, size));
			pos = splitLIndex + 1;
		}

	} while (splitLIndex != -1);

	for (const QString& value: list)
	{
		QString strValue = value.trimmed().replace(doubleSemicolonStr, semicolonStr);

		if (!strValue.isEmpty())
		{
			qint32 splitIndex = strValue.indexOf(QRegExp("[^:][:][^:]"));
			if (splitIndex == -1)
				keywords_.append(strValue.replace(doubleColonStr, colonStr));
			else if (splitIndex == 0)
			{
				QString v = value.trimmed().mid(1);
				if (!v.isEmpty())
					keywords_.append(v);
			}
			else
			{
				QString k = strValue.mid(0, 1+splitIndex).trimmed()
						.replace(doubleColonStr, colonStr);
				QString v = strValue.mid(1+splitIndex+1).trimmed()
						.replace(doubleColonStr, colonStr).replace(doubleSemicolonStr, semicolonStr);
				if (!k.isEmpty() && !v.isEmpty())
					values_[k] = v;
				else if (!k.isEmpty())
					keywords_.append(k);
				else if (!v.isEmpty())
					keywords_.append(v);
			}
		}
	}
}

QString KeyValueRecord::value(const QString& key, const QString& defValue) const
{
	return values_.contains(key) ? values_[key] : defValue;
}

void KeyValueRecord::setKeyValue(const QString& key, const QString& value)
{
	values_.insert(key, value);
}

void KeyValueRecord::setKeyValue(const QString& key, qint32 value)
{
	values_.insert(key, QString::number(value));
}

void KeyValueRecord::setKeyValue(const QString &key, qint64 value)
{
	values_.insert(key, QString::number(value));
}

void KeyValueRecord::addKeyWord(const QString& keyword)
{
	keywords_.append(keyword);
}

QString KeyValueRecord::createStr() const
{
	QString result;
	for (auto it = values_.constBegin(); it != values_.constEnd(); ++it)
	{
		QString key = QString(it.key()).replace(colonStr, doubleColonStr).replace(semicolonStr, doubleSemicolonStr);
		QString value = QString(it.value()).replace(colonStr, doubleColonStr).replace(semicolonStr, doubleSemicolonStr);
		result.append(key % colonStr % value % semicolonStr);
	}
	for (const QString& str: keywords_)
	{
		QString key = QString(str).replace(colonStr, doubleColonStr).replace(semicolonStr, doubleSemicolonStr);
		result.append(key % semicolonStr);
	}
	return result;
}

} // Ramio::
