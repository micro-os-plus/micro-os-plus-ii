//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Cortex-M CPU definitions.

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_CPU_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_CPU_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M) || defined(__DOXYGEN__)

// Include architecture definitions, like various types.
#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"

#include "portable/language/cpp/include/cstdint.h"

namespace hal
{
  namespace cortexm
  {
    // ========================================================================

    class Cpu
    {
    public:
      Cpu(void) = delete;

      /// \brief  No operation
      static void
      nop(void);

      /// \brief  Enable Interrupts
      static void
      enableInterrupts(void);

      /// \brief  Disable Interrupts
      static void
      disableInterrupts(void);

      /// \brief  Get Control Register
      /// \return               Control Register value
      static uint32_t
      getCONTROL(void);

      /// \brief  Set Control Register
      /// \param [in]    control  Control Register value to set
      static void
      setCONTROL(uint32_t control);

      /// \brief  Get IPSR Register
      /// \return               IPSR Register value
      static uint32_t
      __get_IPSR(void);

      /// \brief  Get APSR Register
      /// \return               APSR Register value
      static uint32_t
      __get_APSR(void);

      /// \brief  Get xPSR Register
      /// \return               xPSR Register value
      static uint32_t
      __get_xPSR(void);

      /// \brief  Get Process Stack Pointer
      /// \return               PSP Register value
      static uint32_t
      getPSP(void);

      /// \brief  Set Process Stack Pointer
      /// \param [in]    topOfProcStack  Process Stack Pointer value to set
      static void
      setPSP(uint32_t topOfProcStack);

      /// \brief  Get Main Stack Pointer
      /// \return               MSP Register value
      static uint32_t
      __get_MSP(void);

      /// \brief  Set Main Stack Pointer
      /// \param [in]    topOfMainStack  Main Stack Pointer value to set
      static void
      __set_MSP(uint32_t topOfMainStack);

      /// \brief  Get Priority Mask
      /// \return               Priority Mask value
      static uint32_t
      __get_PRIMASK(void);

      /// \brief  Set Priority Mask
      /// \param [in]    priMask  Priority Mask
      static void
      __set_PRIMASK(uint32_t priMask);

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(__DOXYGEN__)

      /// \brief  Enable Fault Interrupt
      static void
      __enable_fault_irq(void);

      /// \brief  Disable Fault Interrupt
      static void
      __disable_fault_irq(void);

      /// \brief  Get Base Priority
      /// \return               Base Priority register value
      static uint32_t
      getBASEPRI(void);

      /// \brief  Set Base Priority
      /// \param [in]    basePri  Base Priority value to set
      static void
      setBASEPRI(uint32_t value);

      /// \brief  Set Base Priority Max
      /// \param [in]    basePri  Base Priority value to set
      static void
      setBASEPRI_MAX(uint32_t value);

      /// \brief  Get Fault Mask
      /// \return               Fault Mask register value
      static uint32_t
      __get_FAULTMASK(void);

      /// \brief  Set Fault Mask
      /// \param [in]    faultMask  Fault Mask value to set
      static void
      __set_FAULTMASK(uint32_t faultMask);

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3)
#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4) || defined(__DOXYGEN__)

      /// \brief  Get FPSCR
      /// \return               Floating Point Status/Control register value
      static uint32_t __get_FPSCR(void);

      /// \brief  Set FPSCR
      /// \param [in]    fpscr  Floating Point Status/Control value to set
      static void __set_FPSCR(uint32_t fpscr);
#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)
    };

    // ------------------------------------------------------------------------

#pragma GCC diagnostic push
// prevent "error: always_inline function might not be inlinable"
#pragma GCC diagnostic ignored "-Wattributes"

    /// \detail
    /// This function executes a NOP.
    inline void
    __attribute__((always_inline))
    Cpu::nop(void)
    {
      asm volatile
      (
          " nop       \n"

          : // no output
          :// no input
          :// no clobber
      );
    }

