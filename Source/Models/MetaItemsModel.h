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

#pragma once

#include <QAbstractItemModel>
#include <Items/ItemSet.h>
#include <Items/AbstractMetaSet.h>
#include <Items/MetaItemData.h>

namespace Ramio {

class DLL_EXPORT MetaItemsModel : public QAbstractItemModel
{
	Q_OBJECT
	Q_DISABLE_COPY(MetaItemsModel)
public:
	MetaItemsModel(const AbstractMetaSet& set, QObject* parent = Q_NULLPTR);
	MetaItemsModel(const AbstractSet& set, const Meta::Description& metaDescription, QObject* parent = Q_NULLPTR);
	~MetaItemsModel() Q_DECL_OVERRIDE;

	void setColumns(const QList<quint8>& columns = QList<quint8>());

	void resetModel() {onItemsReloading(); onItemsReloaded();}

protected:
	QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
	bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex& index) const Q_DECL_OVERRIDE;

private slots:
	void onItemAdding(const Item& item);
	void onItemAdded(const Item& item);
	void onItemsAdding(int count);
	void onItemsAdded();
	void onItemRemoving(const Item& item);
	void onItemRemoved(const Item& item);
	void onItemChanged(const Item& item);
	void onItemsReloading();
	void onItemsReloaded();

private:
	const AbstractSet& set_;
	const Meta::Description& metaDescription_;
	QList<quint8> columns_;
	bool reloading_ = false;
};

} // Ramio::
