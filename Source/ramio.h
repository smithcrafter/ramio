#pragma once

#include <QtCore/qcompilerdetection.h>

#ifdef RAMIO_LIB
	#define RAMIO_LIB_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
	#define RAMIO_LIB_EXPORT
#else
	#define RAMIO_LIB_EXPORT Q_DECL_IMPORT
#endif


class QString;
class QStringList;
class QLatin1String;

namespace Ramio {

extern const RAMIO_LIB_EXPORT QString emptyString;
extern const RAMIO_LIB_EXPORT QStringList emptyStringList;

} // Ramio::

#define const_static_cast(type, ptr) const_cast<type*>(static_cast<const type*>(ptr));
#define remove_const_reference_t(type) std::remove_const_t<std::remove_reference_t<type>>

#ifdef QDOC
	#undef Q_OBJECT
	#undef slots
	#undef Q_DISABLE_COPY
	#undef DLL_EXPORT
	#undef Q_NULLPTR
	#undef Q_DECL_OVERRIDE

	#define Q_OBJECT
	#define slots
	#define Q_DISABLE_COPY(Class)
	#define DLL_EXPORT
	#define Q_NULLPTR  0
	#define Q_DECL_OVERRIDE
#endif