    /// \detail
    /// This function enables interrupts by setting the I-bit (PRIMASK)
    /// in the CPSR.
    ///
    /// \note Can only be executed in Privileged modes.
    inline void
    __attribute__((always_inline))
    Cpu::enableInterrupts(void)
    {
      asm volatile
      (
          " cpsie i       \n"

          : // no output
          :// no input
          :// no clobber
      );
    }

    /// \detail
    /// The PRIMASK register is used to disable all exceptions except NMI
    /// and hard fault. It effectively changes the current priority level
    /// to 0 (highest programmable level).
    ///
    /// PRIMASK is useful for temporarily disabling all interrupts for
    /// critical tasks. When PRIMASK is set, if a fault takes place,
    /// the hard fault handler will be executed.
    ///
    /// \note Can only be executed in Privileged modes.
    inline void
    __attribute__((always_inline))
    Cpu::disableInterrupts(void)
    {
      asm volatile
      (
          " cpsid i       \n"

          : // no output
          :// no input
          :// no clobber
      );
    }

    /// \detail
    /// This function returns the content of the Control Register.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::getCONTROL(void)
    {
      uint32_t result;

      asm volatile
      (
          " mrs %0, control       \n"

          : "=r" (result)
          : // no input
          :// no clobber
      );
      return (result);
    }

    /// \detail
    /// This function writes the given value to the Control Register.
    inline void
    __attribute__((always_inline))
    Cpu::setCONTROL(uint32_t control)
    {
      asm volatile
      (
          " msr control, %0       \n"

          : // no output
          : "r" (control)// input
          :// no clobber
      );
    }

    /// \detail
    /// This function returns the content of the IPSR Register.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_IPSR(void)
    {
      uint32_t result;

      asm volatile
      (
          " mrs %0, ipsr       \n"

          : "=r" (result) // output
          :// no input
          :// no clobber
      );
      return (result);
    }

    /// \detail
    /// This function returns the content of the APSR Register.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_APSR(void)
    {
      uint32_t result;

      asm volatile (" mrs %0, apsr       \n" : "=r" (result) );
      return (result);
    }

    /// \detail
    /// This function returns the content of the xPSR Register.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_xPSR(void)
    {
      uint32_t result;

      asm volatile (" mrs %0, xpsr       \n" : "=r" (result) );
      return (result);
    }

    /// \detail
    /// This function returns the current value of the Process Stack Pointer (PSP).
    inline uint32_t
    __attribute__((always_inline))
    Cpu::getPSP(void)
    {
      register uint32_t result;

      asm volatile
      (
          " mrs %0, psp       \n"

          : "=r" (result) // output
          :// no input
          :// no clobber
      );
      return (result);
    }

    /// \detail
    /// This function assigns the given value to the Process Stack Pointer (PSP).
    inline void
    __attribute__((always_inline))
    Cpu::setPSP(uint32_t topOfProcStack)
    {
      asm volatile
      (
          " msr psp, %0       \n"

          : // no output
          : "r" (topOfProcStack)// input
          :// no clobber
      );
    }

    /// \detail
    /// This function returns the current value of the Main Stack Pointer (MSP).
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_MSP(void)
    {
      register uint32_t result;

      asm volatile (" mrs %0, msp       \n" : "=r" (result) );
      return (result);
    }

    /// \detail
    /// This function assigns the given value to the Main Stack Pointer (MSP).
    inline void
    __attribute__((always_inline))
    Cpu::__set_MSP(uint32_t topOfMainStack)
    {
      asm volatile (" msr msp, %0       \n" : : "r" (topOfMainStack) );
    }

    /// \detail
    /// This function returns the current state of the priority mask bit
    /// from the Priority Mask Register.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_PRIMASK(void)
    {
      uint32_t result;

      asm volatile (" mrs %0, primask       \n" : "=r" (result) );
      return (result);
    }

