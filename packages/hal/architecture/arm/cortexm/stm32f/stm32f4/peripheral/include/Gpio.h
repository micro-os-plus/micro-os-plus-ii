//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 GPIO high level classes.
///
/// \example hal/architecture/arm/cortexm/tests/src/gpio.cpp

#ifndef HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
#define HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/include/ArchitectureDefinitions.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/GpioDefinitions.h"

#include "hal/architecture/arm/cortexm/peripheral/include/BitBand.h"

namespace hal
{
  namespace stm32f4
  {
    // ========================================================================

    /// \headerfile Gpio.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Gpio.h"
    /// \ingroup stm32f4_gpio
    /// \nosubgrouping
    ///
    /// \brief GPIO pin class template (static version).
    ///
    /// \details
    /// This class template provides full control of a STM32F4 GPIO pin.
    /// It is intended for most common cases when both the port number
    /// and the bit number are constants known at compile time.
    ///
    /// For performance reasons, all member functions are inline and very
    /// simple, performing just the required memory access(es).
    ///
    /// Using it is typical for static classes, although a default
    /// constructor is provided, so you can instantiate it as well.
    ///
    /// \code{.cpp}
    /// template class hal::stm32f4::TGpioPin<XPORT, XBIT>;
    /// typedef class hal::stm32f4::TGpioPin<XPORT, XBIT> XGPIO;
    ///
    /// XGPIO::setPinHigh();
    /// \endcode

    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      class TGpioPin
      {
      public:
        /// \name Constructors/destructor
        /// @{

        /// \brief Construct a GPIO pin object.
        ///
        /// \par Parameters
        ///    None.
        TGpioPin() = default;

        /// @} end of name Constructors/destructor

        // ----- Configuration functions ----------------------------------------
        /// \name Configuration functions
        /// @{

        /// \brief Configure the mode bits.
        ///
        /// \param [in] value An enumeration value with the mode.
        /// \par Returns
        ///    Nothing.
        static void
        configureMode(gpio::Mode value);

        /// \brief Retrieve the mode bits.
        ///
        /// \par Parameters
        ///    None.
        /// \return An enumeration value with the current pin mode.
        static gpio::Mode
        retrieveMode(void);

        /// \brief Configure the output type bits.
        ///
        /// \param [in] value An enumeration value with the output type.
        /// \par Returns
        ///    Nothing.
        static void
        configureOutputType(gpio::OutputType value);

        /// \brief Retrieve the output type bits.
        ///
        /// \par Parameters
        ///    None.
        /// \return An enumeration value with the current output type.
        static gpio::OutputType
        retrieveOutputType(void);

        /// \brief Configure the output speed bits.
        ///
        /// \param [in] value An enumeration value with the output speed.
        /// \par Returns
        ///    Nothing.
        static void
        configureOutputSpeed(gpio::OutputSpeed value);

        /// \brief Retrieve the output speed bits.
        ///
        /// \par Parameters
        ///    None.
        /// \return An enumeration value with the current output speed.
        static gpio::OutputSpeed
        retrieveOutputSpeed(void);

        /// \brief Configure the pull-up/pull-down bits.
        ///
        /// \param [in] value An enumeration value with the pull-up/pull-down resistors.
        /// \par Returns
        ///    Nothing.
        static void
        configurePullUpPullDown(gpio::Resistors value);

        /// \brief Retrieve the pull-up/pull-down bits.
        ///
        /// \par Parameters
        ///    None.
        /// \return An enumeration value with the current pull-up/pull-down resistors.
        static gpio::Resistors
        retrievePullUpPullDown(void);

        /// \brief Configure the alternate function bits.
        ///
        /// \param [in] value An enumeration value with the alternate function.
        /// \par Returns
        ///    Nothing.
        static void
        configureAlternateFunction(gpio::AlternateFunction value);

        /// \brief Retrieve the alternate function bits.
        ///
        /// \par Parameters
        ///    None.
        /// \return An enumeration value with the current pull-up/pull-down resistors.
        static gpio::AlternateFunction
        retrieveAlternateFunction(void);

        // TODO: add configure lock

        /// @} end of name Configuration functions

        // ----- Pin member functions -------------------------------------------
        /// \name Pin member functions
        /// @{

        /// \brief Set the pin level to high.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        setPinHigh(void);

        /// \brief Set the pin level to low.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        setPinLow(void);

        /// \brief Toggle the pin level.
        ///
        /// \par Parameters
        ///    None.
        /// \par Returns
        ///    Nothing.
        static void
        togglePin(void);

        /// \brief Check if the pin level is high.
        ///
        /// \par Parameters
        ///    None.
        /// \return True if the pin level is high.
        static bool
        isPinHigh(void);

        /// \brief Check if the pin level is low.
        ///
        /// \par Parameters
        ///    None.
        /// \return True if the pin level is low.
        static bool
        isPinLow(void);

        /// \brief Read the pin level.
        ///
        /// \par Parameters
        ///    None.
        /// \retval 1 The pin level is high.
        /// \retval 0 The pin level is low.
        static gpio::bitValue_t
        readPin(void);

        /// @} end of name Pin member functions

      private:
        /// \name Private members
        /// @{

        /// \brief The port number, as given when instantiating the template.
        static const gpio::portNumber_t m_portNumber = Port_T;

        /// \brief The address of the port hardware registers.
        ///
        /// \details
        /// This value is computed based on the
        /// peripheral base address, the port number and the port offset.
        /// For convenient access, it is represented as a reference.
        static constexpr gpio::PortRegisters& m_portRegisters =
            *reinterpret_cast<gpio::PortRegisters*>(gpio::PortRegisters::MEMORY_BASE
                + (m_portNumber * gpio::PortRegisters::MEMORY_OFFSET));

        /// \brief The bit number, as given when instantiating the template.
        static const gpio::bitNumber_t m_bitNumber = Bit_T;

        /// \brief The single bit mask, corresponding to the bit number.
        ///
        /// \details
        /// This value is
        /// intentionally 16-bit, to trigger an error if m_bitNumber>16.
        static constexpr gpio::reg16_t m_bitMask = (1 << m_bitNumber);

        /// @} end of name Private members
      };

