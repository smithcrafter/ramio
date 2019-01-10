/*
 * Copyright (C) 2016-2018 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
 *
 * This file is part of the Ramio, a Qt-based casual C++ classes for quick application writing.
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
#include <Items/MetaDescription.h>
#include <Items/Item.h>

namespace Ramio {

MetaItemsSortFilterModel::MetaItemsSortFilterModel(QObject* parent)
	: NumericSortFilterModel(parent)
{
}

bool MetaItemsSortFilterModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
	if (Ramio::Meta::Property* pr = static_cast<Ramio::Meta::Property*>(sourceModel()->headerData(source_left.column(), Qt::Horizontal, Qt::UserRole).value<void*>()))
	{
		const auto* left = static_cast<Ramio::Item*>(source_left.data(Qt::UserRole).value<void*>());
		const auto* right = static_cast<Ramio::Item*>(source_right.data(Qt::UserRole).value<void*>());

		if (pr->type == Ramio::Meta::Type::Time)
		{
			const auto& d_left = left->data().field<RMetaTime>(pr->dif);
			const auto& d_right = right->data().field<RMetaTime>(pr->dif);
			return d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::Date)
		{
			const auto& d_left = left->data().field<RMetaDate>(pr->dif);
			const auto& d_right = right->data().field<RMetaDate>(pr->dif);
			return d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::DateTime)
			return Ramio::less(pr->type, left->data(), right->data(), pr->dif);
		else if (pr->type == Ramio::Meta::Type::Int)
		{
			const auto& d_left = left->data().field<RMetaInt>(pr->dif);
			const auto& d_right = right->data().field<RMetaInt>(pr->dif);
			return  d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::Long)
		{
			const auto& d_left = left->data().field<RMetaLong>(pr->dif);
			const auto& d_right = right->data().field<RMetaLong>(pr->dif);
			return d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::Double || pr->type == Ramio::Meta::Type::Money)
		{
			const auto& d_left = left->data().field<RMetaDouble>(pr->dif);
			const auto& d_right = right->data().field<RMetaDouble>(pr->dif);
			return d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::PKey)
		{
			const auto& d_left = left->data().field<RMetaPKey>(pr->dif);
			const auto& d_right = right->data().field<RMetaPKey>(pr->dif);
			return d_left < d_right;
		}
	}
	return NumericSortFilterModel::lessThan(source_left, source_right);
}

} // Ramio::
