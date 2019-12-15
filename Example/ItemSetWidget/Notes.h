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
#include <QtCore/QDateTime>

enum Importance : RMetaInt
{
	LowImportance = 0,
	MiddleImportance,
	HigthImportance
};

struct ImportanceDescription : public Ramio::Meta::TypeDescription
{
	ImportanceDescription() : Ramio::Meta::TypeDescription(true) {}
	~ImportanceDescription() override = default;

	TypeDescription* clone() const override {return new ImportanceDescription();}

	const QString& typeName(RMetaInt type) override;
	QList<RMetaInt> supportedTypes() override;
	const QStringList& supportedTypeNames() override;

};


struct NoteRecord : Ramio::MetaBaseItemData
{
	RMetaString title;
	RMetaString text;
	RMetaDateTime time;
	RMetaPKey sectionId;

	RMETA_OBJECT_START(Ramio::MetaBaseItemData)
	RMETA_OBJECT_FIELD_C(title, String,  "Заголовок")
	RMETA_OBJECT_FIELD_C(text, String, "Текст")
	RMETA_OBJECT_FIELD_C(time, DateTime, "Время")
	RMETA_OBJECT_PROPERTY(sectionId, PKey, "SectionId", "Раздел", FKey)
	RMETA_OBJECT_END

	NoteRecord() = default;
	NoteRecord(QString a, QString t, QDateTime d) : title(std::move(a)), text(std::move(t)), time(std::move(d)) {}
};

GENERATE_HEADER_CLASS(Note, NoteRecord)
GENERATE_HEADER_CLASS_METASET(MetaNoteSet, Note, NoteRecord)
