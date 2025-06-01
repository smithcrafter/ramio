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

#include "Protocol.h"
#include <QtCore/QMap>

namespace Ramio {

struct ItemData;
namespace Meta {struct Description;}

namespace Proto {

struct RAMIO_LIB_EXPORT EPDataObjectCreated : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;
	QMap<QString, QString> fields;

	EPDataObjectCreated(qint64 pid = 0) : EventPacket(Events::DataObjectCreated, pid) {}
	EPDataObjectCreated(QString dataSetName, QString itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT EPDataObjectsCreated : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QList<QMap<QString, QString>> fieldsList;

	EPDataObjectsCreated(qint64 pid = 0) : EventPacket(Events::DataObjectsCreated, pid) {}
	EPDataObjectsCreated(QString dataSetName, QString itemName, qint64 pid = 0);

	void appendFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data, int index) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


struct RAMIO_LIB_EXPORT EPDataObjectChanged : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;
	QMap<QString, QString> fields;

	EPDataObjectChanged(qint64 pid = 0) : EventPacket(Events::DataObjectChanged, pid) {}
	EPDataObjectChanged(QString dataSetName, QString itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT EPDataObjectsChanged : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QList<QMap<QString, QString>> fieldsList;

	EPDataObjectsChanged(qint64 pid = 0) : EventPacket(Events::DataObjectsChanged, pid) {}
	EPDataObjectsChanged(QString dataSetName, QString itemName, qint64 pid = 0);

	void appendFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data, int index) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT EPDataObjectDeleted : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	EPDataObjectDeleted(qint64 pid = 0) : EventPacket(Events::DataObjectDeleted, pid) {}
	EPDataObjectDeleted(QString dataSetName, QString itemName, QString id, QString uuid, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT EPDataObjectsDeleted : public EventPacket
{
	QString dataSetName;
	QString itemName;
	QList<QPair<QString, QString>> itemIdUUid;

	EPDataObjectsDeleted(qint64 pid = 0) : EventPacket(Events::DataObjectsDeleted, pid) {}
	EPDataObjectsDeleted(QString dataSetName, QString itemName, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

} // Proto::
} // Ramio::
