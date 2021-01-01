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

#pragma once

#include <QtCore/QObject>
#include "MetaItemSet.h"
#include "AbstractMetaSet.h"

namespace Ramio {

class RAMIO_LIB_EXPORT Components : public QObject
{
	Q_OBJECT
public:
	Components(QObject* parent = Q_NULLPTR);

	AbstractMetaSet* findSet(const QString& name);

	template<typename SetType>
	SetType& set(const QString& name) {auto* s = findSet(name); Q_ASSERT(s); return *static_cast<SetType&>(s);}

	const QList<AbstractMetaSet*>& sets() const {return sets_;}

	void addSet(AbstractMetaSet& set);

	void initSubComponents(Components& other);

signals:
	void itemCreated(const AbstractMetaSet& set, const Item& item);
	void itemChanged(const AbstractMetaSet& set, const Item& item);
	void itemDeleted(const AbstractMetaSet& set, const Item& item);

private:
	QList<AbstractMetaSet*> sets_;
};

} // Ramio::
