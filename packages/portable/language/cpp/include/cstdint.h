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

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDINT_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDINT_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/language/cpp/include/internal/__config.h"
#include <stdint.h>

namespace os
{
  namespace std
  {

    using ::int8_t;
    using ::int16_t;
    using ::int32_t;
    using ::int64_t;

    using ::uint8_t;
    using ::uint16_t;
    using ::uint32_t;
    using ::uint64_t;

    using ::int_least8_t;
    using ::int_least16_t;
    using ::int_least32_t;
    using ::int_least64_t;

    using ::uint_least8_t;
    using ::uint_least16_t;
    using ::uint_least32_t;
    using ::uint_least64_t;

    using ::int_fast8_t;
    using ::int_fast16_t;
    using ::int_fast32_t;
    using ::int_fast64_t;

    using ::uint_fast8_t;
    using ::uint_fast16_t;
    using ::uint_fast32_t;
    using ::uint_fast64_t;

    using ::intptr_t;
    using ::uintptr_t;

    using ::intmax_t;
    using ::uintmax_t;

  }
}

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CSTDINT_H_
