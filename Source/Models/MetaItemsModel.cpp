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

#include "MetaItemsModel.h"
#include <QColor>

namespace Ramio {

static const QVector<int> baseChangingRoles = QVector<int>() <<Qt::DisplayRole;

MetaItemsModel::MetaItemsModel(const AbstractMetaSet& set, QObject* parent)
	: MetaItemsModel(*set.aSet(), set.meta(), parent)
{
}

MetaItemsModel::MetaItemsModel(const AbstractSet& set, const Meta::Description& metaDescription, QObject* parent)
	: QAbstractItemModel(parent),
	  set_(set),
	  metaDescription_(metaDescription)
{
	this->setColumns();
	connect(&set, &AbstractSet::adding, this, &MetaItemsModel::onItemAdding);
	connect(&set, &AbstractSet::added, this, &MetaItemsModel::onItemAdded);
	connect(&set, &AbstractSet::deleting, this, &MetaItemsModel::onItemRemoving);
	connect(&set, &AbstractSet::deleted, this, &MetaItemsModel::onItemRemoved);
	connect(&set, &AbstractSet::changed, this, &MetaItemsModel::onItemChanged);
	connect(&set, &AbstractSet::reloading, this, &MetaItemsModel::onItemsReloading);
	connect(&set, &AbstractSet::reloaded, this, &MetaItemsModel::onItemsReloaded);
}

MetaItemsModel::~MetaItemsModel() = default;

void MetaItemsModel::setColumns(const QList<quint8>& columns)
{
	columns_.clear();
	if (columns.isEmpty())
		for (quint8 i = 0; i < metaDescription_.properties.count(); i++)
			columns_.append(i);
	else
		columns_ = columns;
	this->resetModel();
}

QModelIndex MetaItemsModel::parent(const QModelIndex&) const
{
	return QModelIndex();
}

QModelIndex MetaItemsModel::index(int row, int column, const QModelIndex& parent) const
{
	if (row >= 0 && row < set_.count() && parent == QModelIndex())
		return createIndex(row, column, const_cast<void*>(static_cast<const void*>(set_.items().at(row))));
	return QModelIndex();
}

int MetaItemsModel::rowCount(const QModelIndex& parent) const
{
	return parent == QModelIndex() ? set_.count() :  0;
}

int MetaItemsModel::columnCount(const QModelIndex& parent) const
{
	if (parent == QModelIndex())
		return columns_.count();
	return 0;
}

QVariant MetaItemsModel::data(const QModelIndex& index, int role) const
{
	const auto* item = static_cast<Item*>(index.internalPointer());
	if (!item || !index.isValid()) return QVariant();

	if (role == Qt::DisplayRole)
	{
		const Meta::Property& pr = metaDescription_.properties[columns_[index.column()]];
		auto& data = static_cast<const MetaItemData&>(item->data());

		if (pr.relationtype == Meta::FieldType::Function)
		{
			// Experemtnal
			typedef QVariant (MetaItemData::*dataFunction)(const MetaItemData&) const;
			dataFunction memfunc_ptr;
			const void* prt = reinterpret_cast<const void*>(pr.dif);
			*((ptrdiff_t*)(&memfunc_ptr)) = *(ptrdiff_t*)&prt;
			return (data.*memfunc_ptr)(data);

		}
		else if (pr.relationtype == Meta::FieldType::Type && metaDescription_.typeDescription)
		{
			return metaDescription_.typeDescription->typeName(CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt));
		}
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMetaPKey);
			if (pr.relationtype == Meta::FieldType::FKey && set_.mSet())
				if (const Ramio::AbstractMetaSet* rset = set_.mSet()->relations()[pr.name])
				{
					if (!value)
						return QVariant();
					else if (const Item* ritem = rset->aSet()->itemById(value))
						return ritem->shortDesc();
					else
						return QStringLiteral("id=%1").arg(value);
				}
			return value;
		}
		else if (pr.type == Meta::Type::Int)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaInt);
		else if (pr.type == Meta::Type::Long)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaLong);
		else if (pr.type == Meta::Type::String)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaString);
		else if (pr.type == Meta::Type::Double)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaDouble);
		else if (pr.type == Meta::Type::Time)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaTime);
		else if (pr.type == Meta::Type::Date)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaDate);
		else if (pr.type == Meta::Type::DateTime)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaDateTime);
		else if (pr.type == Meta::Type::Money)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaMoney);
		else if (pr.type == Meta::Type::Uuid)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMetaUuid);
	}
	else if (role == Qt::BackgroundColorRole)
	{
		if (metaDescription_.functions.contains("BackgroundColorRole"))
		{
			auto& data = static_cast<const MetaItemData&>(item->data());
			return QColor(metaDescription_.functions["BackgroundColorRole"]->operator()(data));
		}
	}
	else if (role == Qt::UserRole)
		return QVariant::fromValue<void*>(const_cast<Item*>(item));

	return QVariant();
}

QVariant MetaItemsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal && section < columns_.count())
			return metaDescription_.properties[columns_[section]].prettyname;
		return section;
	}
	else if (role == Qt::UserRole)
	{
		if (orientation == Qt::Horizontal && section < columns_.count())
			return QVariant::fromValue<void*>(const_cast<Meta::Property*>(&metaDescription_.properties[columns_[section]]));
	}
	return QVariant();
}

bool MetaItemsModel::setData(const QModelIndex& /*index*/, const QVariant& /*value*/, int /*role*/)
{
	return false;
}

Qt::ItemFlags MetaItemsModel::flags(const QModelIndex& /*index*/) const
{
	if (reloading_)
		return Qt::ItemFlags();
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void MetaItemsModel::onItemAdding(const Item& /*item*/)
{
	if (reloading_) return;
	int row = set_.items().count();
	beginInsertRows(QModelIndex(), row, row);
}

void MetaItemsModel::onItemAdded(const Item& /*item*/)
{
	if (reloading_) return;
	endInsertRows();
}

void MetaItemsModel::onItemsAdding(int count)
{
	if (reloading_) return;
	int row = set_.items().count();
	beginInsertRows(QModelIndex(), row, row + count - 1);
}

void MetaItemsModel::onItemsAdded()
{
	if (reloading_) return;
	endInsertRows();
}

void MetaItemsModel::onItemRemoving(const Item& item)
{
	if (reloading_) return;
	int row = set_.items().indexOf(&item);
	beginRemoveRows(QModelIndex(), row, row);
}

void MetaItemsModel::onItemRemoved(const Item& /*item*/)
{
	if (reloading_) return;
	endRemoveRows();
}

void MetaItemsModel::onItemChanged(const Item& item)
{
	if (reloading_) return;
	int row = set_.items().indexOf(&item);
	if (row < 0) return;
	const QModelIndex topLeft = this->createIndex(row, 0, const_cast<void*>(static_cast<const void*>(&item)));
	emit dataChanged(topLeft, this->createIndex(row,  columnCount()-1,const_cast<void*>(static_cast<const void*>(&item))), baseChangingRoles);
}

void MetaItemsModel::onItemsReloading()
{
	reloading_ = true;
	QAbstractItemModel::beginResetModel();
}

void MetaItemsModel::onItemsReloaded()
{
	reloading_ = false;
	QAbstractItemModel::endResetModel();
}

} // Ramio::
