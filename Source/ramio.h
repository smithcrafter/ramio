#pragma once

#include <qcompilerdetection.h>

#ifdef RAMIO_LIB
# define DLL_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
# define DLL_EXPORT
#else
# define DLL_EXPORT Q_DECL_IMPORT
#endif
