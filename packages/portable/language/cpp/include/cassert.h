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
/// \brief Assert definitions.

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CASSERT_H_
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CASSERT_H_

#include "portable/core/include/ConfigDefines.h"

#undef assert

#if defined(DEBUG) || defined(__DOXYGEN__)

/// \headerfile cassert.h "portable/language/cpp/include/cassert.h"
/// \ingroup infra
///
/// \brief Assertion macro.
///
/// \param e            Boolean expression to test.
/// \retval 0           Actually non relevant.
/// \par Header
///     "portable/language/cpp/include/cassert.h"
///
/// \details
/// If the assertion evaluates to false, the program is terminated,
/// eventually with an identifying message sent to the trace device.
/// \note This macro is enabled only on debug configurations.
#define assert(e) ((void) ((e) ? 0 : (os::infra::assertFailed(__func__, __FILE__, __LINE__, #e), 0)))

namespace os
{
  namespace infra
  {
    void
    __attribute__((noreturn))
    assertFailed(const char* func, const char* file, int lineno, const char* expr);
  }
}

#else
#define assert(e) ((void)0)
#endif

#endif  // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_CASSERT_H_
