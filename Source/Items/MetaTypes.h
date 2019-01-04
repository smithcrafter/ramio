#pragma once

#include <ramio.h>
#include <QtCore/QUuid>
#include <QtCore/QDateTime>

#define DB_NULL 0

#define RMetaPKey quint64
#define RMetaInt int
#define RMetaLong long long
#define RMetaUuid QUuid
#define RMetaString QString
#define RMetaDouble double
#define RMetaTime QTime
#define RMetaDateTime QDateTime
#define RMetaMoney double


template<typename TYPE>
QString typeToString(const TYPE& t);


template<> QString typeToString<RMetaPKey>(const RMetaPKey& value);
template<> QString typeToString<RMetaInt>(const RMetaInt& value);
template<> QString typeToString<RMetaUuid>(const RMetaUuid& value);
template<> QString typeToString<RMetaString>(const RMetaString& value);
template<> QString typeToString<RMetaDouble>(const RMetaDouble& value);
template<> QString typeToString<RMetaDateTime>(const RMetaDateTime& value);
