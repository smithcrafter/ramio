/*
 * Copyright (C) 2016-2019 Vladimir Kuznetsov <smithcoder@yandex.ru> https://smithcoder.ru/
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

// STRUCTITEM

#define GENERATE_CLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::StructItem<STRUCTDATA> \
	{ \
		using Base = Ramio::StructItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {} \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {} \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
		~CLASS_NAME() Q_DECL_OVERRIDE { this->beforeDeleted(); }

#define GENERATE_CLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_CLASS_START(CLASS_NAME, STRUCTDATA) \
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

// METASET

#define GENERATE_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, parent) {}


#define GENERATE_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	GENERATE_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	};

#define GENERATE_METASET_SCHEME(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName, SchemeName) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, parent) {meta_.schemeName = SchemeName;} \
};

#define GENERATE_HEADER_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_METASET_START_WITHCACHE(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaItemSet<CLASS_NAME, STRUCTDATA, true> \
{ \
	using Base = MetaItemSet<CLASS_NAME, STRUCTDATA, true>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_METASET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_METASET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
};

#define GENERATE_SOURCE_METASET(CLASS_SET_NAME, ItemsName, ItemName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, parent) {} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;

#define GENERATE_SOURCE_METASET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;


// BASEITEM

#define GENERATE_BASECLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::BaseItem<STRUCTDATA> \
	{ \
		using Base = Ramio::BaseItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(watcher) {} \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(data, watcher) {} \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
		~CLASS_NAME() Q_DECL_OVERRIDE { this->beforeDeleted(); }

#define GENERATE_BASECLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_CLASS_START(CLASS_NAME, STRUCTDATA) \
	};

#define GENERATE_HEADER_BASECLASS_START(CLASS_NAME, STRUCTDATA) \
	class CLASS_NAME : public Ramio::BaseItem<STRUCTDATA> \
	{ \
		using Base = Ramio::BaseItem<STRUCTDATA>; \
	public: \
		explicit CLASS_NAME(Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher = Q_NULLPTR); \
		~CLASS_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_BASECLASS(CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_BASECLASS_START(CLASS_NAME, STRUCTDATA) \
	};

#define GENERATE_SOURCE_BASECLASS(CLASS_NAME, STRUCTDATA) \
	CLASS_NAME::CLASS_NAME(Ramio::ItemObserver* watcher) : Base(watcher) {} \
	CLASS_NAME::CLASS_NAME(const STRUCTDATA& data, Ramio::ItemObserver* watcher) : Base(data, watcher) {} \
	CLASS_NAME::CLASS_NAME(STRUCTDATA&& data, Ramio::ItemObserver* watcher) : Base(std::forward<STRUCTDATA>(data), watcher) {} \
	CLASS_NAME::~CLASS_NAME() { this->beforeDeleted(); }


// BASESET


#define GENERATE_METABASESET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
class CLASS_SET_NAME : public Ramio::MetaBaseItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaBaseItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, \
	std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {}


#define GENERATE_METABASESET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	GENERATE_METABASESET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName) \
	};

#define GENERATE_METABASESET_SCHEME(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA, ItemsName, ItemName, SchemeName) \
class CLASS_SET_NAME : public Ramio::MetaBaseItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaBaseItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR) : Base(ItemsName, ItemName, \
	std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {meta_.schemeName = SchemeName;} \
};

#define GENERATE_HEADER_METABASESET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
class CLASS_SET_NAME : public Ramio::MetaBaseItemSet<CLASS_NAME, STRUCTDATA> \
{ \
	using Base = MetaBaseItemSet<CLASS_NAME, STRUCTDATA>; \
public: \
	CLASS_SET_NAME(QObject* parent = Q_NULLPTR); \
	~CLASS_SET_NAME() Q_DECL_OVERRIDE;

#define GENERATE_HEADER_METABASESET(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
	GENERATE_HEADER_METABASESET_START(CLASS_SET_NAME, CLASS_NAME, STRUCTDATA) \
};

#define GENERATE_SOURCE_CLASS_METABASESET(CLASS_SET_NAME, ItemsName, ItemName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;

#define GENERATE_SOURCE_METABASESET_SCHEME(CLASS_SET_NAME, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::unique_ptr<Ramio::Meta::TypeDescription>(Q_NULLPTR), parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;

#define GENERATE_SOURCE_METABASESET_SCHEME_TYPE(CLASS_SET_NAME, TYPE_DESC, ItemsName, ItemName, SchemeName) \
	CLASS_SET_NAME::CLASS_SET_NAME(QObject* parent) \
	: Base(ItemsName, ItemName, std::unique_ptr<Ramio::Meta::TypeDescription>(new TYPE_DESC), parent) {meta_.schemeName = SchemeName;} \
	CLASS_SET_NAME::~CLASS_SET_NAME() = default;

