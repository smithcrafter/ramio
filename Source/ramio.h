#pragma once

#define Ramio Ramio_Namespace_0_1_6

#  ifdef __linux
#    define Q_DECL_EXPORT     __attribute__((visibility("default")))
#    define Q_DECL_IMPORT     __attribute__((visibility("default")))
#    define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#  else
#    define Q_DECL_EXPORT     __declspec(dllexport)
#    define Q_DECL_IMPORT     __declspec(dllimport)

#  endif

#ifdef RAMIO_LIB
	#define RAMIO_LIB_EXPORT Q_DECL_EXPORT
#elif defined(RAMIO_DIRECT)
	#define RAMIO_LIB_EXPORT
#else
	#define RAMIO_LIB_EXPORT Q_DECL_IMPORT
#endif

class QString;
//class QStringList;
class QLatin1String;

namespace Ramio {

extern const RAMIO_LIB_EXPORT QString emptyString;

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
