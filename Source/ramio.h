#pragma once

#include <qcompilerdetection.h>
class QStringList;

const QString& r_emptyString();
const QStringList& r_emptyStringList();

#ifdef RAMIO_LIB
	# define DLL_EXPORT Q_DECL_EXPORT
	extern const QString emptyString;
	extern const QStringList emptyStringList;
#elif defined(RAMIO_DIRECT)
	# define DLL_EXPORT
	extern const QString emptyString;
	extern const QStringList emptyStringList;
#else
	# define DLL_EXPORT Q_DECL_IMPORT
#endif

# define const_static_cast(type, ptr) const_cast<type*>(static_cast<const type*>(ptr));

