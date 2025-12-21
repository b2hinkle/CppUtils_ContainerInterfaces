// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#ifndef CPPUTILS_CONTAINERINTERFACES_INCLUDE_EXPORT_H
#define CPPUTILS_CONTAINERINTERFACES_INCLUDE_EXPORT_H

// Since interface libraries cannot generate header files during their cmake configuration, we author our
// own "export header" file here, which defines the export macros as a noop.

#define CPPUTILS_CONTAINERINTERFACES_EXPORT
#define CPPUTILS_CONTAINERINTERFACES_NO_EXPORT

#endif // #ifndef CPPUTILS_CONTAINERINTERFACES_INCLUDE_EXPORT_H
