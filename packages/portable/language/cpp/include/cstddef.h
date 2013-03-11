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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDDEF_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDDEF_H_

#include "portable/core/include/OS_Defines.h"

#include "portable/language/cpp/include/internal/__config.h"

#include <stddef.h>

namespace os
{
  namespace std
  {

#if !defined(__DOXYGEN__)
    using ::ptrdiff_t;
    using ::size_t;
#endif

    typedef long double max_align_t;

    typedef decltype(nullptr) nullptr_t;

  }
}

#endif  /* OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDDEF_H_ */
