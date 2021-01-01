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

#include "MetaItemSet.h"


// STRUCTITEM [full]

#define GENERATE_METACLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::StructItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StructItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {} \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {} \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
		~CLASS_NAME() Q_DECL_OVERRIDE { this->beforeDeleted(); }

#define RGEN_METACLASS_START(CLASS_NAME) \
	GENERATE_METACLASS_START(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


#define GENERATE_METACLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_METACLASS_START(CLASS_NAME, STRUCTDATA) };

#define RGEN_METACLASS(CLASS_NAME) \
	GENERATE_METACLASS(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)

// STRUCTITEM [header]

#define GENERATE_HEADER_METACLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::StructItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StructItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		~CLASS_NAME() Q_DECL_OVERRIDE;

#define RGEN_HEADER_METACLASS_START(CLASS_NAME) \
	GENERATE_HEADER_METACLASS_START(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


#define GENERATE_HEADER_METACLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_METACLASS_START(CLASS_NAME, STRUCTDATA) };

#define RGEN_HEADER_METACLASS(CLASS_NAME) \
	GENERATE_HEADER_METACLASS(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


// STRUCTITEM [source]

#define GENERATE_SOURCE_METACLASS(CLASS_NAME, STRUCTDATA) \
	CLASS_NAME::CLASS_NAME(Ramio::ItemObserver* watcher) : Base(watcher) {} \
	CLASS_NAME::CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher) : Base(data, watcher) {} \
	CLASS_NAME::CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
	CLASS_NAME::~CLASS_NAME() { this->beforeDeleted(); }

#define RGEN_SOURCE_METACLASS(CLASS_NAME) \
	GENERATE_SOURCE_METACLASS(CLASS_NAME, STRUCTDATA)


// METASET [full]

#define GENERATE_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, parent) {}

#define RGEN_METASET_START(CLASS_SET_NAME, ItemsName, ItemName) \
	GENERATE_METASET_START(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName)


#define GENERATE_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	GENERATE_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) };

#define RGEN_METASET(CLASS_SET_NAME, ItemsName, ItemName) \
	GENERATE_METASET(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName) \


#define GENERATE_METASET_SCHEME(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName, SchemeName) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, parent) {meta_.schemeName = SchemeName;} \
};

#define RGEN_METASET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	GENERATE_METASET_SCHEME(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName, SchemeName)


// METASET [header]

#define GENERATE_HEADER_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define RGEN_HEADER_METASET_START(CLASS_SET_NAME) \
	GENERATE_HEADER_METASET_START(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type)


#define GENERATE_HEADER_METASET_START_WITHCACHE(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA, true> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA, true>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define RGEN_HEADER_METASET_START_WITHCACHE(CLASS_SET_NAME) \
	GENERATE_HEADER_METASET_START_WITHCACHE(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type)


#define GENERATE_HEADER_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) };

#define RGEN_HEADER_METASET(CLASS_SET_NAME) \
	GENERATE_HEADER_METASET(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type))

// METASET [source]

#define GENERATE_SOURCE_METASET(CLASS_SET_NAME, ItemsName, ItemName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, parent) {} \
	CLASS_SET_NAME::~CLASS_SET_NAME() {}

#define GENERATE_SOURCE_METASET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() {}
