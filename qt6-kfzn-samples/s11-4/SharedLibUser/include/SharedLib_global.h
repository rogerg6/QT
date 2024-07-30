#ifndef SHAREDLIB_GLOBAL_H
#define SHAREDLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHAREDLIB_LIBRARY)
#define SHAREDLIB_EXPORT Q_DECL_EXPORT
#else
#define SHAREDLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SHAREDLIB_GLOBAL_H
