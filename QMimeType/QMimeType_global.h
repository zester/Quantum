#ifndef QMIMETYPE_GLOBAL_H
#define QMIMETYPE_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QtXml>

#if defined(QMIMETYPE_LIBRARY)
#  define QMIMETYPESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMIMETYPESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMIMETYPE_GLOBAL_H
