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

#include "NumericSortFilterModel.h"

namespace Ramio {

class RAMIO_LIB_EXPORT MetaItemsSortFilterModel : public NumericSortFilterModel
{
public:
	MetaItemsSortFilterModel(QObject* parent = Q_NULLPTR);
	~MetaItemsSortFilterModel() Q_DECL_OVERRIDE;

private:
	virtual bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const Q_DECL_OVERRIDE;
};

} // Ramio::
