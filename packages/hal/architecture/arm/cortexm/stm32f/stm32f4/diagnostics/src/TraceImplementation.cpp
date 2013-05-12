//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 definitions of the trace implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/diagnostics/include/TraceImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/peripheral/include/Iwdg.h"

#include "portable/peripheral/bitbang/include/I2CMaster.h"
#include "portable/peripheral/bitbang/include/I2CMaster.cpp.h"

#include "hal/platform/include/XCDL_TraceI2CDefines.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"

// required for gpio clock
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_rcc.h"

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {

      // ----------------------------------------------------------------------

      /// \addtogroup stm32f4_diag
      /// @{

      typedef os::bitbang::i2c::duration_t duration_t;
      typedef os::bitbang::i2c::address_t address_t;

      static const duration_t CLOCK_DURATION_LOOPS =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK;

      static const address_t I2C_DESTINATION_ADDRESS =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DESTINATION_ADDRESS;

      static const gpio::portNumber_t SDA_PORT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT;
      static const gpio::bitNumber_t SDA_BIT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT;

      static const gpio::portNumber_t SCL_PORT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT;
      static const gpio::bitNumber_t SCL_BIT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT;

      /// @} end of addtogroup stm32f4_diag

      // ======================================================================

      /// \ingroup stm32f4_diag
      /// \nosubgrouping
      ///
      /// \brief Open drain pin template class.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        class TPinOpenDrain
        {
        public:
          typedef WatchDog_T WatchDog;
          static constexpr gpio::bitNumber_t GPIO_BitNo = Bit_T;

          // 0 = GPIOA, 1 = GPIOC, ...
          static constexpr gpio::portNumber_t GPIO_PortNo = Port_T;

          // kind of explicit instantiation
          typedef class TGpioPin<GPIO_PortNo, GPIO_BitNo> GpioPin;

          /// \name Constructors/destructor
          /// @{

          /// \brief Deleted constructor.
          TPinOpenDrain() = delete;

          /// @} end of name Constructors/destructor

          /// \name Public member functions
          /// @{

          /// \brief Power up the pin.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          powerUp(void);

          /// \brief Power the the pin.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          powerDown(void);

          /// \brief Set pin level to high.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          setHigh(void);

          /// \brief Set pin level to low.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          setLow(void);

          /// \brief Check if the pin state is low.
          ///
          /// \par Parameters
          ///     None.
          /// \retval True        Pin is low.
          /// \retval False       Pin is high.
          static bool
          isLow(void);

          /// \brief Check if the pin state is high.
          ///
          /// \par Parameters
          ///     None.
          /// \retval True        Pin is high.
          /// \retval False       Pin is low.
          static bool
          isHigh(void);

          /// \brief Wait for the pin to get high.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          waitToGetHigh(void);

          /// \brief Release the pin and loop until it gets high.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static void
          setHighAndSynchronise(void);

        };

      // ======================================================================

      /// \details
      /// Initialise the pin to open drain mode, max speed
      /// and leave it in high state.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::powerUp(void)
        {
          /// \todo Implement this in C++.
          RCC_AHB1PeriphClockCmd((RCC_AHB1Periph_GPIOA << GPIO_PortNo), ENABLE);

          GpioPin::configureMode(gpio::Mode::Output);
          GpioPin::configureOutputType(gpio::OutputType::OpenDrain);
          GpioPin::configureOutputSpeed(gpio::OutputSpeed::High_100MHz);
          GpioPin::configurePullUpPullDown(gpio::Resistors::PullDown);

          // start pin as high
          setHigh();
        }

      /// \details
      /// Return the pin to high input mode.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::powerDown(void)
        {
          GpioPin::configureMode(gpio::Mode::Input);
          GpioPin::configurePullUpPullDown(gpio::Resistors::None);
        }

      /// \details
      /// Set the pin to high state. In fact release the pin
      /// and the bus pull up resistors will make it high.
      /// \note In case the slave keeps
      /// the bus low, the effect will be delayed accordingly.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline void
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::setHigh(void)
        {
          GpioPin::setPinHigh();
        }

      /// \details
      /// Set the pin to low state. The effect will be immediate.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline void
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::setLow(void)
        {
          GpioPin::setPinLow();
        }

      /// \details
      /// Read the pin state and return true if low.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline bool
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::isLow(void)
        {
          return GpioPin::isPinLow();
        }

      /// \details
      /// Read the pin state and return true if high.
      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline bool
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::isHigh(void)
        {
          return GpioPin::isPinHigh();
        }

      /// \details
      /// For synchronisation purposes, the slave may keep the
      /// lines low until ready to continue. The master shall
      /// wait for this condition.
      /// To avoid the watch dog to trigger, reset it.
      /// \warning If used for devices that compile on release
      /// the implementation should not loop forever.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline void
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::waitToGetHigh(void)
        {
          while (isLow())
            {
              WatchDog::reset();
            }
        }

      /// \details
      /// Release the pin state and loop until the pin gets
      /// high, eventually resetting
      /// the watch dog.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline void
        __attribute__((always_inline))
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::setHighAndSynchronise(void)
        {
          setHigh();
          waitToGetHigh();
        }

      // ======================================================================

      /// \ingroup stm32f4_diag
      /// \brief Watch dog policy class.
      class WatchDog
      {
      public:
        static void
        reset(void);
      };

      /// \brief Reset the watch dog device.
      inline void
      __attribute__((always_inline))
      WatchDog::reset(void)
      {
        //IWDG ->KR = ((uint16_t) 0xAAAA);
        Iwdg::reload();
      }

      // ======================================================================
      /// \addtogroup stm32f4_diag
      /// @{

      /// \brief SDA template explicit instantiation.
      template class TPinOpenDrain<WatchDog, SDA_PORT, SDA_BIT> ;
      /// \brief SDA class type definition.
      typedef class TPinOpenDrain<WatchDog, SDA_PORT, SDA_BIT> SDA;

      /// \brief SCL template explicit instantiation.
      template class TPinOpenDrain<WatchDog, SCL_PORT, SCL_BIT> ;
      /// \brief SCL class type definition.
      typedef class TPinOpenDrain<WatchDog, SCL_PORT, SCL_BIT> SCL;

    /// @} end of addtogroup stm32f4_diag

    // ----------------------------------------------------------------------
    }// namespace diag
  } // namespace stm32f4
} // namespace hal

