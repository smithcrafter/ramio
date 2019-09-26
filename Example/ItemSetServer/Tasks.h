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
#include <QtCore/QDateTime>

struct TaskRecord : Ramio::MetaItemData
{
	RMetaString text;
	RMetaDateTime time;
	RMetaPKey userId = 0;
	RMetaInt state = 0;
	RMetaString color;

	QVariant stateStr(const TaskRecord& data) const;

	RMETA_OBJECT_START(MetaItemData)
	RMETA_OBJECT_PROPERTY(text, String, "Text", "Текст", Field)
	RMETA_OBJECT_PROPERTY(time, DateTime, "Time", "Время", Field)
	RMETA_OBJECT_PROPERTY(userId, PKey, "UserId", "Пользователь", FKey)
	RMETA_OBJECT_PROPERTY(state, Int, "State", "Состояние", Field)
	RMETA_OBJECT_PROPERTY(color, String, "Color", "Цвет", Field)
	RMETA_OBJECT_FUNCTION(TaskRecord, stateStr, String, "StateStr", "Состояние", Function)
	RMETA_OBJECT_END

	TaskRecord() = default;
	TaskRecord(QString a, QDateTime b, quint64 c) : text(std::move(a)), time(std::move(b)), userId(c)  {}
};

class Task : public Ramio::StructItem<TaskRecord>
{
	using Base = Ramio::StructItem<TaskRecord>;
public:
	Task(Ramio::ItemObserver* watcher = Q_NULLPTR);
	Task(const TaskRecord& data, Ramio::ItemObserver* watcher = Q_NULLPTR);
	Task(TaskRecord&& data, Ramio::ItemObserver* watcher = Q_NULLPTR);
	~Task() Q_DECL_OVERRIDE;

	bool isFinished() const  {return data().state%2;}
	bool isArhived() const {return data().state/2%2;}
	void changeFinished() {data().state ^= 1;}
	void setArhived() {data().state |= 2;}
};


GENERATE_HEADER_CLASS_METASET_START(MetaTaskSet, Task, TaskRecord)
std::function<QString(const Ramio::BaseMetaItemData&)> colorFunction;
};
