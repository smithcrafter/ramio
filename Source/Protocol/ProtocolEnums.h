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

#include <ramio.h>
#include <Global/QtCoreDeclaration.h>
#include <QFlags>

namespace Ramio {
namespace Proto {

enum class PacketType : quint8
{
	Unset = 0,
	Query,
	Event,
	Answer,
	Ticket
};

enum class Queries : quint8
{
	Unknow = 0xFF,
	Unset = 0,
	Login = 0x10,
	ReLogin = 0x11,
	PrepareSession = 0x12,
	StartSession = 0x13,
	RestoreSession = 0x14,
	FinishSession = 0x16,
	Logout = 0x17,

	GetData = 0x20,
	GetDataObject = 0x21,

	GetDataSet = 0x27,

	CreateDataObject = 0x30,
	SaveDataObject = 0x31,
	DeleteDataObject = 0x37,

	RunDataObjectFunction = 0x41,
	RunDataSetFunction = 0x47,

	RunAction = 0x80,
	StartOperation = 0x91,
	CancelOperation = 0x97,
};

enum class Events : quint8
{
	Unknow = 0xFF,
	Unset = 0,
	Disconnect,
	DataObjectCreated,
	DataObjectsCreated,
	DataObjectChanged,
	DataObjectsChanged,
	DataObjectDeleted,
	DataObjectsDeleted,
	EnumCount
};

enum class DataSetChangeNotification : quint8
{
	None = 0,
	AddImmediately = 0x01,
	AddCache = 0x02,
	ChangeImmediately = 0x04,
	ChangeCache = 0x08,
	DelImmediately = 0x10,
	DelCache = 0x20,
	SetReloaded = 0x40,
	NotUseThisFlag = 0x80,
	Immediately = 0x55,
	Cache = 0x6A,
	Full = 0x7F
};

Q_DECLARE_FLAGS(DataSetChangeNotifications, DataSetChangeNotification)
Q_DECLARE_OPERATORS_FOR_FLAGS(DataSetChangeNotifications)

} // Proto::
} // Ramio::
