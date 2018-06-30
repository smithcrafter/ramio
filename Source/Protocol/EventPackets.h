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

#include "Protocol.h"
#include <Items/AbstractMetaSet.h>

namespace Ramio {
namespace Proto {

struct DLL_EXPORT EPDataObjectCreated : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QMap<QString, QString> fields;

	EPDataObjectCreated(qint64 pid = 0) : EventPacket(Events::DataObjectCreated, pid) {}
	EPDataObjectCreated(QString v_dataSetName, QString v_itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT EPDataObjectChanged : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QMap<QString, QString> fields;

	EPDataObjectChanged(qint64 pid = 0) : EventPacket(Events::DataObjectChanged, pid) {}
	EPDataObjectChanged(QString v_dataSetName, QString v_itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT EPDataObjectDeleted : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	EPDataObjectDeleted(qint64 pid = 0) : EventPacket(Events::DataObjectDeleted, pid) {}
	EPDataObjectDeleted(QString v_dataSetName, QString v_itemName, QString v_id, QString v_uuid, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


} // Proto::
} // Ramio::
