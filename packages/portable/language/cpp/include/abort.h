//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Declaration of system abort().

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H

namespace os
{
  namespace std
  {
    /// \brief Abort execution.
    /// \ingroup std_support
    ///
    /// \par Parameters
    ///    None.
    /// \par Returns
    ///    Never.
    void
    __attribute__((noreturn))
    abort(void);
  } // namespace std
} // namespace os

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H
