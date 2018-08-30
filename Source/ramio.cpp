#include <QtCore/QStringList>

static const QString emptyString;
static const QStringList emptyStringList;

const QString &r_emptyString()
{
	return emptyString;
}

const QStringList& r_emptyStringList()
{
	return  emptyStringList;
}