/// \brief TTimer
template class os::bitbang::i2c::TTimer<hal::stm32f4::diag::WatchDog,
    hal::stm32f4::diag::CLOCK_DURATION_LOOPS>;

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {
      /// \ingroup stm32f4_diag
      /// \brief Timer
      typedef os::bitbang::i2c::TTimer<WatchDog, CLOCK_DURATION_LOOPS> Timer;
    } // namespace diag
  } // namespace stm32f4
} // namespace hal

template class os::bitbang::i2c::TMaster<hal::stm32f4::diag::SDA,
    hal::stm32f4::diag::SCL, hal::stm32f4::diag::Timer>;

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {
      // ======================================================================

      /// \ingroup stm32f4_diag
      /// \brief I2CMaster
      typedef class os::bitbang::i2c::TMaster<SDA, SCL, Timer> I2CMaster;

      // ======================================================================

#if defined(DEBUG) || defined(__DOXYGEN__)

      /// \details
      /// Called during early start-up, to perform
      /// initialisations required before constructor.
      ///
      /// Enable APB1 clock for GPIOC.
      void
      TraceImplementation::powerUp(void)
      {
        I2CMaster::powerUp();
      }

      /// \details
      /// Called during late cleanup, to turn off
      /// hardware.
      void
      TraceImplementation::powerDown(void)
      {
        I2CMaster::powerDown();
      }

      /// \details
      /// Send the sequence of bytes to the
      /// bit banged I2C device. The operation is atomic.
      ssize_t
      TraceImplementation::write(const void* pBuf, size_t numBytes)
      {
        if (!isDevicePresent())
          return 0;

        size_t count = 0;

        // DI
        for (;;)
          {
            I2CMaster::sendStart();

            I2CMaster::sendAddress(I2C_DESTINATION_ADDRESS,
                I2CMaster::Mode::Write);
            if (!I2CMaster::receiveAck())
              {
                I2CMaster::cleanup();
                goto retry;
              }

            for (; count < numBytes; ++count)
              {
                uint8_t ch = static_cast<const uint8_t*>(pBuf)[count];
                I2CMaster::sendByte(ch);
                if (!I2CMaster::receiveAck())
                  {
                    I2CMaster::cleanup();
                    goto retry;
                  }
              }
            I2CMaster::sendStop();

            Timer::sleep(hal::stm32f4::diag::CLOCK_DURATION_LOOPS * 10);
            break;

            retry: //
            Timer::sleep((hal::stm32f4::diag::CLOCK_DURATION_LOOPS + 1) * 10);
          }
        // EI
        return count;
      }

      /// \details
      /// If the device is connected, the SDA line is pulled up
      /// and we can detect this condition. Otherwise a high
      /// pull down resistor keeps the line low.
      bool
      TraceImplementation::isDevicePresent(void)
      {
        return SDA::isHigh();
      }

#endif

    // ======================================================================
    }// namespace diag
  } // namespace stm32f4
} // namespace hal

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION)