    // ------------------------------------------------------------------------

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::configureMode(gpio::Mode value)
      {
        gpio::reg32_t current = m_portRegisters.readMode();
        current &= ~(gpio::MODE_MASK << (2 * m_bitNumber));

        gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
        newValue &= gpio::MODE_MASK;
        newValue <<= (2 * m_bitNumber);
        newValue |= current;

        m_portRegisters.writeMode(newValue);
      }

    /// \details
    /// Read the register and return the 2 configuration bits.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::Mode
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::retrieveMode(void)
      {
        gpio::reg32_t current = m_portRegisters.readMode();
        current >>= (2 * m_bitNumber);
        current &= gpio::MODE_MASK;

        return static_cast<gpio::Mode>(current);
      }

    /// \details
    /// Use bit-banding to write the single configuration bit.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::configureOutputType(gpio::OutputType value)
      {
        gpio::bitValue_t newValue = static_cast<gpio::reg32_t>(value);

        hal::cortexm::BitBand::writePeripheralBitValue(&m_portRegisters.otyper,
            m_bitNumber, newValue);
      }

    /// \details
    /// Use bit-banding to read the single configuration bit and return it.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::OutputType
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::retrieveOutputType(void)
      {
        return static_cast<gpio::OutputType>(hal::cortexm::BitBand::readPeripheralBitValue(
            &m_portRegisters.otyper, m_bitNumber));
      }

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::configureOutputSpeed(gpio::OutputSpeed value)
      {
        gpio::reg32_t current = m_portRegisters.readOutputSpeed();
        current &= ~(gpio::OUTPUT_SPEED_MASK << (2 * m_bitNumber));

        gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
        newValue &= gpio::OUTPUT_SPEED_MASK;
        newValue <<= (2 * m_bitNumber);
        newValue |= current;

        m_portRegisters.writeOutputSpeed(newValue);
      }

