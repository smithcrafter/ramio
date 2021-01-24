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

#include "MetaItemData.h"

class QDomElement;
class QJsonObject;
class QJsonArray;
class QObject;
class QIODevice;

namespace Ramio {

namespace Serialization {

struct Options
{
	bool keepEmptyValues = false;
	QStringList skipFields;
};

const Options& standardOptions();


void serialize(const Ramio::Meta::Description& meta, const Ramio::ItemData& data, QDomElement& deItem,
			   const Options& options = standardOptions());
void deserialize(const Ramio::Meta::Description& meta, Ramio::ItemData& data, const QDomElement& deItem);

void serialize(const Ramio::Meta::Description& meta, const Ramio::ItemData& data, QMap<QString, QString>& map,
			   const Options& options = standardOptions());
void deserialize(const Ramio::Meta::Description& meta, Ramio::ItemData& data, const QMap<QString, QString>& map);

void serialize(const Ramio::Meta::Description& meta, const ItemData& data, QJsonObject& jsObject,
			   const Options& options = standardOptions());
void deserialize(const Ramio::Meta::Description& meta, Ramio::ItemData& data, const QJsonObject& jsObject);



void serialize(const Ramio::Meta::Description& meta, const ItemData& data, QIODevice& device);
bool deserialize(const Ramio::Meta::Description& meta, Ramio::ItemData& data, QIODevice& device);

} // Serialization ::

} // Ramio::
