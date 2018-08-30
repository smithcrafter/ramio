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

#include <ramio.h>
#include <QtCore/QString>
class QDebug;

#define RD_UNKNOW_ERROR -1
#define RD_NO_ERROR 0
#define RD_WARRNIN 1
#define RD_OK 2
#define RD_NOT_CURENT_ACTION_ERROR 3
#define RD_NOT_CRITICAL_ERROR 4
#define RD_ERROR_WITH_DESC 5
#define RD_NETWORK_ERROR 6
#define RD_AUTHORIZATION_ERROR 7
#define RD_SESSION_ERROR 8
#define RD_PROTOCOL_ERROR 9
#define RD_DATA_ERROR 10
#define RD_DEVICE_ERROR 11
#define RD_DATABASE_ERROR 12

/**
 * @brief The ResDesc struct.
 * Струтура с кодом ошибки и описания.
 */
struct DLL_EXPORT ResDesc
{
	int res = RD_NO_ERROR;
	QString desc;

	ResDesc() = default;
	ResDesc(int p_res) : res(p_res) {}
	ResDesc(int p_res, QString p_desc) : res(p_res), desc(std::move(p_desc)) {}

	inline bool noError() const { return !res || res == RD_OK;}
	inline bool noCriticalError() const { return (res >= RD_NO_ERROR && res <= RD_NOT_CRITICAL_ERROR);}

	void setResDesc(int v_res, QString v_desc = QString()) {res = v_res; desc = std::move(v_desc);}
};

DLL_EXPORT QDebug operator << (QDebug dbg, const ResDesc& rd);
