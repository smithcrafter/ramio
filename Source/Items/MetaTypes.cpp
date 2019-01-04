#include "MetaTypes.h"

template<>
QString typeToString<RMetaPKey>(const RMetaPKey& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaInt>(const RMetaInt& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaUuid>(const RMetaUuid& value)
{
	return value.toString();
}

template<>
QString typeToString<RMetaString>(const RMetaString& value)
{
	return value;
}

template<>
QString typeToString<RMetaDouble>(const RMetaDouble& value)
{
	return QString::number(value);
}

template<>
QString typeToString<RMetaDateTime>(const RMetaDateTime& value)
{
	return value.toString(Qt::ISODate);
}
