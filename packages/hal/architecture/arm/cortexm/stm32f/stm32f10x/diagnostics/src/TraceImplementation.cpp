//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F10x definitions of the trace implementation class.

#include "portable/core/include/ConfigDefines.h"

#if defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_DIAGNOSTICS_TRACEIMPLEMENTATION) || defined(__DOXYGEN__)

#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/diagnostics/include/TraceImplementation.h"

#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_rcc.h"

#include "portable/devices/bitbang/include/I2CMaster.h"
#include "portable/devices/bitbang/include/I2CMaster.cpp.h"

namespace hal
{
  namespace stm32f10x
  {
    namespace diag
    {
      // ----------------------------------------------------------------------

      typedef os::bitbang::i2c::duration_t duration_t;
      typedef os::bitbang::i2c::address_t address_t;

      static const duration_t HOLD_DURATION_LOOPS = 1000;
      static const duration_t SETUP_DURATION_LOOPS = HOLD_DURATION_LOOPS / 2;
      static const address_t I2C_DESTINATION_ADDRESS = 0x28;

      // ======================================================================

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        class TPinOpenDrain
        {
        public:
          typedef WatchDog_T WatchDog;
          static constexpr int GPIO_Pin = PinNo_T;
          static constexpr GPIO_TypeDef* GPIOx = (GPIO_TypeDef*) Port_T;

          TPinOpenDrain() = delete;

          // should leave the pin High
          static void
          powerUp(void);

          static void
          powerDown(void);

          static void
          setHigh(void);

          static void
          setLow(void);

          static bool
          isLow(void);

          static bool
          isHigh(void);

          static void
          waitToGetHigh(void);

          static void
          setHighAndSynchronise(void);

        };

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::powerUp(void)
        {
          GPIO_InitTypeDef GPIO_InitStructure;

          /* Configure PC12 in output push/pull mode */
          GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
          GPIO_Init(GPIOx, &GPIO_InitStructure);

        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::powerDown(void)
        {
          GPIO_DeInit(GPIOx);
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::setHigh(void)
        {
          GPIOx->BSRR = GPIO_Pin;
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::setLow(void)
        {
          GPIOx->BRR = GPIO_Pin;
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        bool
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::isLow(void)
        {
          return ((GPIOx->IDR & GPIO_Pin) == 0);
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        bool
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::isHigh(void)
        {
          return ((GPIOx->IDR & GPIO_Pin) != 0);
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::waitToGetHigh(void)
        {
          while (isLow())
            {
              WatchDog::reset();
            }
        }

      template<class WatchDog_T, unsigned int Port_T, int PinNo_T>
        inline __attribute__((always_inline))
        void
        TPinOpenDrain<WatchDog_T, Port_T, PinNo_T>::setHighAndSynchronise(void)
        {
          setHigh();
          waitToGetHigh();
        }

      class Watchdog
      {
      public:
        static
        void
        reset(void);
      };

      inline  __attribute__((always_inline))
      void
      Watchdog::reset(void)
      {
        IWDG->KR = ((uint16_t)0xAAAA);
      }

      template class TPinOpenDrain<Watchdog, (unsigned int) GPIOC, 7> ;
      typedef class TPinOpenDrain<Watchdog, (unsigned int) GPIOC, 7> SDA;

      template class TPinOpenDrain<Watchdog, (unsigned int) GPIOC, 6> ;
      typedef class TPinOpenDrain<Watchdog, (unsigned int) GPIOC, 6> SCL;
    } // namespace diag
  } // namespace stm32f10x
} // namespace hal

template class os::bitbang::i2c::TTimer<hal::stm32f10x::diag::Watchdog,
    hal::stm32f10x::diag::HOLD_DURATION_LOOPS,
    hal::stm32f10x::diag::SETUP_DURATION_LOOPS>;

namespace hal
{
  namespace stm32f10x
  {
    namespace diag
    {
      typedef os::bitbang::i2c::TTimer<Watchdog, HOLD_DURATION_LOOPS,
          SETUP_DURATION_LOOPS> Timer;
    } // namespace diag
  } // namespace stm32f10x
} // namespace hal

template class os::bitbang::i2c::TMaster<hal::stm32f10x::diag::SDA,
    hal::stm32f10x::diag::SCL, hal::stm32f10x::diag::Timer>;

namespace hal
{
  namespace stm32f10x
  {
    namespace diag
    {

      // ======================================================================

      typedef class os::bitbang::i2c::TMaster<SDA, SCL, Timer> I2CMaster;

      // ======================================================================

#if defined(DEBUG) || defined(__DOXYGEN__)

      TraceImplementation::TraceImplementation()
      {
      }

      TraceImplementation::~TraceImplementation()
      {
      }

      /// \details
      /// Called during early start-up, to perform
      /// initialisations required before constructor.
      ///
      /// Enable APB2 clock for GPIOC.
      void
      TraceImplementation::powerUp(void)
      {
        // WARNING: must be in sync with I2C pin definitions.
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

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

            I2CMaster::sendAddress(I2C_DESTINATION_ADDRESS, I2CMaster::Mode::Write);
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

            Timer::sleep(hal::stm32f10x::diag::HOLD_DURATION_LOOPS * 10);
            break;

            retry: //
            Timer::sleep((hal::stm32f10x::diag::HOLD_DURATION_LOOPS + 1) * 10);
          }
        // EI
        return count;
      }

      /// details
      /// If the device is connected, the SDA line is pulled up
      /// and we can detect his condition. Otherwise a high
      /// pull down resistor keeps the line low.
      bool
      TraceImplementation::isDevicePresent(void)
      {
        return SDA::isHigh();
      }

#endif

    // ======================================================================

    }// namespace diag
  } // namespace stm32f10x
} // namespace hal

extern "C" void
assert_failed(unsigned char*func, int lineno);

void
assert_failed(unsigned char*func __attribute__((unused)),
    int lineno __attribute__((unused)))
{
  // TODO: print string and number
}

#endif // defined(OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F10X_DIAGNOSTICS_TRACEIMPLEMENTATION)
