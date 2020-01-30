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

#include "Tasks.h"
#include <QtCore/QVariant>
#include <QtGui/QColor>

RMETA_OBJECT_IMPL(TaskRecord)
RMETA_OBJECT_PROPERTY(text, String, "Text", "Текст", Field)
RMETA_OBJECT_PROPERTY(time, DateTime, "Time", "Время", Field)
RMETA_OBJECT_PROPERTY(userId, PKey, "UserId", "Пользователь", FKey)
RMETA_OBJECT_PROPERTY(state, Int, "State", "Состояние", Field)
RMETA_OBJECT_PROPERTY(color, String, "Color", "Цвет", Field)
RMETA_OBJECT_FUNCTION(TaskRecord, stateStr, String, "StateStr", "Состояние", Function)
RMETA_OBJECT_END

QVariant TaskRecord::stateStr() const
{
	if (state/2%2)
		return state%2 ? "Завершённая" : "Архивиная";
	if (state%2)
		return "Выполненная";
	return "Активная";
}

GENERATE_SOURCE_METACLASS(Task, TaskRecord)

MetaTaskSet::MetaTaskSet(QObject* parent)
		: Base(QStringLiteral("Tasks"), QStringLiteral("Task"), parent)
{
	colorFunction = [](const Ramio::AbstractMetaItemData& data, const Ramio::Meta::Property&) -> QVariant {
		return QColor(static_cast<const TaskRecord&>(data).color);};
	this->meta_.functions[Ramio::Meta::FunctionRoles::BackgroundColorRole] = &colorFunction;
}

MetaTaskSet::~MetaTaskSet() = default;
