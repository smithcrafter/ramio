#pragma once

#include <qcompilerdetection.h>
class QStringList;

const QString& r_emptyString();
const QStringList& r_emptyStringList();

#ifdef RAMIO_LIB
# define DLL_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
# define DLL_EXPORT
#else
# define DLL_EXPORT Q_DECL_IMPORT
#endif
