#pragma once

#include "cppappcore.h"

#ifndef QDOC
#define Ramio Ramio_Namespace_0_1_8
#endif

#ifdef RAMIO_LIB
# define RAMIO_LIB_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
# define RAMIO_LIB_EXPORT
#else
# define RAMIO_LIB_EXPORT Q_DECL_IMPORT
#endif

namespace Ramio {

extern const RAMIO_LIB_EXPORT QString emptyString;

} // Ramio::

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
