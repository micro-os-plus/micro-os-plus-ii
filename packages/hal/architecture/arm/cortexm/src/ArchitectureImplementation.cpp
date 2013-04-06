//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "../include/ArchitectureImplementation.h"

#include "portable/infrastructure/include/CStartup.h"

#include "portable/language/cpp/include/iterator.h"

namespace hal
{
  namespace arch
  {
    namespace cortexm
    {
      // ----------------------------------------------------------------------

#if defined(DEBUG)
      void
      ArchitectureImplementation::putGreeting(void)
      {
        os::diag::trace.putString("ARM Cortex M");
        os::diag::trace.putNewLine();
      }
#endif

    // ------------------------------------------------------------------------
    }
  }
}

extern "C"
{

  int
  main(void);

  void
  Reset_Handler();

  void*
  _sbrk();

  void
  __cxa_pure_virtual(void);
}

typedef unsigned int LinkerAlign_t;




class LinkerScript
{
public:
  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getBssBegin(void)
  {
    extern LinkerAlign_t __bss_start__;
    return &__bss_start__;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getBssEnd(void)
  {
    extern LinkerAlign_t __bss_end__;
    return &__bss_end__;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getFlashDataBegin(void)
  {
    // the initialised data starts at the end of the text section (in flash)
    extern LinkerAlign_t __etext;
    return &__etext;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getRamDataBegin(void)
  {
    extern LinkerAlign_t __data_start__;
    return &__data_start__;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getRamDataEnd(void)
  {
    extern LinkerAlign_t __data_end__;
    return &__data_end__;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getInitArrayStart(void)
  {
    extern LinkerAlign_t __init_array_start;
    return &__init_array_start;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getInitArrayEnd(void)
  {
    extern LinkerAlign_t __init_array_end;
    return &__init_array_end;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getFiniArrayStart(void)
  {
    extern LinkerAlign_t __fini_array_start;
    return &__fini_array_start;
  }

  inline __attribute__((always_inline))
  static LinkerAlign_t*
  getFiniArrayEnd(void)
  {
    extern LinkerAlign_t __fini_array_end;
    return &__fini_array_end;
  }


};

template class os::infra::CStartup<LinkerAlign_t>;

typedef os::infra::CStartup<LinkerAlign_t> CStartup_t;

#if defined(DEBUG)
typedef unsigned int ConstantMarker_t;

static const ConstantMarker_t CONSTANT_MARKER_MAGIC = 0x12345678;
static volatile ConstantMarker_t constantMarker = CONSTANT_MARKER_MAGIC;
#endif

void
Reset_Handler()
{

  CStartup_t::copyInitialisedData(LinkerScript::getFlashDataBegin(),
      LinkerScript::getRamDataBegin(), LinkerScript::getRamDataEnd());

  CStartup_t::clearBss(LinkerScript::getBssBegin(), LinkerScript::getBssEnd());

  CStartup_t::callStaticInitialisers(LinkerScript::getInitArrayStart(),
      LinkerScript::getInitArrayEnd());

#if defined(DEBUG)
  if (constantMarker != CONSTANT_MARKER_MAGIC)
    {
      os::diag::trace.putString("copyInitialisedData() failed");
      os::diag::trace.putNewLine();
    }
#endif

  main();

  CStartup_t::callStaticInitialisers(LinkerScript::getFiniArrayStart(),
      LinkerScript::getFiniArrayEnd());

  // TODO: soft reset to restart
  for(;;)
    ;
}

void*
_sbrk()
{
  return 0;
}

void
__cxa_pure_virtual(void)
{

}

void
operator
delete(void* p __attribute__((unused)))
{
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM)
