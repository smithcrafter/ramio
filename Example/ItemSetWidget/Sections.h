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

#pragma once

#include <Items/MetaItems.h>

struct SectionRecord : Ramio::MetaItemData
{
	RMetaString name;

	RMETA_OBJECT_START(MetaItemData)
	RMETA_OBJECT_FIELD(name, String, "Name", "Наименование", Field)
	RMETA_OBJECT_END

	SectionRecord() = default;
	SectionRecord(QString a) : name(std::move(a)) {}
};

class Section : public Ramio::StructItem<SectionRecord>
{
	using Base = Ramio::StructItem<SectionRecord>;
public:
	Section(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {}
	Section(const SectionRecord& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {}
	Section(SectionRecord&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<SectionRecord>(data), watcher) {}
	~Section() Q_DECL_OVERRIDE  { this->beforeDeleted(); }

	QString shortDesc() const Q_DECL_OVERRIDE;
};

GENERATE_HEADER_CLASS_METASET(MetaSectionSet, Section, SectionRecord)
