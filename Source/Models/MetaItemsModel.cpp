/*
 * Copyright (C) 2016-2021 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#include "MetaItemsModel.h"
#include <QtGui/QColor>

namespace Ramio {

static const QVector<int> baseChangingRoles = QVector<int>() <<Qt::DisplayRole;

MetaItemsModel::MetaItemsModel(const AbstractMetaSet& set, QObject* parent)
	: MetaItemsModel(*set.aSet(), set.meta(), parent)
{
}

MetaItemsModel::MetaItemsModel(const AbstractListSet& set, const Meta::Description& metaDescription, QObject* parent)
	: QAbstractItemModel(parent),
	  set_(set),
	  metaDescription_(metaDescription)
{
	this->setColumnIndexes();
	connect(&set, &AbstractListSet::adding, this, &MetaItemsModel::onItemAdding);
	connect(&set, &AbstractListSet::added, this, &MetaItemsModel::onItemAdded);
	connect(&set, &AbstractListSet::deleting, this, &MetaItemsModel::onItemRemoving);
	connect(&set, &AbstractListSet::deleted, this, &MetaItemsModel::onItemRemoved);
	connect(&set, &AbstractListSet::changed, this, &MetaItemsModel::onItemChanged);
	connect(&set, &AbstractListSet::reloading, this, &MetaItemsModel::onItemsReloading);
	connect(&set, &AbstractListSet::reloaded, this, &MetaItemsModel::onItemsReloaded);
}

MetaItemsModel::~MetaItemsModel() = default;

void MetaItemsModel::setColumnIndexes(const QList<quint8>& columns)
{
	columns_.clear();
	if (columns.isEmpty())
		for (quint8 i = 0; i < metaDescription_.properties.count(); i++)
			columns_.append(i);
	else for (quint8 col: columns)
		if (col < metaDescription_.properties.count())
			columns_.append(col);
	this->resetModel();
}

QModelIndex MetaItemsModel::index(int row, int column, const QModelIndex& parent) const
{
	if (row >= 0 && row < set_.count() && parent == QModelIndex())
		return createIndex(row, column, const_cast<void*>(static_cast<const void*>(set_.items().at(row))));
	return QModelIndex();
}

QVariant MetaItemsModel::data(const QModelIndex& index, int role) const
{
	const auto* item = static_cast<Item*>(index.internalPointer());
	if (!item || !index.isValid())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		const Meta::Property& pr = metaDescription_.properties[columns_[index.column()]];
		auto& data = item->data();

		if (pr.role == Meta::FieldRole::Function)
			return static_cast<const MetaItemData&>(data).call(pr.diff);
		else if (pr.role == Meta::FieldRole::Type && metaDescription_.typeDescription)
			return metaDescription_.typeDescription->typeName(CAST_CONST_DATAREL_TO_TYPEREL(RMShort));
		else if (pr.type == Meta::Type::PKey)
		{
			const auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMPKey);
			if (pr.role == Meta::FieldRole::FKey && set_.mSet())
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
		else if (pr.type == Meta::Type::Type)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMType);
		else if (pr.type == Meta::Type::State)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMState);
		else if (pr.type == Meta::Type::Flags)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMFlags);
		else if (pr.type == Meta::Type::Bool)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMBool) ? "True" : "False";
		else if (pr.type == Meta::Type::Short)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMShort);
		else if (pr.type == Meta::Type::UShort)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMUShort);
		else if (pr.type == Meta::Type::Int)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMInt);
		else if (pr.type == Meta::Type::UInt)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMUInt);
		else if (pr.type == Meta::Type::Long)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMLong);
		else if (pr.type == Meta::Type::ULong)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMULong);
		else if (pr.type == Meta::Type::Float)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMFloat);
		else if (pr.type == Meta::Type::Double)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMDouble);
		else if (pr.type == Meta::Type::StdString)
			return QString::fromStdString(CAST_CONST_DATAREL_TO_TYPEREL(RMStdString));
		else if (pr.type == Meta::Type::String)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMString);
		else if (pr.type == Meta::Type::Uuid)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMUuid);
		else if (pr.type == Meta::Type::Time)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMTime);
		else if (pr.type == Meta::Type::Date)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMDate);
		else if (pr.type == Meta::Type::DateTime)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMDateTime);
		else if (pr.type == Meta::Type::ByteArray)
		{
			auto& value = CAST_CONST_DATAREL_TO_TYPEREL(RMByteArray);
			return QString("[%1] %2%3").arg(value.size()).arg(QString(value.mid(32).toHex())).arg(value.size() > 32 ? "..." : "");
		}
		else if (pr.type == Meta::Type::Byte)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMByte);
		else if (pr.type == Meta::Type::Money)
			return CAST_CONST_DATAREL_TO_TYPEREL(RMMoney);
	}
	else if (role == Qt::BackgroundRole)
	{
		if (metaDescription_.functions.contains(Meta::FunctionRoles::BackgroundRole))
		{
			const Meta::Property& pr = metaDescription_.properties[columns_[index.column()]];
			auto& data = static_cast<const MetaItemData&>(item->data());
			return metaDescription_.functions[Meta::FunctionRoles::BackgroundRole]->operator()(data, pr);
		}
	}
	else if (role == Qt::DecorationRole)
	{
		if (metaDescription_.functions.contains(Meta::FunctionRoles::DecorationRole))
		{
			const Meta::Property& pr = metaDescription_.properties[columns_[index.column()]];
			auto& data = static_cast<const MetaItemData&>(item->data());
			return metaDescription_.functions[Meta::FunctionRoles::DecorationRole]->operator()(data, pr);
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
		if (orientation == Qt::Horizontal && section >= 0 && section < columns_.count())
			return metaDescription_.properties[columns_[section]].prettyname;
		return section;
	}
	else if (role == Qt::UserRole)
	{
		if (orientation == Qt::Horizontal && section >= 0 && section < columns_.count())
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
	if (reloading_)
		return;
	int row = set_.items().count();
	beginInsertRows(QModelIndex(), row, row);
}

void MetaItemsModel::onItemAdded(const Item& /*item*/)
{
	if (reloading_)
		return;
	endInsertRows();
}

void MetaItemsModel::onItemsAdding(int count)
{
	if (reloading_)
		return;
	int row = set_.items().count();
	beginInsertRows(QModelIndex(), row, row + count - 1);
}

void MetaItemsModel::onItemsAdded()
{
	if (reloading_)
		return;
	endInsertRows();
}

void MetaItemsModel::onItemRemoving(const Item& item)
{
	if (reloading_)
		return;
	int row = set_.items().indexOf(&item);
	beginRemoveRows(QModelIndex(), row, row);
}

void MetaItemsModel::onItemRemoved(const Item& /*item*/)
{
	if (reloading_)
		return;
	endRemoveRows();
}

void MetaItemsModel::onItemChanged(const Item& item)
{
	if (reloading_)
		return;
	int row = set_.items().indexOf(&item);
	if (row < 0)
		return;
	const QModelIndex topLeft = this->createIndex(row, 0, const_cast<void*>(static_cast<const void*>(&item)));
	emit dataChanged(topLeft, this->createIndex(row, columnCount()-1,const_cast<void*>(static_cast<const void*>(&item))), baseChangingRoles);
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
