//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Mutex definitions.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

#include "portable/core/include/Mutex.h"
#include "portable/core/include/Mutex.cpp.h"
#include "portable/core/include/CriticalSections.h"

namespace os
{
  namespace core
  {
    // ------------------------------------------------------------------------

    // explicit templates instantiations
    template class TGenericMutex<scheduler::CriticalSection, mutex::TNotifier<>,
        mutex::RecursivePolicy> ;
    template class TGenericMutex<scheduler::CriticalSection, mutex::TNotifier<>,
        mutex::NonRecursivePolicy> ;

  // ------------------------------------------------------------------------
  }// namespace core
} //namespace os

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
