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

#include "ProtocolStr.h"
#include <QtCore/QString>

namespace Ramio {
namespace Proto {

const QString DataSetChangeNotificationAtr(QStringLiteral("DataSetChangeNotification"));
const QString DataSetNameAtr(QStringLiteral("DataSetName"));
const QString ItemIdAtr(QStringLiteral("ItemId"));
const QString ItemNameAtr(QStringLiteral("ItemName"));
const QString ItemUuidAtr(QStringLiteral("ItemUuid"));
const QString PasswordAtr(QStringLiteral("Password"));
const QString SchemeNameAtr(QStringLiteral("SchemeName"));
const QString SessionKeyAtr(QStringLiteral("SessionKey"));
const QString UUIDAtr(QStringLiteral("UUID"));
const QString UserIdAtr(QStringLiteral("UserId"));
const QString UsernameAtr(QStringLiteral("Username"));
const QString ActionAtr(QStringLiteral("Action"));
const QString SectionAtr(QStringLiteral("Section"));
const QString ResultAtr(QStringLiteral("Result"));
const QString ValuesAtr(QStringLiteral("Values"));
const QString ParamsAtr(QStringLiteral("Params"));

} // Proto::
} // Ramio::
