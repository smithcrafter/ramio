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

#include "Tasks.h"
#include <QtCore/QVariant>

QVariant TaskRecord::stateStr(const TaskRecord &data) const
{
	if (data.state/2%2)
		return "Архивиная";
	if (data.state%2)
		return "Завершённая";
	return "Активная";
}

GENERATE_SOURCE_CLASS(Task, TaskRecord)

MetaTaskSet::MetaTaskSet(QObject* parent)
		: Base(QStringLiteral("Tasks"), QStringLiteral("Task"), std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR),parent)
{
	colorFunction = [](const Ramio::BaseMetaItemData& data) -> QString {return static_cast<const TaskRecord&>(data).color;};
	this->meta_.functions["BackgroundColorRole"] = &colorFunction;
}

MetaTaskSet::~MetaTaskSet() = default;
