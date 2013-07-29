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

#include "portable/core/include/ConfigDefines.h"

#include "portable/diagnostics/include/Trace.h"

#include "portable/language/cpp/include/malloc.h"

#include "portable/language/cpp/include/cstdlib.h"

namespace os
{
  namespace std
  {
    /// \details
    /// The malloc() function allocates size bytes of memory and returns a
    /// pointer to the allocated memory. Currently it calls
    /// the C function.
    void*
    malloc(os::std::size_t size) noexcept
    {
      void* p = ::malloc(size);
#if defined(DEBUG)
      os::diag::trace.putString("os::core::malloc(");
      os::diag::trace.putDec(size);
      os::diag::trace.putString(") -> ");
      os::diag::trace.putHex(p);
      os::diag::trace.putNewLine();
#endif
      return p;
    }

    /// \details
    /// The free() function deallocates the memory allocation pointed
    /// to by ptr.
    /// If ptr is a NULL pointer, no operation is performed.
    /// Currently it calls
    /// the C function.
    void
    free(void *ptr) noexcept
    {
#if defined(DEBUG)
      os::diag::trace.putString("os::core::free(");
      os::diag::trace.putHex(ptr);
      os::diag::trace.putString(")");
      os::diag::trace.putNewLine();
#endif
      return ::free(ptr);
    }
  } // namespace std
} // namespace os
