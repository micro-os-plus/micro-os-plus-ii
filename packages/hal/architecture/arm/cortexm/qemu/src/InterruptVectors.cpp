//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief QEMU array of interrupt vectors.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_QEMU) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"

#include "portable/core/include/Platform.h"

// Since weak references can point only to symbols defined in the
// same compilation unit, we bring all pieces that form the
// interrupt vectors together here.
// The order should not be a problem, since each piece goes to a specific
// linker section.
#include "hal/architecture/arm/cortexm/cortexm3/include/InterruptVectors.cpp.h"

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD)
