//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Error.

#ifndef OS_PORTABLE_CORE_ERROR_H_
#define OS_PORTABLE_CORE_ERROR_H_

#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace core
  {
    // ========================================================================

    typedef int errorNumber_t;

    class Error
    {
    public:
      static constexpr errorNumber_t NONE = 0;
      static constexpr errorNumber_t UNKNOWN = -1;
      static constexpr errorNumber_t INTERNAL_SIZE_EXCEEDED = -2;
      static constexpr errorNumber_t RECURSION_DEPTH_EXCEEDED = -3;
      static constexpr errorNumber_t BUSY = -4;
      static constexpr errorNumber_t NOT_OWNER = -5;
      static constexpr errorNumber_t OUT_OF_SYNC = -6;
      static constexpr errorNumber_t TIMEOUT = -7;
      static constexpr errorNumber_t ATTENTION_REQUESTED = -8;

      Error(void) = default;
      ~Error() = default;

      void
      clear(void);

      Error&
      operator=(errorNumber_t error);

      bool
      operator==(errorNumber_t error);

      bool
      operator!=(errorNumber_t error);

    };

    // ========================================================================

  }// namespace core
} // namespace os

#endif // OS_PORTABLE_CORE_ERROR_H_
