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

		if (pr->type == Ramio::Meta::Type::DateTime)
		{
			const RMetaDateTime& d_left = *reinterpret_cast<const RMetaDateTime*>(reinterpret_cast<const char*>(&left->data())+pr->dif);
			const RMetaDateTime& d_right = *reinterpret_cast<const RMetaDateTime*>(reinterpret_cast<const char*>(&right->data())+pr->dif);
			return  d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::Int)
		{
			const RMetaInt& d_left = *reinterpret_cast<const RMetaInt*>(reinterpret_cast<const char*>(&left->data())+pr->dif);
			const RMetaInt& d_right = *reinterpret_cast<const RMetaInt*>(reinterpret_cast<const char*>(&right->data())+pr->dif);
			return  d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::Double || pr->type == Ramio::Meta::Type::Money)
		{
			const RMetaDouble& d_left = *reinterpret_cast<const RMetaDouble*>(reinterpret_cast<const char*>(&left->data())+pr->dif);
			const RMetaDouble& d_right = *reinterpret_cast<const RMetaDouble*>(reinterpret_cast<const char*>(&right->data())+pr->dif);
			return  d_left < d_right;
		}
		else if (pr->type == Ramio::Meta::Type::PKey)
		{
			const RMetaPKey& d_left = *reinterpret_cast<const RMetaPKey*>(reinterpret_cast<const char*>(&left->data())+pr->dif);
			const RMetaPKey& d_right = *reinterpret_cast<const RMetaPKey*>(reinterpret_cast<const char*>(&right->data())+pr->dif);
			return  d_left < d_right;
		}
	}
	return NumericSortFilterModel::lessThan(source_left, source_right);
}

} // Ramio::
