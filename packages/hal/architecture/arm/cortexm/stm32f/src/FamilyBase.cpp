//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F definitions of family implementation.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/include/FamilyBase.h"
#include "hal/architecture/include/FamilyImplementation.h"

namespace hal
{
  namespace stm32f
  {
  // --------------------------------------------------------------------------

  // --------------------------------------------------------------------------
  }// namespace stm32f
} // namespace hal

extern "C" void
assert_failed(unsigned char* func, int lineno);

/// \brief Assertion failed support.
/// \ingroup stm32f
///
/// \param [in]         func  A string identifying the failed condition.
/// \param [in]         lineno  The line number of the failed condition.
/// \par Returns
///    Nothing (in fact it does not return, reset is called).
///
/// \details
/// This function is called by ST code to identify the
/// place where an assertion failed.
/// Normally should not be called on release versions.
void
assert_failed(unsigned char* func __attribute__((unused)),
    int lineno __attribute__((unused)))
{
#if defined(DEBUG) || defined(__DOXYGEN__)
  os::diag::trace.putString(func);
  os::diag::trace.putString(" ");
  os::diag::trace.putDec(lineno);
  os::diag::trace.putNewLine();
#endif

  hal::cortexm::FamilyImplementation::resetSystem();
}

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F)
