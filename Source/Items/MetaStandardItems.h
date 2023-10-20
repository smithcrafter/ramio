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

#include "MetaStandardItemSet.h"


// STANDARD CLASS [full]

#define GENERATE_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::StandardItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StandardItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {} \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {} \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
		~CLASS_NAME() Q_DECL_OVERRIDE { if (!watchers_.isEmpty()) this->beforeDeleted(); }

#define RGEN_STANDARDCLASS_START(CLASS_NAME) \
	GENERATE_STANDARDCLASS_START(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


#define GENERATE_STANDARDCLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA) };

#define RGEN_STANDARDCLASS(CLASS_NAME) \
	GENERATE_STANDARDCLASS(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


// STANDARD CLASS [header]

#define GEN_HEADER_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA) \
	  public Ramio::StandardItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StandardItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		~CLASS_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : GEN_HEADER_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA)

#define RGEN_HEADER_STANDARDCLASS_START(CLASS_NAME) \
	GENERATE_HEADER_STANDARDCLASS_START(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


#define GENERATE_HEADER_STANDARDCLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_STANDARDCLASS_START(CLASS_NAME, STRUCTDATA) };

#define RGEN_HEADER_STANDARDCLASS(CLASS_NAME) \
	GENERATE_HEADER_STANDARDCLASS(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)

// STANDARD CLASS [source]

#define GENERATE_SOURCE_STANDARDCLASS(CLASS_NAME, STRUCTDATA) \
	CLASS_NAME::CLASS_NAME(Ramio::ItemObserver* watcher) : Base(watcher) {} \
	CLASS_NAME::CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher) : Base(data, watcher) {} \
	CLASS_NAME::CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
	CLASS_NAME::~CLASS_NAME() { if (!watchers_.isEmpty()) this->beforeDeleted(); }

#define RGEN_SOURCE_STANDARDCLASS(CLASS_NAME) \
	GENERATE_SOURCE_STANDARDCLASS(CLASS_NAME, Ramio::RItem2StrucData<CLASS_NAME>::type)


// STANDARD SET [full]

#define GENERATE_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
class CLASS_SET_NAME : public Ramio::MetaStandardItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaStandardItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, \
	std::shared_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {}

#define RGEN_STANDARDSET_START(CLASS_SET_NAME, ItemsName, ItemName) \
	GENERATE_STANDARDSET_START(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName)


#define GENERATE_STANDARDSET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	GENERATE_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) };

#define RGEN_STANDARDSET(CLASS_SET_NAME, ItemsName, ItemName) \
	GENERATE_STANDARDSET(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName)


#define GENERATE_STANDARDSET_SCHEME(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName, SchemeName) \
class CLASS_SET_NAME : public Ramio::MetaStandardItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaStandardItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, \
	std::shared_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {meta_.schemeName = SchemeName;} };

#define RGEN_STANDARDSET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	GENERATE_STANDARDSET_SCHEME(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type, ItemsName, ItemName, SchemeName) \


// STANDARD SET [header]

#define GEN_HEADER_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	public Ramio::MetaStandardItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaStandardItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define RGEN_HEADER_STANDARDSET_START(CLASS_SET_NAME) \
	GENERATE_HEADER_STANDARDSET_START(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type) \

#define GENERATE_HEADER_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	class CLASS_SET_NAME : GEN_HEADER_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA)

#define GENERATE_HEADER_STANDARDSET_START_WITHCACHE(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaStandardItemSet<CLASS_NAME, STRUCTDATA, true, true> \
{ \
	using Base = MetaStandardItemSet<CLASS_NAME, STRUCTDATA, true, true>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define RGEN_HEADER_STANDARDSET_START_WITHCACHE(CLASS_SET_NAME) \
	GENERATE_HEADER_STANDARDSET_START_WITHCACHE(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type)


#define GENERATE_HEADER_STANDARDSET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_STANDARDSET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) };

#define RGEN_HEADER_STANDARDSET(CLASS_SET_NAME) \
	GENERATE_HEADER_STANDARDSET(CLASS_SET_NAME, Ramio::RContainer2Item<CLASS_SET_NAME>::type, \
	Ramio::RItem2StrucData<Ramio::RContainer2Item<CLASS_SET_NAME>::type>::type)

// STANDARD SET [source]

#define GENERATE_SOURCE_STANDARDSET(CLASS_SET_NAME, ItemsName, ItemName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::shared_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {} \
	CLASS_SET_NAME::~CLASS_SET_NAME() {}

#define GENERATE_SOURCE_STANDARDSET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::shared_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() {}

#define GENERATE_SOURCE_STANDARDSET_SCHEME_TYPE(CLASS_SET_NAME, TYPE_DESC, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::shared_ptr<Ramio::Meta::TypeDescription>(new TYPE_DESC), parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() {}
