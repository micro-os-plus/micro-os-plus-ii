#include "portable/language/cpp/include/malloc.h"

#include "portable/diagnostics/include/Trace.h"

//#include <stddef.h>
#include <stdlib.h>

namespace os
{

  void*
  malloc(size_t size)
  {
    void* p = ::malloc(size);
#if defined(DEBUG)
    os::diag::trace.putString("os::malloc(");
    os::diag::trace.putDec(size);
    os::diag::trace.putString(") -> ");
    os::diag::trace.putHex(p);
    os::diag::trace.putNewLine();
#endif
    return p;
  }

  void
  free(void *ptr)
  {
#if defined(DEBUG)
    os::diag::trace.putString("os::free(");
    os::diag::trace.putHex(ptr);
    os::diag::trace.putString(")");
    os::diag::trace.putNewLine();
#endif
    return ::free(ptr);
  }
}
