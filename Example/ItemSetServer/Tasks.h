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

RDECL_CLASS_STRUCT(Task, TaskRecord)

struct TaskRecord : Ramio::MetaItemData
{
	RMString text;
	RMDateTime time;
	RMPKey userId = 0;
	RMString color;
	RMInt state = 0;

	TaskRecord() = default;
	TaskRecord(QString a, QDateTime b, quint64 c) : text(std::move(a)), time(std::move(b)), userId(c)  {}
	QVariant stateStr() const;
	RMETA_DATA_DECL(Ramio::MetaItemData)
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


GENERATE_HEADER_METASET_START(MetaTaskSet, Task, TaskRecord)
std::function<QVariant(const Ramio::AbstractMetaItemData&, const Ramio::Meta::Property&)> colorFunction;
};