    /// \details
    /// Read the register and return the 2 configuration bits.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::OutputSpeed
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::retrieveOutputSpeed(void)
      {
        gpio::reg32_t current = m_portRegisters.readOutputSpeed();
        current >>= (2 * m_bitNumber);
        current &= gpio::OUTPUT_SPEED_MASK;

        return static_cast<gpio::OutputSpeed>(current);
      }

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::configurePullUpPullDown(gpio::Resistors value)
      {
        gpio::reg32_t current = m_portRegisters.readPullUpPullDown();
        current &= ~(gpio::RESISTORS_MASK << (2 * m_bitNumber));

        gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
        newValue &= gpio::RESISTORS_MASK;
        newValue <<= (2 * m_bitNumber);
        newValue |= current;

        m_portRegisters.writePullUpPullDown(newValue);
      }

    /// \details
    /// Read the register and return the 2 configuration bits.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::Resistors
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::retrievePullUpPullDown(void)
      {
        gpio::reg32_t current = m_portRegisters.readPullUpPullDown();
        current >>= (2 * m_bitNumber);
        current &= gpio::RESISTORS_MASK;

        return static_cast<gpio::Resistors>(current);
      }

    /// \details
    /// Use read/modify/write to change the 4 configuration bits.
    /// The AFR registers are organised as an array of two words.
    /// Bits corresponding to pins 0-7 are stored in the first word,
    /// bits corresponding to pins 8-15 in the second word.
    /// \warning Non atomic, the caller must use critical sections.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::configureAlternateFunction(
          gpio::AlternateFunction value)
      {
        gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);

        // All computations are done by the compiler, so divisions
        // are accepted.
        gpio::index_t index = (m_bitNumber / 8);
        gpio::bitNumber_t bitNumber = (m_bitNumber % 8);

