//
// This file is part of the µOS++ SE distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief Template declarations for the bit banged I2C Master class.
///
/// \details The current implementation was intended as
/// output device for the tracing facility, i.e. to output messages
/// over I2C to a dedicated device that transfers them on the fly
/// over USB serial to a computer.
///
/// In this configuration the bus topology is minimal, one master and
/// one slave, so no complex multi-master situations are expected.
/// However, the minimal level of synchronisation is supported,
/// the master is prepared to wait for the slave to complete
/// in situations when
/// clock stretching is used. Even more, the master will also
/// wait for the data line to be released, although in this case
/// the transactions will probably be compromised anyway.
///
/// \todo When the SDA line is controlled by someone else, abort
/// the transaction and retry it properly.

#ifndef OS_PORTABLE_PERIPHERAL_BITBANG_I2CMASTER_H_
#define OS_PORTABLE_PERIPHERAL_BITBANG_I2CMASTER_H_

#include "portable/core/include/ConfigDefines.h"

namespace os
{
  namespace bitbang
  {
    namespace i2c
    {
      /// \brief Timer duration.
      typedef int duration_t;

      /// \brief 7bit I2C destination address.
      typedef uint8_t address_t;

      // ========================================================================

      template<class WatchDog_T>
        class TPinSample
        {
        public:
          typedef WatchDog_T WatchDog;

          TPinSample(void) = delete;

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

      template<class WatchDog_T>
        void
        TPinSample<WatchDog_T>::waitToGetHigh(void)
        {
          while (isLow())
            {
              WatchDog::reload();
            }
        }

      template<class WatchDog_T>
        void
        TPinSample<WatchDog_T>::setHighAndSynchronise(void)
        {
          setHigh();
          waitToGetHigh();
        }

      // ========================================================================

      /// \headerfile I2CMaster.h "portable/peripheral/bitbang/include/I2CMaster.h"
      /// \ingroup dev
      /// \nosubgrouping
      ///
      /// \brief Timer template for I2C master.
      ///
      /// \tparam WatchDog_T  Watchdog implementation class.
      /// \tparam HoldDuration_T  Duration for the hold period.
      /// \tparam SetupDuration_T  Duration for the setup period.
      ///
      /// \details
      /// The TTimer template implements a simple timer used
      /// by the I2C master.
     template<class WatchDog_T, int ClockDuration_T, int SetupDuration_T = ClockDuration_T/2>
        class TTimer
        {
        public:
          typedef WatchDog_T WatchDog;

          /// \name Constructors/destructor
          /// @{

          /// \brief Deleted constructor.
          TTimer(void) = delete;

          /// @} end of name Constructors/destructor

          /// \name Public member functions
          /// @{

          /// \brief Sleep a number of units.
          ///
          /// \param count [in] Number of units to sleep.
          /// \par Returns
          ///     Nothing.
          static
          void
          sleep(duration_t count);

          /// \brief Sleep for the clock high duration.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static
          void
          sleepClockDuration(void);

          /// \brief Sleep for the half clock high duration.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static
          void
          sleepHalfClockDuration(void);

          /// \brief Sleep for the setup duration.
          ///
          /// \par Parameters
          ///     None.
          /// \par Returns
          ///     Nothing.
          static
          void
          sleepSetupDuration(void);

          /// @} end of Public member functions

        };

      // ------------------------------------------------------------------------

      template<class WatchDog_T, int ClockDuration_T, int SetupDuration_T>
        inline void
        __attribute__((always_inline))
        TTimer<WatchDog_T, ClockDuration_T, SetupDuration_T>::sleepClockDuration(
            void)
        {
          sleep(ClockDuration_T);
        }

      template<class WatchDog_T, int ClockDuration_T, int SetupDuration_T>
        inline void
        __attribute__((always_inline))
        TTimer<WatchDog_T, ClockDuration_T, SetupDuration_T>::sleepSetupDuration(
            void)
        {
          sleep(SetupDuration_T);
        }

