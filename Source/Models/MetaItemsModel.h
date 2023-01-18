/*
 * Copyright (C) 2016-2022 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

#pragma once

#include <QtCore/QAbstractItemModel>
#include <Items/ItemSet.h>
#include <Items/AbstractMetaSet.h>
#include <Items/MetaItemData.h>

namespace Ramio {

class RAMIO_LIB_EXPORT MetaItemsModel : public QAbstractItemModel
{
	Q_OBJECT
	Q_DISABLE_COPY(MetaItemsModel)
public:
	MetaItemsModel(const AbstractMetaSet& set, QObject* parent = Q_NULLPTR);
	MetaItemsModel(const AbstractListSet& set, const Meta::Description& metaDescription, QObject* parent = Q_NULLPTR);
	~MetaItemsModel() Q_DECL_OVERRIDE;

	void setColumnIndexes(const QList<quint8>& columns = QList<quint8>());
	void setColumns(const QStringList& names) {setColumnIndexes(metaDescription_.fieldIndexes(names, true));}

	void resetModel() {onItemsReloading(); onItemsReloaded();}

	void setCheckable() {checking_ = true; resetModel();}

protected:
	QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE {Q_UNUSED(index); return QModelIndex(); }
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE {return parent == QModelIndex() ? set_.count() : 0;}
	int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE {return parent == QModelIndex() ? columns_.count() : 0;}
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
	const AbstractListSet& set_;
	const Meta::Description& metaDescription_;
	QList<quint8> columns_;
	QList<const Ramio::Item*> checked_;
	bool checking_ = false;
	bool reloading_ = false;
};

} // Ramio::
