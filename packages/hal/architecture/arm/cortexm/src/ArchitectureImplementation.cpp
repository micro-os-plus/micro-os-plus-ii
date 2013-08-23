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

#include "portable/language/cpp/include/iterator.h"

#include "portable/diagnostics/include/Trace.h"

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

#if 0
  hal::arch::stackElement_t*
  ArchitectureImplementation::ThreadContext::createInitial(
      hal::arch::stackElement_t* pStackTop,
      os::core::threadEntryPoint_t entryPoint __attribute__((unused)),
      void* pParameters __attribute__((unused)))
    {
      // The value on the right is the offset from the thread stack pointer

      // Place a few bytes of known values on the bottom of the stack.
      // This is just useful for debugging.

//#define STACK_WORD_COUNT   (16+1)
      *pStackTop-- = 0x12345678;// (magic)     +16*4=68

      // Simulate how the stack would look after a call to yield()

      // Thread starts with interrupts enabled ???
      // T bit set
      *pStackTop-- = 0x01000000;// xPSR        +15*4=64

      // The start of the thread code will be popped off the stack last,
      // so place it first.

//#define STACK_PCL_WORD_OFFSET   (14)
      *pStackTop-- = (hal::arch::stackElement_t) entryPoint;// PCL     +14*4=60

      // Next simulate the stack as if after a call to Context::save().
      *pStackTop-- = 0x00;// LR        +13*4=56
      *pStackTop-- = 0x12;// R12       +12*4=52
      *pStackTop-- = 0x03;// R3        +11*4=48
      *pStackTop-- = 0x02;// R2        +10*4=44
      *pStackTop-- = 0x01;// R1        +9*4=40

//#define STACK_R0_WORD_OFFSET    (8)
      *pStackTop-- = (hal::arch::stackElement_t) pParameters;// R0     +8*4=36
      *pStackTop-- = 0x11;// R11       +7*4=32
      *pStackTop-- = 0x10;// R10       +6*4=28
      *pStackTop-- = 0x09;// R9        +5*4=24
      *pStackTop-- = 0x08;// R8        +4*4=20
      *pStackTop-- = 0x07;// R7        +3*4=16
      *pStackTop-- = 0x06;// R6        +2*4=12
      *pStackTop-- = 0x05;// R5        +1*4=8
      *pStackTop-- = 0x04;// R4        +0*4=4

      ++pStackTop;

      return pStackTop;
    }
#endif
  // --------------------------------------------------------------------------
}
}

typedef hal::cortexm::LinkerScript LinkerScript;
template class os::infra::TCppStartup<LinkerScript>;

extern int
main(void);

namespace hal
{
namespace cortexm
{
// ------------------------------------------------------------------------

typedef os::infra::TCppStartup<LinkerScript> CppStartup;

#if defined(DEBUG)
typedef unsigned int constantMarker_t;

static constexpr constantMarker_t CONSTANT_MARKER_MAGIC = 0x12345678;
static volatile constantMarker_t constantMarker = CONSTANT_MARKER_MAGIC;
#endif

namespace InterruptHandler
{
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

    // Everything should be ready, the show can start
    main();

    // Not usual in embedded environments, but if the application
    // terminates gracefully, run the destructors.
    // The last destructor (~EarlyInitialisations()) should
    // call os::platform::resetSystem().
    CppStartup::callStaticDestructors();

#if defined(DEBUG)

    // normally should not reach this
    os::diag::trace.putString("looping after main()");
    os::diag::trace.putNewLine();

#endif
    for (;;)
      ;
  }
} // namespace InterruptHandler

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

// ========================================================================

/// \details
/// Store the current signal status in the local private variable,
/// and block the signal used by the ticks timer.
InterruptsCriticalSection::InterruptsCriticalSection(void)
{
}

/// \details
/// Restore the signal status from the local private variable.
InterruptsCriticalSection::~InterruptsCriticalSection()
{
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
// ========================================================================

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

/// \details
ThreadContext::ThreadContext(void)
{
}

ThreadContext::~ThreadContext()
{
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
  os::diag::trace.putDestructor();
#endif
}

/// \details
/// The trampolineEntryPoint is pointing to the thread trampoline,
/// a small routine used to gain control after the thread main code
/// terminates.
void
ThreadContext::create(
    hal::arch::stackElement_t* pStackBottom __attribute__((unused)),
    hal::arch::stackSize_t stackSizeBytes __attribute__((unused)),
    os::core::trampoline3_t trampolineEntryPoint __attribute__((unused)),
    void* p1 __attribute__((unused)), void* p2 __attribute__((unused)),
    void* p3 __attribute__((unused)))
{
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
  os::diag::trace.putString("ThreadContext::create()");
  os::diag::trace.putString(" stack=");
  os::diag::trace.putHex((void*) pStackBottom);
  os::diag::trace.putString("-");
  os::diag::trace.putHex(
      (void*) (pStackBottom
          + stackSizeBytes / sizeof(hal::arch::stackElement_t)));
  os::diag::trace.putString(", size=");
  os::diag::trace.putDec(stackSizeBytes);
  os::diag::trace.putString(", entry=");
  os::diag::trace.putHex((void*) trampolineEntryPoint);
  os::diag::trace.putString(", p1=");
  os::diag::trace.putHex(p1);
  os::diag::trace.putString(", p2=");
  os::diag::trace.putHex(p2);
  os::diag::trace.putString(", p3=");
  os::diag::trace.putHex(p3);
  os::diag::trace.putNewLine();
#endif

  return;
}

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  // ========================================================================

  // ------------------------------------------------------------------------
} // namespace cortexm
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
void*
_sbrk();

void
__cxa_pure_virtual(void);

void*
_sbrk()
{
// not yet implemented
// TODO: allocate space on heap
return 0;
}

void
__cxa_pure_virtual(void)
{
// not yet implemented
// TODO: trace message and restart
}
}

void
operator
delete(void* p __attribute__((unused)))
{
    // not yet implemented
}

// ----------------------------------------------------------------------------

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
