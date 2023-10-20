#pragma once

#ifdef __linux
# define Q_DECL_EXPORT     __attribute__((visibility("default")))
# define Q_DECL_IMPORT     __attribute__((visibility("default")))
# define Q_DECL_HIDDEN     __attribute__((visibility("hidden")))
#else
# define Q_DECL_EXPORT     __declspec(dllexport)
# define Q_DECL_IMPORT     __declspec(dllimport)
#endif

class QString;
class QLatin1String;

#define const_static_cast(type, ptr) const_cast<type*>(static_cast<const type*>(ptr));
#define remove_const_reference_t(type) std::remove_const_t<std::remove_reference_t<type>>

#define CLEAR_PTR(p) 	if (p) {delete p;} p = nullptr;
