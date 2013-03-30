//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//
// [Partly inspired from the LLVM libcxx sources].
// Copyright (c) 2009-2013 by the contributors listed in
// 'LLVM libcxx Credits.txt'. See 'LLVM libcxx License.txt' for details.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS) || defined(__DOXYGEN__)

#include "portable/language/cpp/include/streambuf.h"
#include "portable/language/cpp/include/streambuf.cpp.h"

#include <wchar.h>

namespace os
{
  namespace std
  {

    // Explicit instantiation of the template.
    template class basic_streambuf<char> ;
  }
}

#endif // defined(OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS)
