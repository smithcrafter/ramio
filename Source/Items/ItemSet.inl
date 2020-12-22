/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick development of a prototype application.
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

#include "ItemSet.h"

namespace Ramio {

template<typename ITEM, typename STRUCTDATA>
void ItemSet<ITEM, STRUCTDATA>::addItems(const QList<STRUCTDATA>& datalist)
{
    Base::startReload();
    for (const auto& data: datalist)
        addItem(data);
     Base::finishReload();
}

template<typename ITEM, typename STRUCTDATA>
void ItemSet<ITEM, STRUCTDATA>::addItems(const QList<const STRUCTDATA*>& datalist)
{
    Base::startReload();
    for (const auto data: datalist)
        addItem(*data);
    Base::finishReload();
}

template<typename ITEM, typename STRUCTDATA>
void ItemSet<ITEM, STRUCTDATA>::insertItems(const QList<ITEM*>& itemslist)
{
    Base::startReload();
    for (auto* data: itemslist)
        insertItem(data);
    Base::finishReload();
}


template<typename ITEM, typename STRUCTDATA>
void ItemSet<ITEM, STRUCTDATA>::clear()
{
    Base::startReload();
    for (auto* item: items_)
         Base::removeItem(*item);
    Base::finishReload();
}


} // Ramio::
