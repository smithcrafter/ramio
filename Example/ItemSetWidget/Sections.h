/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#pragma once

#include <Items/MetaItems.h>

struct SectionRecord : Ramio::MetaItemData
{
	RMString name;

	RMETA_DATA_DECL(Ramio::MetaItemData)

	SectionRecord() = default;
	SectionRecord(QString a) : name(std::move(a)) {}
};

GENERATE_METACLASS_START(Section, SectionRecord)
	QString shortDesc() const Q_DECL_OVERRIDE;
};

GENERATE_HEADER_METASET(MetaSectionSet, Section, SectionRecord)
