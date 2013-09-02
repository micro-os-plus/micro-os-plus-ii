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
#include "portable/core/include/Scheduler.h"
#include "portable/core/include/Thread.h"
#include "hal/architecture/arm/cortexm/include/Cpu.h"
#include "portable/core/include/MainThread.h"
#include "portable/core/include/Stack.h"
#include "portable/core/include/CriticalSections.h"

// ----------------------------------------------------------------------------

namespace hal
{
  namespace cortexm
  {
    // ------------------------------------------------------------------------

    hal::arch::stackElement_t** ArchitectureImplementation::ms_ppStack;

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
      ms_ppStack = os::mainThread.getContext().getPPStack();

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

    void
    ArchitectureImplementation::busyWaitMicros(uint32_t micros)
    {
      while (micros--)
        {
          // TODO: make value depend on clock and optimisations
          for (int i = 20; i > 0; --i)
            {
              Cpu::nop();
            }

          resetWatchdog();
        }
    }

    void
    ArchitectureImplementation::contextSwitch(void)
    {
      // ----- begin of critical section --------------------------------------
      //os::core::scheduler::InterruptsCriticalSection cs;

      os::scheduler.prepareContextSwitchFromInterrupt();

      // update the context cache, where to save the stack pointer
      // for the next PendSV
      ms_ppStack = os::scheduler.getCurrentThread()->getContext().getPPStack();
      // ----- end of critical section ----------------------------------------
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

#if 0
        // Initialise the processor stack to the static area
        Cpu::setPSP((uint32_t)&g_mainStack[sizeof(g_mainStack)-1]);
#else
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
#endif

        // Switch to the PSP (the alternate stack)
        Cpu::setCONTROL(Cpu::getCONTROL() | 0x2);

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

      // The exception stack frame
      //
      //        {aligner}
      //        FPSCR (fp status, optional)
      //        S15 (low vfp, optional)
      //        ...
      //        S0 (low vfp, optional)
      //        xPSR (status)
      //        PC (R15)
      //        LR (R14)
      //        R12
      //        R3
      //        R2
      //        R1
      //        R0 <- SP (R13)

#if 0
      void
      PendService(void)
        {
          //hal::qemu::diag::SemiHosting::writeChar('*');
#if defined(DEBUG)
          os::diag::trace.putString("PendService()");
          os::diag::trace.putNewLine();
#endif
        }
#else
      void
      __attribute__ ((naked))
      PendService(void)
      {
#if 0
        asm volatile
        (
            "       mrs r0, psp                         \n"
        );

        ThreadContext& context __attribute__((unused))=
        (((os::core::Thread*) os::scheduler.getCurrentThread())->getContext());
#endif

        asm volatile
        (
            // Registers R0-R3 are free to use. LR = R14.
            "       mrs r0, psp                         \n"// Get the main stack in R0
            "                                           \n"
            "       ldr     r3, ppStack                 \n"// Get the address of ms_ppStack
            "       ldr     r2, [r3]                    \n"
            "                                           \n"
#if 0
            "       tst r14, #0x10                      \n" // Is the task using the FPU context?
            "       it eq                               \n"
            "       vstmdbeq r0!, {s16-s31}             \n"// If so, push high vfp registers.
#endif
            "                                           \n"
            "       stmdb r0!, {r4-r11}                 \n" // Save the core registers.
            "                                           \n"
            "       str r0, [r2]                        \n"// Save the new top of stack into the first member of the TCB.
            "                                           \n"
            "       stmdb sp!, {r3, lr}                 \n"
            "                                           \n"
            "       mov r0, %[pri]                      \n"// Disable interrupts allowed to make system calls
            "       msr basepri, r0                     \n"
            "                                           \n"
            "       bl %[csw]                           \n"// bl contextSwitch
            "                                           \n"
            "       mov r0, #0                          \n"// Setting a value of 0 will cancel masking completely,
            "       msr basepri, r0                     \n"// enabling all interrupts
            "                                           \n"
            "       ldmia sp!, {r3, lr}                 \n"
            "                                           \n"
            "       ldr r1, [r3]                        \n"// At *ms_ppStack is the new stack pointer.
            "       ldr r0, [r1]                        \n"
            "                                           \n"
            "       ldmia r0!, {r4-r11}                 \n"// Pop the core registers.
            "                                           \n"
#if 0
            "       tst r14, #0x10                      \n" // Is the task using the FPU context?
            "       it eq                               \n"
            "       vldmiaeq r0!, {s16-s31}             \n"// If so, pop the high vfp registers too.
#endif
            "                                           \n"
            "       msr psp, r0                         \n" // Restore the main stack register
            "                                           \n"
            "       bx lr                               \n"// Branch to LR (R14) to return from exception
            "                                           \n"
            "       .align 2                            \n"
            "ppStack: .word _ZN3hal7cortexm26ArchitectureImplementation10ms_ppStackE       \n"

            : /* out */
            : /* in */
            [pri] "i"(configMAX_SYSCALL_INTERRUPT_PRIORITY),
            [csw] "i"(&hal::cortexm::ArchitectureImplementation::contextSwitch)
            //[pps] "m"(&hal::cortexm::ArchitectureImplementation::ms_ppStack)
            : "memory", "cc"
        );
      }
#endif

    // ----------------------------------------------------------------------

    }
// namespace InterruptHandler

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

// ========================================================================

/// \details
/// Store the current interrupt priority (BASEPRI) in the
/// local private variable,
/// and set a the new value, supposedly higher.
    InterruptsCriticalSection::InterruptsCriticalSection(void)
    {
      // Preserve the current priority locally.
      m_basepri = Cpu::getBASEPRI();

      // Set new priority. Always increase, never decrease
      Cpu::setBASEPRI_MAX(configMAX_SYSCALL_INTERRUPT_PRIORITY);
    }

/// \details
/// Restore the interrupt priority (BASEPRI) from the
/// local private variable.
    InterruptsCriticalSection::~InterruptsCriticalSection()
    {
      // Restore the priority saved by the constructor.
      Cpu::setBASEPRI(m_basepri);
    }

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
// ========================================================================

#if defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER) || defined(__DOXYGEN__)

/// \details
    ThreadContext::ThreadContext(void)
    {
#if defined(DEBUG) && defined(OS_DEBUG_THREADCONTEXT)
      os::diag::trace.putConstructor();
#endif
      m_pStack = nullptr;
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
    ThreadContext::create(hal::arch::stackElement_t* pStackBottom,
        hal::arch::stackSize_t stackSizeBytes __attribute__((unused)),
        os::core::trampoline3_t trampolineEntryPoint, void* p1, void* p2,
        void* p3)
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

      if (pStackBottom != nullptr && stackSizeBytes != 0)
        {

          hal::arch::stackElement_t* pStack;
          pStack = pStackBottom
              + stackSizeBytes / sizeof(hal::arch::stackElement_t);

          // Place a few bytes of known values on the bottom of the stack.
          // This has no functional purpose, it is useful only for debugging.

          // The value on the right is the offset from the thread stack pointer

          // This magic should always be present here. If it is not,
          // someone else damaged the thread stack.
          *--pStack = 0x12345678;           // magic

          // To be safe, we need to align the stack frames to 8. In total
          // we have 16 words to store, so if the current address is not even,
          // descend an extra word.
          if (((int) pStack & 1) == 0)
            {
              *--pStack = 0x12345678;       // one more magic
            }

          // Simulate the Cortex-M exception stack frame, i.e. how the stack
          // would look after a call to yield().

          // Thread starts with interrupts enabled.
          // T bit set
          *--pStack = 0x01000000;           // xPSR        +15*4=64

          // The address of the trampoline code will be popped off the stack last,
          // so place it first.

          *--pStack = (hal::arch::stackElement_t) trampolineEntryPoint; // PCL     +14*4=60

          // Create the stack as if after a context save.

          *--pStack = 0x0;          // LR        +13*4=56
          *--pStack = 12;           // R12       +12*4=52

          // According to ARM ABI, first 4 word parameters are passed in R0-R3.
          // We use only 3.
          *--pStack = 3;                              // R3   +11*4=48
          *--pStack = (hal::arch::stackElement_t) p3; // R2   +10*4=44
          *--pStack = (hal::arch::stackElement_t) p2; // R1   +9*4=40
          *--pStack = (hal::arch::stackElement_t) p1; // R0   +8*4=36

          *--pStack = 11;           // R11       +7*4=32
          *--pStack = 10;           // R10       +6*4=28
          *--pStack = 9;            // R9        +5*4=24
          *--pStack = 8;            // R8        +4*4=20
          *--pStack = 7;            // R7        +3*4=16
          *--pStack = 6;            // R6        +2*4=12
          *--pStack = 5;            // R5        +1*4=8
          *--pStack = 4;            // R4        +0*4=4

          // Be sure the stack is at least large enough to hold the exception frame.
          assert(pStack > pStackBottom);

          // Store the current stack pointer in the context
          m_pStack = pStack;
        }
    }

#endif // defined(OS_INCLUDE_PORTABLE_CORE_SCHEDULER)
  // ========================================================================

  // ------------------------------------------------------------------------
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

#if 1
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

#else
  caddr_t
  _sbrk (int incr)
    {
// not yet implemented
// TODO: allocate space on heap
      return 0;
    }
#endif

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
