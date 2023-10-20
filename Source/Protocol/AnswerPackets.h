/*
 * Copyright (C) 2016-2023 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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
class AbstractMetaSet;

namespace Proto {

struct RAMIO_LIB_EXPORT APPingPong : public AnswerQueryPacket
{
	APPingPong(qint64 pid = 0) : AnswerQueryPacket(Queries::PingPong, pid) {}
};

struct RAMIO_LIB_EXPORT APLogin : public AnswerQueryPacket
{
	QString userId;
	QString name;
	QString uuid;

	APLogin(qint64 pid = 0) : AnswerQueryPacket(Queries::Login, pid) {}
	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APGetDataObject: public AnswerQueryPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	QMap<QString, QString> fields;

	APGetDataObject(qint64 pid = 0) : AnswerQueryPacket(Queries::GetDataObject, pid) {}
	APGetDataObject(QString dataSetName, QString itemName, QString id, QString uuid, qint64 pid = 0);

	void createFromData(const Ramio::Meta::Description& meta, const Ramio::ItemData& data);
	void updateData(const Ramio::Meta::Description& meta, Ramio::ItemData& data) const;

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APGetDataSet : public AnswerQueryPacket
{
	const Ramio::AbstractMetaSet* set = Q_NULLPTR;

	QString dataSetName;

	APGetDataSet(qint64 pid = 0) : AnswerQueryPacket(Queries::GetDataSet, pid) {}
	APGetDataSet(const Ramio::AbstractMetaSet& set, qint64 pid = 0);

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APCreateDataObject : public AnswerQueryPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APCreateDataObject(qint64 pid = 0) : AnswerQueryPacket(Queries::CreateDataObject, pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APSaveDataObject : public AnswerQueryPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APSaveDataObject(qint64 pid = 0) : AnswerQueryPacket(Queries::SaveDataObject, pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APDeleteDataObject : public AnswerQueryPacket
{
	QString dataSetName;
	QString itemName;
	QString itemId;
	QString itemUuid;

	APDeleteDataObject(qint64 pid = 0) : AnswerQueryPacket(Queries::DeleteDataObject, pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

struct RAMIO_LIB_EXPORT APRunAction : public AnswerQueryPacket
{
	QString action;
	QString section;
	ResDesc result;
	QMap<QString, QString> values;

	APRunAction(qint64 pid = 0) : AnswerQueryPacket(Queries::RunAction, pid) {}

	void serialize(XmlDocument& msg) const Q_DECL_OVERRIDE;
	void deserialize(const XmlDocument& msg) Q_DECL_OVERRIDE;
};

} // Proto::
} // Ramio::