    /// \detail
    /// This function assigns the given value to the Priority Mask Register.
    inline void
    __attribute__((always_inline))
    Cpu::__set_PRIMASK(uint32_t priMask)
    {
      asm volatile (" msr primask, %0       \n" : : "r" (priMask) );
    }

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3) || defined(__DOXYGEN__)

    /// \detail
    /// This function enables FAULTMASK interrupts by clearing the F-bit in the CPSR.
    ///
    /// \note Can only be executed in Privileged modes.
    ///
    /// \note Cortex-M3 specific.
    inline void
    __attribute__((always_inline))
    Cpu::__enable_fault_irq(void)
    {
      asm volatile (" cpsie f       \n");
    }

    /// \detail
    /// This function disables FAULTMASK interrupts by setting the F-bit in the CPSR.
    ///
    /// \note Can only be executed in Privileged modes.
    ///
    /// \note Cortex-M3 specific.
    inline void
    __attribute__((always_inline))
    Cpu::__disable_fault_irq(void)
    {
      asm volatile (" cpsid f       \n");
    }

    /// \detail
    /// This function returns the current value of the Base Priority register.
    ///
    /// \note Cortex-M3 specific.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::getBASEPRI(void)
    {
      uint32_t result;

      asm volatile
      (
          " mrs %[R], basepri_max       \n"

          : [R]"=r" (result) //
          :
          :
      );
      return (result);
    }

    /// \detail
    /// Disable interrupts with priority lower than a certain level.
    ///
    /// As with other priority-level registers, the formatting of the
    /// BASEPRI register is affected by the number of implemented
    /// priority register widths. For example, if only 3 bits are
    /// implemented for priority-level registers, BASEPRI can be
    /// programmed as 0x00, 0x20, 0x40 ... 0xC0, and 0xE0.
    ///
    /// Setting a value of 0 will cancel masking completely, enabling
    /// all interrupts.
    ///
    /// \note Cortex-M3 specific.
    inline void
    __attribute__((always_inline))
    Cpu::setBASEPRI(uint32_t value)
    {
      asm volatile
      (
          " msr basepri, %[R]       \n"

          :
          : [R]"r" (value) // input
          :
      );
    }

    /// \detail
    /// Conditionally disable interrupts with priority lower than a
    /// certain level. The processor hardware automatically compares
    /// the current value and the new value and only allows the update
    /// if it is to be changed to a higher priority level; it cannot
    /// be changed to lower priority levels.
    ///
    /// Setting a value of 0 will cancel masking completely, enabling
    /// all interrupts.
    ///
    /// \note Cortex-M3 specific.
    inline void
    __attribute__((always_inline))
    Cpu::setBASEPRI_MAX(uint32_t value)
    {
      asm volatile
      (
          " msr basepri_max, %[R]       \n"

          :
          : [R]"r" (value) // input
          :
      );
    }

    /// \detail
    /// This function returns the current value of the Fault Mask register.
    ///
    /// \note Cortex-M3 specific.
    inline uint32_t
    __attribute__((always_inline))
    Cpu::__get_FAULTMASK(void)
    {
      uint32_t result;

      asm volatile (" mrs %0, faultmask       \n" : "=r" (result) );
      return (result);
    }

    /// \detail
    /// This function assigns the given value to the Fault Mask register.
    ///
    /// \note Cortex-M3 specific.
    inline void
    __attribute__((always_inline))
    Cpu::__set_FAULTMASK(uint32_t faultMask)
    {
      asm volatile (" msr faultmask, %0       \n" : : "r" (faultMask) );
    }

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3)
#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4) || defined(__DOXYGEN__)

  /// \detail
  /// This function returns the current value of the Floating Point
  /// Status/Control register.
  ///
  /// \note Cortex-M4 specific.
  inline uint32_t
  __attribute__((always_inline))
  Cpu::__get_FPSCR(void)
    {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
      uint32_t result;

      asm volatile (" vmrs %0, fpscr       \n" : "=r" (result) );
      return(result);
#else
      return(0);
#endif
    }

  /// \detail
  /// This function assigns the given value to the Floating Point
  /// Status/Control register.
  ///
  /// \note Cortex-M4 specific.
  inline void
  __attribute__((always_inline))
  Cpu::__set_FPSCR(uint32_t fpscr __attribute__((unused)))
    {
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
      asm volatile (" vmsr fpscr, %0       \n" : : "r" (fpscr) );
#endif
    }

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4)
#pragma GCC diagnostic pop

  // ==========================================================================

}
  // namespace cortexm
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_CPU_H_
