//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F4 definitions of the trace implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F4_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/diagnostics/include/TraceImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f4/lib/stm/include/stm32f4xx_rcc.h"

#include "portable/peripheral/bitbang/include/I2CMaster.h"
#include "portable/peripheral/bitbang/include/I2CMaster.cpp.h"

#include "hal/platform/include/XCDL_TraceI2CDefines.h"

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {
      // ----------------------------------------------------------------------

      typedef os::bitbang::i2c::duration_t duration_t;
      typedef os::bitbang::i2c::address_t address_t;

      static const duration_t CLOCK_DURATION_LOOPS =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK;

      static const address_t I2C_DESTINATION_ADDRESS =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DESTINATION_ADDRESS;

      static const int SDA_PORT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT;
      static const int SDA_BIT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT;

      static const int SCL_PORT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT;
      static const int SCL_BIT =
          OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT;

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
          static constexpr int GPIO_BitNo = Bit_T;
          static constexpr int GPIO_BitMask = (1 << GPIO_BitNo);

          // 0 = GPIOA, 1 = GPIOC, ...
          static constexpr int GPIO_PortNo = Port_T;
          static constexpr GPIO_TypeDef* GPIO_Address =
              (GPIO_TypeDef*) ((GPIOA_BASE + (0x0400 * GPIO_PortNo)));

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
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::powerUp(void)
        {
          RCC_AHB1PeriphClockCmd((RCC_AHB1Periph_GPIOA << GPIO_PortNo), ENABLE);

          GPIO_InitTypeDef GPIO_InitStructure;

          GPIO_InitStructure.GPIO_Pin = GPIO_BitMask;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
          GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
          GPIO_Init(GPIO_Address, &GPIO_InitStructure);

          // start pin as high
          setHigh();
        }

      /// \details
      /// Return the pin to high input mode.
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::powerDown(void)
        {
          GPIO_InitTypeDef GPIO_InitStructure;

          GPIO_InitStructure.GPIO_Pin = GPIO_BitMask;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
          GPIO_Init(GPIO_Address, &GPIO_InitStructure);
        }

      /// \details
      /// Set the pin to high state. In fact release the pin
      /// and the bus pull up resistors will make it high.
      /// \note In case the slave keeps
      /// the bus low, the effect will be delayed accordingly.
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::setHigh(void)
        {
          GPIO_Address->BSRRL = GPIO_BitMask;
        }

      /// \details
      /// Set the pin to low state. The effect will be immediate.
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::setLow(void)
        {
          GPIO_Address->BSRRH = GPIO_BitMask;
        }

      /// \details
      /// Read the pin state and return true if low.
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline __attribute__((always_inline))
        bool
        TPinOpenDrain<WatchDog_T, Port_T, Bit_T>::isLow(void)
        {
          return ((GPIO_Address->IDR & GPIO_BitMask) == 0);
        }

      /// \details
      /// Read the pin state and return true if high.
      /// \todo Implement this in C++.
      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        bool
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::isHigh(void)
        {
          return ((GPIO_Address->IDR & GPIO_BitMask) != 0);
        }

      /// \details
      /// For synchronisation purposes, the slave may keep the
      /// lines low until ready to continue. The master shall
      /// wait for this condition.
      /// To avoid the watch dog to trigger, reset it.
      /// \warning If used for devices that compile on release
      /// the implementation should not loop forever.
      template<class WatchDog_T, unsigned int Port_T, int Bit_T>
        inline __attribute__((always_inline))
        void
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
        inline __attribute__((always_inline))
        void
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
        static
        void
        reset(void);
      };

      /// \brief Reset the watch dog device.
      inline __attribute__((always_inline))
      void
      WatchDog::reset(void)
      {
        IWDG ->KR = ((uint16_t) 0xAAAA);
      }

      // ======================================================================

      /// \ingroup stm32f4_diag
      /// @{

      /// \brief SDA template explicit instantiation.
      template class TPinOpenDrain<WatchDog, SDA_PORT, SDA_BIT> ;
      /// \brief SDA class type definition.
      typedef class TPinOpenDrain<WatchDog, SDA_PORT, SDA_BIT> SDA;

      /// \brief SCL template explicit instantiation.
      template class TPinOpenDrain<WatchDog, SCL_PORT, SCL_BIT> ;
      /// \brief SCL class type definition.
      typedef class TPinOpenDrain<WatchDog, SCL_PORT, SCL_BIT> SCL;

    /// @}

    // ----------------------------------------------------------------------
    }// namespace diag
  } // namespace stm32f4
} // namespace hal

template class os::bitbang::i2c::TTimer<hal::stm32f4::diag::WatchDog,
    hal::stm32f4::diag::CLOCK_DURATION_LOOPS>;

namespace hal
{
  namespace stm32f4
  {
    namespace diag
    {
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
