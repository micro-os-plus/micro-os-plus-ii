//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M implementation of architecture class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

//#include "portable/core/include/OS.h"

#include "portable/core/include/Platform.h"
#include "hal/architecture/arm/cortexm/include/ArchitectureImplementation.h"
#include "portable/infrastructure/include/CppStartup.h"
#include "hal/architecture/arm/cortexm/ldscripts/LinkerScript.h"
//#include "portable/language/cpp/include/iterator.h"
#include "portable/diagnostics/include/Trace.h"
//#include "portable/core/include/Scheduler.h"
//#include "portable/core/include/Thread.h"
#include "hal/architecture/arm/cortexm/include/Cpu.h"
#include "portable/core/include/MainThread.h"
//#include "portable/core/include/Stack.h"
//#include "portable/core/include/CriticalSections.h"

// ----------------------------------------------------------------------------

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

#if defined(DEBUG) || defined(__DOXYGEN__)
    void
    ArchitectureImplementation::putGreeting(void)
    {
      os::diag::trace.putString("ARM Cortex M");
      os::diag::trace.putNewLine();
    }
#endif

    void
    ArchitectureImplementation::initialiseScheduler(void)
    {
#if defined(DEBUG)
      os::diag::trace.putString(__PRETTY_FUNCTION__);
      os::diag::trace.putNewLine();
#endif
      // The first context switch will be executed within the context
      // of the main thread, so the first time when the context is saved
      // onto the stack, the cached pointer shall be initialised with
      // the main thread context.
      ThreadContext::ms_ppStack = os::mainThread.getContext().getPPStack();

      // Make PendSV the lowest priority interrupts (same for SysTick)
      // portNVIC_SYSPRI2_REG |= portNVIC_PENDSV_PRI;
      (*((volatile unsigned long *) 0xe000ed20)) |=
          (((unsigned long) configKERNEL_INTERRUPT_PRIORITY) << 16UL );

      // Disable base priority (allow all interrupts).
      Cpu::setBASEPRI(0);

      // Set the master interrupts enable bit.
      Cpu::enableInterrupts();
    }

    void
    ArchitectureImplementation::resetWatchdog(void)
    {
      // TODO: implement
    }

#define BUSY_LOOPS 5

    void
    ArchitectureImplementation::busyWaitMicros(uint32_t micros)
    {
      while (micros--)
        {
#if 1
          // TODO: make value depend on clock and optimisations
          for (int i = BUSY_LOOPS; i > 0; --i)
            {
              Cpu::nop();
            }
#endif
          resetWatchdog();
        }
    }

  // --------------------------------------------------------------------------
  }
}

typedef hal::cortexm::LinkerScript LinkerScript;
template class os::infra::TCppStartup<LinkerScript>;

//static char g_mainStack[1024];

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    using CppStartup = os::infra::TCppStartup<LinkerScript>;

#if defined(DEBUG)
    typedef unsigned int constantMarker_t;

    static constexpr constantMarker_t CONSTANT_MARKER_MAGIC = 0x12345678;
    static volatile constantMarker_t constantMarker = CONSTANT_MARKER_MAGIC;
#endif

    namespace InterruptHandler
    {
      // ----------------------------------------------------------------------

      /// \ingroup arm_cm3_irq
      /// \details
      /// All ARM Cortex-M architectures jump to this the entry point
      /// via the pointer located in the second word of the interrupt
      /// table for reset events.
      ///
      /// This function starts with the reset settings, i.e. low speed and
      /// peripherals disabled, and will later initialise the
      /// hardware for a higher frequency.
      void
      Reset(void)
      {
        CppStartup::initialiseDataAndBss();

        // The os::platform::initialiseSystem() will be called
        // by the first constructor (EarlyInitialisations())
        CppStartup::callStaticConstructors();

#if defined(DEBUG)
        // Trace is available only after first constructors are called,
        // do not move this from here.
        if (constantMarker != CONSTANT_MARKER_MAGIC)
          {
            os::diag::trace.putString("copyInitialisedData() failed");
            os::diag::trace.putNewLine();
          }
#endif

        // early call, used to avoid further context creation
        os::mainThread.start();

        os::core::stack::element_t* pspStack =
            os::mainThread.getStack().getTopAligned(8);

#if defined(DEBUG)

        // normally should not reach this
        os::diag::trace.putString("switching to PSP=");
        os::diag::trace.putHex(pspStack);
        os::diag::trace.putNewLine();

#endif

        Cpu::setPSP((uint32_t) pspStack);

        // Switch to the PSP (the alternate stack)
        Cpu::setCONTROL(Cpu::getCONTROL() | 0x2);

#if defined(DEBUG)
        // One extra empty line, to find main() easily
        os::diag::trace.putNewLine();
#endif

        // Everything should be ready, the show can start
        os::platform.executeMain();

        // Not usual in embedded environments, but if the application
        // terminates gracefully, run the destructors.

        // The last destructor (~EarlyInitialisations()) should
        // call os::platform::exit() to reset the system.
        CppStartup::callStaticDestructors();

#if defined(DEBUG)

        // normally should not reach this
        os::diag::trace.putString("looping after main()");
        os::diag::trace.putNewLine();

#endif
        for (;;)
          ;
      }

    // ----------------------------------------------------------------------

    }// namespace InterruptHandler

  // ========================================================================

  }// namespace cortexm
} // namespace hal

// ----------------------------------------------------------------------------

/// \brief C alias of the C++ reset handler.
///
/// \details
/// This definition is useful for allowing the debugger to stop
/// right at the beginning of the program. Since we make extensive use
/// of namespaces, it would be complicated to enter the long name
/// into the GDB configuration, and it is easier to use this alias.
extern "C" void
Reset_Handler(void)
    __attribute__((alias("_ZN3hal7cortexm16InterruptHandler5ResetEv")));

// ----------------------------------------------------------------------------
// Patches to make the code compile.
// Probably will be further refined.

extern "C"
{
  caddr_t
  _sbrk(int incr);

  void
  __cxa_pure_virtual(void);
} // end of "C"

caddr_t
_sbrk(int incr)
{
  extern char end asm ("end"); /* Defined by the linker.  */
  static char * heap_end;
  char * prev_heap_end;

  if (heap_end == NULL)
    heap_end = &end;

  prev_heap_end = heap_end;

#if 0
  if (heap_end + incr > stack_ptr)
    {
      /* Some of the libstdc++-v3 tests rely upon detecting
       out of memory errors, so do not abort here.  */
#if 0
      extern void abort (void);

      _write (1, "_sbrk: Heap and stack collision\n", 32);

      abort ();
#else
      errno = ENOMEM;
      return (caddr_t) -1;
#endif
    }
#endif

  heap_end += incr;

  return (caddr_t) prev_heap_end;
}

void
__cxa_pure_virtual(void)
{
#if defined(DEBUG)

  // normally should not reach this
  os::diag::trace.putString("pure virtual called");
  os::diag::trace.putNewLine();

#endif

  os::std::abort();
}

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
