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

#include "MetaItemSet.h"

#define GENERATE_CLASS(CLASS_NAME, STRUCTDATA) \
class CLASS_NAME : public Ramio::StructItem<STRUCTDATA> \
{ \
	using Base = Ramio::StructItem<STRUCTDATA>; \
public: \
	explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {} \
	CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {} \
	CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
	~CLASS_NAME() Q_DECL_OVERRIDE { this->beforeDeleted(); }\
};

#define GENERATE_HEADER_CLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::StructItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StructItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		~CLASS_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_CLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_CLASS_START(CLASS_NAME, STRUCTDATA) \
	};

#define GENERATE_SOURCE_CLASS(CLASS_NAME, STRUCTDATA) \
	CLASS_NAME::CLASS_NAME(Ramio::ItemObserver* watcher) : Base(watcher) {} \
	CLASS_NAME::CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher) : Base(data, watcher) {} \
	CLASS_NAME::CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
	CLASS_NAME::~CLASS_NAME() { this->beforeDeleted(); }


#define GENERATE_CLASS_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, \
	std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {} \
};

#define GENERATE_HEADER_CLASS_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_CLASS_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_CLASS_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
};

#define GENERATE_SOURCE_CLASS_METASET(CLASS_SET_NAME, ItemsName, ItemName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;
