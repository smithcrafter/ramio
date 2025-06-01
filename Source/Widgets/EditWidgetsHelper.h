/*
 * Copyright (C) 2016-2025 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, RAM object with Input-Output instructions.
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

#include <QtGlobal>
class QWidget;

namespace Ramio {

class AbstractMetaSet;
struct Data;
namespace Meta {struct Property; struct Description;}

QWidget* createEditWidget(const Meta::Description& meta, const Meta::Property& pr, const AbstractMetaSet* set, QWidget* parent = Q_NULLPTR);

void updateEditWidgetFromData(const Data& data, const Meta::Property& pr, const AbstractMetaSet* set, QWidget* widget);
void updateDataFromEditWidget(Data& data, const Meta::Property& pr, const AbstractMetaSet* set, const QWidget* widget);


} // Ramio::
