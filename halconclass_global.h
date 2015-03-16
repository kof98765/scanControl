#ifndef MYHALCON_GLOBAL_H
#define MYHALCON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HALCONCLASS_LIBRARY)
#  define HALCONCLASSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HALCONCLASSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MYHALCON_GLOBAL_H
