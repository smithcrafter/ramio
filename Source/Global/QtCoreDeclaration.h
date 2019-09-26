#pragma once

#include <string>

class QByteArray;
class QString;
class QStringList;
class QLatin1String;
using QLatin1Literal = QLatin1String;
class QDate;
class QTime;
class QDateTime;
class QUuid;
class QDomElement;
class QDomDocument;
class QDomNode;
class QHostAddress;
class QTimer;

#ifndef QGLOBAL_H

using qint8 = signed char;			/* 8 bit signed */
using quint8 = unsigned char;		/* 8 bit unsigned */
using qint16 = short;				/* 16 bit signed */
using quint16 = unsigned short;		/* 16 bit unsigned */
using qint32 = int;					/* 32 bit signed */
using quint32 = unsigned int;		/* 32 bit unsigned */
using qint64 = long long;			/* 64 bit signed */
using quint64 = unsigned long long;	/* 64 bit unsigned */
using qlonglong = qint64;
using qulonglong = quint64;

#endif