      template<class WatchDog_T, int ClockDuration_T, int SetupDuration_T>
        inline void
        __attribute__((always_inline))
        TTimer<WatchDog_T, ClockDuration_T, SetupDuration_T>::sleepHalfClockDuration(
            void)
        {
          sleep(ClockDuration_T / 2);
        }

      // ========================================================================

      /// \headerfile I2CMaster.h "portable/peripheral/bitbang/include/I2CMaster.h"
      /// \ingroup dev
      /// \nosubgrouping
      ///
      /// \brief Bit banged I2C Master class.
      ///
      /// \tparam SDA_T  SDA line implementation class.
      /// \tparam SCL_T  SCL line implementation class.
      /// \tparam Timer_T  Timer implementation class.
      ///
      /// \details
      /// The TMaster template implements a bit-banged I2C master.
      /// It requires two GPIO pins and a timer routine.
      ///
      /// All master transactions are opened by a start condition,
      /// a mandatory address, several
      /// write or read bytes and is closed by the stop condition.

      template<class SDA_T, class SCL_T, class Timer_T>
        class TMaster
        {
        public:

          /// \name Standard template types
          ///
          /// These types permit a standardised way of
          /// referring to names of (or names dependent on) the template
          /// parameters, which are specific to the implementation. Except
          /// when referring to the template, (in which case the templates
          /// parameters are required), use these types everywhere
          /// else instead of usual types.
          /// @{

          /// \brief I2C data line object.
          typedef SDA_T SDA;

          /// \brief I2C clock line object.
          typedef SCL_T SCL;

          /// \brief I2C timer object to perform the short protocol delays.
          typedef Timer_T Timer;

          /// @} end of name Standard template types

          /// \name Local types.
          /// @{

          /// \brief Mode bit.
          enum Mode
          {
            Write = 0x0, ///< Identify the transaction as output
            Read = 0x1 ///< Identify the transaction as input
          };

          /// @} end of name Local types.

          /// \name Constructors/destructor
          /// @{

          /// \brief Deleted constructor.
          TMaster(void) = delete;

          /// @} end of name Constructors/destructor

          /// \name Initialisation function members
          /// @{

          /// \brief Power up the device.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          powerUp(void);

          /// \brief Power down the device.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          powerDown(void);

          /// @} end of name Initialisation function members

          /// \name Public function members
          /// @{

          /// \brief Send the stop condition.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          sendStart(void);

          /// \brief Send the destination address and the mode bit.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          sendAddress(address_t addr, Mode mode);

          /// \brief Send one byte.
          ///
          /// \param [in] b     One byte.
          /// \par Returns
          ///    Nothing.
          static
          void
          sendByte(uint8_t b);

          /// \brief Receive one byte.
          ///
          /// \par Parameters
          ///    None.
          /// \return Byte from slave.
          static uint8_t
          receiveByte(void);

          /// \brief Receive the ACK/NACK bit.
          ///
          /// \par Parameters
          ///    None.
          /// \retval True        ACK bit received.
          /// \retval False       NACK bit received.
          static
          bool
          receiveAck(void);

          /// \brief Send the stop condition.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          sendStop(void);

          /// \brief Cleanup the bus.
          ///
          /// \par Parameters
          ///    None.
          /// \par Returns
          ///    Nothing.
          static
          void
          cleanup(void);

          /// @} end of name Public function members

        };

      // ------------------------------------------------------------------------

      /// \details
      /// Pack the 7bit destination address and the mode bit
      /// into a byte and send it on the bus to identify the slave that
      /// is addressed.
      template<class SDA_T, class SCL_T, class Timer_T>
        inline  __attribute__((always_inline))
        void
        TMaster<SDA_T, SCL_T, Timer_T>::sendAddress(address_t addr,
            Mode mode)
        {
          sendByte((addr << 1) | (mode & 1));
        }

    // ==========================================================================
    }//namespace i2c
  }      // namespace bitbang
} // namespace os
#endif // OS_PORTABLE_PERIPHERAL_BITBANG_I2CMASTER_H_
