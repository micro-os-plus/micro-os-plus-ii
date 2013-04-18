//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Template definitions for the bit banged I2C Master class.

#ifndef OS_PORTABLE_DEVICES_BITBANG_I2CMASTERCPP_H_
#define OS_PORTABLE_DEVICES_BITBANG_I2CMASTERCPP_H_

#include "portable/core/include/ConfigDefines.h"

#include "portable/devices/bitbang/include/I2CMaster.h"

namespace os
{
  namespace bitbang
  {
    namespace i2c
    {
      // ======================================================================

      template<class WatchDog_T, int HoldDuration_T, int SetupDuration_T>
        void
        TTimer<WatchDog_T, HoldDuration_T, SetupDuration_T>::sleep(
            duration_t count)
        {
          // add one more cycle
          ++count;

          for (++count; --count > 0;)
            {
              WatchDog::reset();
            }
        }

      // ======================================================================

      /// \details
      /// Power up the two pins used for the I2C lines.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::powerUp(void)
        {
          SDA::powerUp();
          SCL::powerUp();
        }

      /// \details
      /// Power down the two pins used for the I2C lines.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::powerDown(void)
        {
          SDA::powerDown();
          SCL::powerDown();
        }

      /// \details
      /// Send the start condition, by setting low the
      /// data line followed by the clock line.
      /// \warning May wait indefinitely for the other
      /// master/slaves to release the bus.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::sendStart()
        {
          // start with both lines High
          SDA::setHighAndSynchronise();
          SCL::setHighAndSynchronise();
          Timer::sleepSetupDuration();

          SDA::setLow();
          Timer::sleepHoldDuration();
          SCL::setLow();
          Timer::sleepSetupDuration();
        }

      /// \details
      /// Serialise one byte and send it to the I2C bus.
      /// Data is transferred with the Most Significant Bit (MSB) first.
      /// \warning May wait indefinitely for the other
      /// master/slaves to release the bus.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::sendByte(uint8_t b)
        {
          for (int i = 8; i > 0; --i)
            {
              if ((b & 0x80) != 0)
                {
                  SDA::setHigh();
                }
              else
                {
                  SDA::setLow();
                }
              b <<= 1;
              Timer::sleepSetupDuration();

              SCL::setHighAndSynchronise();
              Timer::sleepHoldDuration();
              SCL::setLow();

              Timer::sleepSetupDuration();
            }
          // leave the line high
          //SDA::setHigh();
        }

      /// \details
      /// Generate 8 clock pulses and sample the data line to
      /// assemble one byte of data.
      /// Data is received with the Most Significant Bit (MSB) first.
      /// \warning May wait indefinitely for the other
      /// master/slaves to release the bus.
      template<class SDA_T, class SCL_T, class Timer_T>
        uint8_t
        TMaster<SDA_T, SCL_T, Timer_T>::receiveByte(void)
        {
          uint8_t b = 0;

          // release SDA, to allow the slave to control it
          SDA::setHigh();
          for (int i = 8; i > 0; --i)
            {
              Timer::sleepSetupDuration();

              SCL::setHighAndSynchronise();
              Timer::sleepHalfHoldDuration();
              b <<= 1;
              // sample at the middle of the hold period
              if (SDA::isHigh())
                {
                  b |= 1;
                }
              Timer::sleepHalfHoldDuration();
              SCL::setLow();

              Timer::sleepSetupDuration();
            }
          return b;
        }

      /// \details
      /// Generate one clock pulse and sample the data line to
      /// determine if the slave acknowledged the transfer.
      /// \warning May wait indefinitely for the other
      /// master/slaves to release the bus.
      template<class SDA_T, class SCL_T, class Timer_T>
        bool
        TMaster<SDA_T, SCL_T, Timer_T>::receiveAck()
        {
          bool ret;

          // release SDA to allow slave to control it
          SDA::setHigh();
          Timer::sleepSetupDuration();

          SCL::setHighAndSynchronise();
          Timer::sleepHalfHoldDuration();
          // sample at the middle of the hold period
          ret = SDA::isLow();
          Timer::sleepHalfHoldDuration();
          SCL::setLow();

          // as soon as SCL goes low, the slave will
          // release SDA, which will return to high
          Timer::sleepSetupDuration();

          // extra inter-bytes break
          Timer::sleepHoldDuration();
          return ret;
        }

      /// \details
      /// Send the stop condition, by setting high the
      /// data line followed by the clock line.
      /// \warning May wait indefinitely for the other
      /// master/slaves to release the bus.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::sendStop()
        {
          // be sure SDA starts from low
          SDA::setLow();
          Timer::sleepHoldDuration();

          SCL::setHighAndSynchronise();
          Timer::sleepHoldDuration();
          SDA::setHighAndSynchronise();
          Timer::sleepSetupDuration();

          // extra end of transaction break
          Timer::sleepHoldDuration();
        }

      /// \details
      /// Detach from the bus, by setting both line high, without
      /// waiting for the other master/slaves to complete.
      template<class SDA_T, class SCL_T, class Timer_T>
        void
        TMaster<SDA_T, SCL_T, Timer_T>::cleanup()
        {
          SCL::setHigh();
          SDA::setHigh();
        }

    // ========================================================================
    }//namespace i2c
  }    // namespace bitbang
} // namespace os
#endif // OS_PORTABLE_DEVICES_BITBANG_I2CMASTERCPP_H_
