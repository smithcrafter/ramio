#include "ramio.h"
#include <QtCore/QStringList>

const QString emptyString;
const QStringList emptyStringList;

const QString& r_emptyString()
{
	return emptyString;
}

const QStringList& r_emptyStringList()
{
	return  emptyStringList;
}