        gpio::reg32_t current = m_portRegisters.readAlternateFunction(index);
        current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * bitNumber));

        newValue &= gpio::ALTERNATE_FUNCTION_MASK;
        newValue <<= (4 * bitNumber);
        newValue |= current;

        m_portRegisters.writeAlternateFunction(index, newValue);

      }

    /// \details
    /// Read the register and return the 4 configuration bits.
    /// The AFR registers are organised as an array of two words.
    /// Bits corresponding to pins 0-7 are stored in the first word,
    /// bits corresponding to pins 8-15 in the second word.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::AlternateFunction
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::retrieveAlternateFunction(void)
      {
        // All computations are done by the compiler, so divisions
        // are accepted.
        gpio::index_t const index = (m_bitNumber / 8);
        gpio::bitNumber_t const bitNumber = (m_bitNumber % 8);

        gpio::reg32_t current = m_portRegisters.readAlternateFunction(index);
        current >>= (4 * bitNumber);
        current &= gpio::ALTERNATE_FUNCTION_MASK;

        return static_cast<gpio::AlternateFunction>(current);
      }

    // ------------------------------------------------------------------------

    /// \details
    /// Use the lower half of the special BSSR register to set the pin high.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::setPinHigh(void)
      {
        m_portRegisters.writeSetReset(static_cast<gpio::reg32_t>(m_bitMask));
      }

    /// \details
    /// Use the upper half of the special BSSR register to set the pin low.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::setPinLow(void)
      {
        // write to the upper half
        m_portRegisters.writeSetReset(
            static_cast<gpio::reg32_t>(m_bitMask) << 16);
      }

    /// \details
    /// Use bit-banding to read the corresponding ODR bit,
    /// reverse its value and write it back.
    /// \warning Non atomic, the caller must use critical sections.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline void
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::togglePin(void)
      {
        gpio::bitValue_t oldValue =
            hal::cortexm::BitBand::readPeripheralBitValue(&m_portRegisters.odr,
                m_bitNumber);

        gpio::bitValue_t newValue = ~oldValue;
        hal::cortexm::BitBand::writePeripheralBitValue(&m_portRegisters.odr,
            m_bitNumber, newValue);
      }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and test it.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline bool
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::isPinHigh(void)
      {
        return (hal::cortexm::BitBand::readPeripheralBitValue(
            &m_portRegisters.idr, m_bitNumber) != 0);
      }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and test it.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline bool
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::isPinLow(void)
      {
        return (hal::cortexm::BitBand::readPeripheralBitValue(
            &m_portRegisters.idr, m_bitNumber) == 0);
      }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and return it.
    template<gpio::portNumber_t Port_T, gpio::bitNumber_t Bit_T>
      inline gpio::bitValue_t
      __attribute__((always_inline))
      TGpioPin<Port_T, Bit_T>::readPin(void)
      {
        return hal::cortexm::BitBand::readPeripheralBitValue(
            &m_portRegisters.idr, m_bitNumber);
      }

    // ========================================================================

    /// \headerfile Gpio.h "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Gpio.h"
    /// \ingroup stm32f4_gpio
    /// \nosubgrouping
    ///
    /// \brief GPIO pin class (full version).
    ///
    /// \details
    /// This class provides full control of a STM32F4 GPIO pin. It is
    /// intended for the rare cases when the port number or the bit
    /// number are not known at compile time.
    ///
    /// For performance reasons, all member functions are inline and very
    /// simple, performing just the required memory access(es).
    class GpioPin
    {
    public:
      /// \name Constructors/destructor
      /// @{

      /// \brief Construct a GPIO pin object.
      ///
      /// \param [in] portNumber An integer, the port number, starting from 0 for port 'A'.
      /// \param [in] bitNumber An integer, the bit number (0-15).
      GpioPin(const gpio::portNumber_t portNumber,
          const gpio::bitNumber_t bitNumber);

      /// @} end of name Constructors/destructor

      // ----- Getters --------------------------------------------------------
      /// \name Getters
      /// @{

      /// \brief Get a reference to the port registers.
      ///
      /// \par Parameters
      ///    None.
      /// \return A reference to the port registers.
      gpio::PortRegisters&
      getPortRegisters(void);

      /// \brief Get the bit number used in the constructor.
      ///
      /// \par Parameters
      ///    None.
      /// \return An integer with the bit number (0-15).
      gpio::bitNumber_t
      getBitNumber(void);

      /// \brief Get the port number used in the constructor.
      ///
      /// \par Parameters
      ///    None.
      /// \return An integer with the port number (0='A', ...).
      gpio::portNumber_t
      getPortNumber(void);

      /// @} end of name Getters

      // ----- Configuration functions ----------------------------------------
      /// \name Configuration functions
      /// @{

      /// \brief Configure the mode bits.
      ///
      /// \param [in] value An enumeration value with the mode.
      /// \par Returns
      ///    Nothing.
      void
      configureMode(gpio::Mode value);

      /// \brief Retrieve the mode bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pin mode.
      gpio::Mode
      retrieveMode(void);

      /// \brief Configure the output type bits.
      ///
      /// \param [in] value An enumeration value with the output type.
      /// \par Returns
      ///    Nothing.
      void
      configureOutputType(gpio::OutputType value);

      /// \brief Retrieve the output type bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current output type.
      gpio::OutputType
      retrieveOutputType(void);

      /// \brief Configure the output speed bits.
      ///
      /// \param [in] value An enumeration value with the output speed.
      /// \par Returns
      ///    Nothing.
      void
      configureOutputSpeed(gpio::OutputSpeed value);

      /// \brief Retrieve the output speed bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current output speed.
      gpio::OutputSpeed
      retrieveOutputSpeed(void);

      /// \brief Configure the pull-up/pull-down bits.
      ///
      /// \param [in] value An enumeration value with the pull-up/pull-down resistors.
      /// \par Returns
      ///    Nothing.
      void
      configurePullUpPullDown(gpio::Resistors value);

      /// \brief Retrieve the pull-up/pull-down bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pull-up/pull-down resistors.
      gpio::Resistors
      retrievePullUpPullDown(void);

      /// \brief Configure the alternate function bits.
      ///
      /// \param [in] value An enumeration value with the alternate function.
      /// \par Returns
      ///    Nothing.
      void
      configureAlternateFunction(gpio::AlternateFunction value);

      /// \brief Retrieve the alternate function bits.
      ///
      /// \par Parameters
      ///    None.
      /// \return An enumeration value with the current pull-up/pull-down resistors.
      gpio::AlternateFunction
      retrieveAlternateFunction(void);

      // TODO: add configure lock

      /// @} end of name Configuration functions

      // ----- Pin member functions -------------------------------------------
      /// \name Pin member functions
      /// @{

      /// \brief Set the pin level to high.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      setPinHigh(void);

      /// \brief Set the pin level to low.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      setPinLow(void);

      /// \brief Toggle the pin level.
      ///
      /// \par Parameters
      ///    None.
      /// \par Returns
      ///    Nothing.
      void
      togglePin(void);

      /// \brief Check if the pin level is high.
      ///
      /// \par Parameters
      ///    None.
      /// \return True if the pin level is high.
      bool
      isPinHigh(void);

      /// \brief Check if the pin level is low.
      ///
      /// \par Parameters
      ///    None.
      /// \return True if the pin level is low.
      bool
      isPinLow(void);

      /// \brief Read the pin level.
      ///
      /// \par Parameters
      ///    None.
      /// \retval 1 The pin level is high.
      /// \retval 0 The pin level is low.
      gpio::bitValue_t
      readPin(void);

      /// @} end of name Pin member functions

      // ----------------------------------------------------------------------

    private:
      /// \name Private members
      /// @{

      /// \brief The address of the port hardware registers.
      ///
      /// \details
      /// This value is calculated by the constructor, based on the
      /// peripheral base address, the port number and the port offset.
      /// For convenient access, it is stored as a reference.
      gpio::PortRegisters& m_portRegisters;

      /// \brief The single bit mask, corresponding to the bit number.
      ///
      /// \details
      /// This value is calculated by the constructor, as (1 << bitNumber)
      const gpio::reg16_t m_bitMask;

      /// \brief The port number, as given in the constructor.
      const gpio::portNumber_t m_portNumber;
      /// \brief The bit number, as given in the constructor.
      const gpio::bitNumber_t m_bitNumber;

      /// @} end of name Private members
    };

    // ----- Inline member function definitions -------------------------------

    /// \details
    /// Compute the memory mapped port address, based on the base address,
    /// the port number and the port offset, then the single bit mask,
    /// and finally store the port number and the bit number in local members.
    ///
    /// When the arguments are constants, it is expected that the compiler
    /// optimises everything and no storage is used at all, the generated
    /// being the same as when using constant templates.
    ///
    /// \note This code is marked as inline, but not always_inline,
    /// so it is the compiler's choice what to do;
    /// in practice the Release (-Os) version is inlined,
    /// the Debug (-O0) is not.
    inline
    GpioPin::GpioPin(gpio::portNumber_t portNumber, gpio::bitNumber_t bitNumber)
        : //
        m_portRegisters(
            *reinterpret_cast<gpio::PortRegisters*>(gpio::PortRegisters::MEMORY_BASE
                + (portNumber * gpio::PortRegisters::MEMORY_OFFSET))), //
        m_bitMask(1 << bitNumber), //
        m_portNumber(portNumber), //
        m_bitNumber(bitNumber) //
    {
      // all initialisations done as constructors
    }

    inline gpio::PortRegisters&
    __attribute__((always_inline))
    GpioPin::getPortRegisters(void)
    {
      return m_portRegisters;
    }

    inline gpio::bitNumber_t
    __attribute__((always_inline))
    GpioPin::getBitNumber(void)
    {
      return m_bitNumber;
    }

    inline gpio::portNumber_t
    __attribute__((always_inline))
    GpioPin::getPortNumber(void)
    {
      return m_portNumber;
    }

    // ------------------------------------------------------------------------

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    inline void
    __attribute__((always_inline))
    GpioPin::configureMode(gpio::Mode value)
    {
      gpio::reg32_t current = m_portRegisters.readMode();
      current &= ~(gpio::MODE_MASK << (2 * m_bitNumber));

      gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
      newValue &= gpio::MODE_MASK;
      newValue <<= (2 * m_bitNumber);
      newValue |= current;

      m_portRegisters.writeMode(newValue);
    }

    /// \details
    /// Read the register and return the 2 configuration bits.
    inline gpio::Mode
    __attribute__((always_inline))
    GpioPin::retrieveMode(void)
    {
      gpio::reg32_t current = m_portRegisters.readMode();
      current >>= (2 * m_bitNumber);
      current &= gpio::MODE_MASK;

      return static_cast<gpio::Mode>(current);
    }

    /// \details
    /// Use bit-banding to write the single configuration bit.
    inline void
    __attribute__((always_inline))
    GpioPin::configureOutputType(gpio::OutputType value)
    {
      gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);

      hal::cortexm::BitBand::writePeripheralBitValue(&m_portRegisters.otyper,
          m_bitNumber, newValue);
    }

    /// \details
    /// Use bit-banding to read the single configuration bit and return it.
    inline gpio::OutputType
    __attribute__((always_inline))
    GpioPin::retrieveOutputType(void)
    {
      return static_cast<gpio::OutputType>(hal::cortexm::BitBand::readPeripheralBitValue(
          &m_portRegisters.otyper, m_bitNumber));
    }

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    inline void
    __attribute__((always_inline))
    GpioPin::configureOutputSpeed(gpio::OutputSpeed value)
    {
      gpio::reg32_t current = m_portRegisters.readOutputSpeed();
      current &= ~(gpio::OUTPUT_SPEED_MASK << (2 * m_bitNumber));

      gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
      newValue &= gpio::OUTPUT_SPEED_MASK;
      newValue <<= (2 * m_bitNumber);
      newValue |= current;

      m_portRegisters.writeOutputSpeed(newValue);
    }

    /// \details
    /// Read the register and return the 2 configuration bits.
    inline gpio::OutputSpeed
    __attribute__((always_inline))
    GpioPin::retrieveOutputSpeed(void)
    {
      gpio::reg32_t current = m_portRegisters.readOutputSpeed();
      current >>= (2 * m_bitNumber);
      current &= gpio::OUTPUT_SPEED_MASK;

      return static_cast<gpio::OutputSpeed>(current);
    }

    /// \details
    /// Use read/modify/write to change the 2 configuration bits.
    /// \warning Non atomic, the caller must use critical sections.
    inline void
    __attribute__((always_inline))
    GpioPin::configurePullUpPullDown(gpio::Resistors value)
    {
      gpio::reg32_t current = m_portRegisters.readPullUpPullDown();
      current &= ~(gpio::RESISTORS_MASK << (2 * m_bitNumber));

      gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);
      newValue &= gpio::RESISTORS_MASK;
      newValue <<= (2 * m_bitNumber);
      newValue |= current;

      m_portRegisters.writePullUpPullDown(newValue);
    }

    /// \details
    /// Read the register and return the 2 configuration bits.
    inline gpio::Resistors
    __attribute__((always_inline))
    GpioPin::retrievePullUpPullDown(void)
    {
      gpio::reg32_t current = m_portRegisters.readPullUpPullDown();
      current >>= (2 * m_bitNumber);
      current &= gpio::RESISTORS_MASK;

      return static_cast<gpio::Resistors>(current);
    }

    /// \details
    /// Use read/modify/write to change the 4 configuration bits.
    /// The AFR registers are organised as an array of two words.
    /// Bits corresponding to pins 0-7 are stored in the first word,
    /// bits corresponding to pins 8-15 in the second word.
    /// \warning Non atomic, the caller must use critical sections.
    inline void
    __attribute__((always_inline))
    GpioPin::configureAlternateFunction(gpio::AlternateFunction value)
    {
      gpio::reg32_t newValue = static_cast<gpio::reg32_t>(value);

      gpio::reg32_t current;

      if (m_bitNumber < 8)
        {
          current = m_portRegisters.readAlternateFunction(0);
          current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * m_bitNumber));

          newValue &= gpio::ALTERNATE_FUNCTION_MASK;
          newValue <<= (4 * m_bitNumber);
          newValue |= current;

          m_portRegisters.writeAlternateFunction(0, newValue);
        }
      else
        {
          gpio::bitNumber_t bitNumber = m_bitNumber - 8;

          current = m_portRegisters.readAlternateFunction(1);
          current &= ~(gpio::ALTERNATE_FUNCTION_MASK << (4 * bitNumber));

          newValue &= gpio::ALTERNATE_FUNCTION_MASK;
          newValue <<= (4 * bitNumber);
          newValue |= current;

          m_portRegisters.writeAlternateFunction(1, newValue);
        }
    }

    /// \details
    /// Read the register and return the 4 configuration bits.
    /// The AFR registers are organised as an array of two words.
    /// Bits corresponding to pins 0-7 are stored in the first word,
    /// bits corresponding to pins 8-15 in the second word.
    inline gpio::AlternateFunction
    __attribute__((always_inline))
    GpioPin::retrieveAlternateFunction(void)
    {
      gpio::reg32_t current;

      if (m_bitNumber < 8)
        {
          current = m_portRegisters.readAlternateFunction(0);
          current >>= (4 * m_bitNumber);
        }
      else
        {
          current = m_portRegisters.readAlternateFunction(1);
          current >>= (4 * (m_bitNumber - 8));
        }

      return static_cast<gpio::AlternateFunction>(current
          & gpio::ALTERNATE_FUNCTION_MASK);
    }

    // ------------------------------------------------------------------------

    /// \details
    /// Use the lower half of the special BSSR register to set the pin high.
    inline void
    __attribute__((always_inline))
    GpioPin::setPinHigh(void)
    {
      m_portRegisters.writeSetReset(static_cast<gpio::reg32_t>(m_bitMask));
    }

    /// \details
    /// Use the upper half of the special BSSR register to set the pin low.
    inline void
    __attribute__((always_inline))
    GpioPin::setPinLow(void)
    {
      // write to the upper half
      m_portRegisters.writeSetReset(
          static_cast<gpio::reg32_t>(m_bitMask) << 16);
    }

    /// \details
    /// Use bit-banding to read the corresponding ODR bit,
    /// reverse its value and write it back.
    /// \warning Non atomic, the caller must use critical sections.
    inline void
    __attribute__((always_inline))
    GpioPin::togglePin(void)
    {
      gpio::bitValue_t oldValue = hal::cortexm::BitBand::readPeripheralBitValue(
          &m_portRegisters.odr, m_bitNumber);

      gpio::bitValue_t newValue = ~oldValue;
      hal::cortexm::BitBand::writePeripheralBitValue(&m_portRegisters.odr,
          m_bitNumber, newValue);
    }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and test it.
    inline bool
    __attribute__((always_inline))
    GpioPin::isPinHigh(void)
    {
      return (hal::cortexm::BitBand::readPeripheralBitValue(
          &m_portRegisters.idr, m_bitNumber) != 0);
    }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and test it.
    inline bool
    __attribute__((always_inline))
    GpioPin::isPinLow(void)
    {
      return (hal::cortexm::BitBand::readPeripheralBitValue(
          &m_portRegisters.idr, m_bitNumber) == 0);
    }

    /// \details
    /// Use bit-banding to read the corresponding IDR bit and return it.
    inline gpio::bitValue_t
    __attribute__((always_inline))
    GpioPin::readPin(void)
    {
      return hal::cortexm::BitBand::readPeripheralBitValue(&m_portRegisters.idr,
          m_bitNumber);
    }

  // ==========================================================================
  }// namespace stm32f4
} // namespace os

#endif // defined(OS_INCLUDE_HAL_MCU_FAMILY_STM32F4)
#endif // HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_PERIPHERAL_GPIO_H_
