#pragma once

#include <qcompilerdetection.h>

#ifdef RAMIO_LIB
	# define DLL_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
	# define DLL_EXPORT
#else
	# define DLL_EXPORT Q_DECL_IMPORT
#endif


class QString;
class QStringList;
class QLatin1String;

namespace Ramio {

extern const DLL_EXPORT QString emptyString;
extern const DLL_EXPORT QStringList emptyStringList;

} // Ramio::

# define const_static_cast(type, ptr) const_cast<type*>(static_cast<const type*>(ptr));
# define remove_const_reference_t(type) std::remove_const_t<std::remove_reference_t<type>>

