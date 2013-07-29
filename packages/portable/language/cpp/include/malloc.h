//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//
// References are to ISO/IEC 14882:2011(E) Third edition (2011-09-01).
//

/// \file
/// \brief Local malloc() & free() declarations.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/cstdint.h"
#include "portable/language/cpp/include/cstddef.h"

namespace os
{
  namespace std
  {
    void*
    malloc(os::std::size_t size);

    void
    free(void *ptr);

  } // namespace std
} // namespace os

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H
