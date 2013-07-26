#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H

#include "portable/core/include/ConfigDefines.h"

#include <stdint.h>
#include <stddef.h>

namespace os
{

  void*
  malloc(size_t size);

  void
  free(void *ptr);
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_MALLOC_H
