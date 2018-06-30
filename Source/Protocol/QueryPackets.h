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
#include <Items/MetaItemData.h>
#include <QtCore/QMap>

namespace Ramio {
namespace Proto {

struct DLL_EXPORT QPLogin : public QueryPacket
{
	QString username;
	QString password;

	QPLogin(qint64 pid = 0) : QueryPacket(Queries::Login, pid) {}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


struct DLL_EXPORT QPGetData : public QueryPacket
{
	QPGetData(qint64 pid = 0) : QueryPacket(Queries::GetData, pid) {}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct QPGetObject : public QueryPacket
{
	QPGetObject(qint64 pid = 0) : QueryPacket(Queries::GetDataObject, pid) {}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct DLL_EXPORT QPGetDataSet : public QueryPacket
{
	QString dataSetName;

	QPGetDataSet(qint64 pid = 0) : QueryPacket(Queries::GetDataSet, pid) {}
	QPGetDataSet(QString v_dataSetName, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

/**
 * @brief The QPCreateDataObject struct
 */
struct DLL_EXPORT QPCreateDataObject : public QueryPacket
{
	QString dataSetName;
	QString itemName;
	QMap<QString, QString> fields;

	QPCreateDataObject(qint64 pid = 0) : QueryPacket(Queries::CreateDataObject, pid) {}
	QPCreateDataObject(QString v_dataSetName, QString v_itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

/**
 * @brief The QPSaveDataObject struct
 * При разборе необходимо проверить "DataSetName", "ItemName", "Uuid" и выделить память.
 */
struct DLL_EXPORT QPSaveDataObject : public QueryPacket
{
	QString dataSetName;
	QString itemName;
	QMap<QString, QString> fields;

	QPSaveDataObject(qint64 pid = 0) : QueryPacket(Queries::SaveDataObject, pid) {}
	QPSaveDataObject(QString v_dataSetName, QString v_itemName, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


struct DLL_EXPORT QPDeleteDataObject : public QueryPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	QPDeleteDataObject(qint64 pid = 0) : QueryPacket(Queries::DeleteDataObject, pid) {}
	QPDeleteDataObject(QString v_dataSetName, QString v_itemName, QString v_id, QString v_uuid, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};


struct DLL_EXPORT QPStartSession : public QueryPacket
{
	QPStartSession(qint64 pid = 0) : QueryPacket(Queries::StartSession, pid) {}
};


} // Proto::
} // Ramio::
