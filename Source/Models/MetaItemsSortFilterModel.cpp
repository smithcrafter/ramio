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

#include "MetaItemsSortFilterModel.h"
#include <Items/MetaItemData.h>
#include <Items/Item.h>

namespace Ramio {

MetaItemsSortFilterModel::MetaItemsSortFilterModel(QObject* parent)
	: NumericSortFilterModel(parent)
{
}

MetaItemsSortFilterModel::~MetaItemsSortFilterModel() = default;

static const QList<Ramio::Meta::Type> exceptionsLessTypes = QList<Ramio::Meta::Type>()
		<< Ramio::Meta::Type::Time << Ramio::Meta::Type::Date << Ramio::Meta::Type::DateTime
		<< Ramio::Meta::Type::Short << Ramio::Meta::Type::UShort << Ramio::Meta::Type::Int << Ramio::Meta::Type::UInt
		<< Ramio::Meta::Type::Long << Ramio::Meta::Type::ULong << Ramio::Meta::Type::Float << Ramio::Meta::Type::Double
		<< Ramio::Meta::Type::Money << Ramio::Meta::Type::Byte << Ramio::Meta::Type::PKey;

bool MetaItemsSortFilterModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
	if (Ramio::Meta::Property* pr = static_cast<Ramio::Meta::Property*>(
				sourceModel()->headerData(source_left.column(), Qt::Horizontal, Qt::UserRole).value<void*>()))
	{
		if (exceptionsLessTypes.contains(pr->type))
		{
			const auto* left = static_cast<Ramio::Item*>(source_left.data(Qt::UserRole).value<void*>());
			const auto* right = static_cast<Ramio::Item*>(source_right.data(Qt::UserRole).value<void*>());
			return Ramio::Meta::less(pr->type, left->data(), right->data(), pr->diff);
		}
	}
	return NumericSortFilterModel::lessThan(source_left, source_right);
}

} // Ramio::
