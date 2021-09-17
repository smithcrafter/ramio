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

#include "Notes.h"

static const QStringList ImportanceDescriptionNames { "Low", "Middle", "Higth"};
static const QList<RMType> ImportanceDescriptionTypes = {LowImportance, MiddleImportance, HigthImportance};

const QString& ImportanceDescription::typeName(RMType type) const
{
	if (type >= 0 && type <= ImportanceDescriptionNames.count())
		return ImportanceDescriptionNames[type];
	return Ramio::Meta::TypeDescription::typeName(type);
}

const QList<RMType>& ImportanceDescription::supportedTypes() const
{
	return ImportanceDescriptionTypes;
}

const QStringList& ImportanceDescription::supportedTypeNames() const
{
	return ImportanceDescriptionNames;
}

RGEN_SOURCE_STANDARDCLASS(Note)

MetaNoteSet::MetaNoteSet(QObject* parent)
	: Base(QStringLiteral("Notebook"), QStringLiteral("Note"),
		   std::shared_ptr<Ramio::Meta::TypeDescription>(new ImportanceDescription), parent)
{
}

MetaNoteSet::~MetaNoteSet()
{
}
