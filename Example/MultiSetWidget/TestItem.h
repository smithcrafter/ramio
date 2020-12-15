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

#include <Items/MetaStandardItems.h>
#include <QtCore/QDateTime>

struct NoteRecord : Ramio::MetaStandardItemData
{
	RMString title;
	RMString text;
	RMDateTime time;

	RMETA_DATA_START(Ramio::MetaStandardItemData)
	RMETA_DATA_FIELD_C(title, String,  "Заголовок")
	RMETA_DATA_FIELD_C(text, String, "Текст")
	RMETA_DATA_FIELD_C(time, DateTime, "Время")
	RMETA_DATA_END
};

GENERATE_HEADER_STANDARDCLASS(Note, NoteRecord)
GENERATE_HEADER_STANDARDSET(MetaNoteSet, Note, NoteRecord)
