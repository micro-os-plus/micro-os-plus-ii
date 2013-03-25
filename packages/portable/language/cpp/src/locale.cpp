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

#include "portable/core/include/OS_Defines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/locale.h"
#include <stdlib.h>

namespace os
{
  namespace std
  {

    locale::locale() _NOEXCEPT
    {
      init();
    }

    void
    locale::init(void)
    {
      dummy = 0;
    }

    bool
    locale::has_facet(id& x __attribute__((unused))) const
    {
      return true;
    }

    const locale::facet*
    locale::use_facet(id& x __attribute__((unused))) const
    {
      return nullptr;
    }

  }
}

#endif
