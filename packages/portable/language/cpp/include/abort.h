//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Declaration of system abort().

#ifndef OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H
#define OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H

extern "C"
{
  void
  __attribute__((noreturn))
  abort(void);
}

#endif // OS_PORTABLE_LANGUAGE_CPP_INCLUDE_ABORT_H
