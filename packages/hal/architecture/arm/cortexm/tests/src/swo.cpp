//
// This file is part of the µOS++ distribution.
// Copyright (c) 2013 Liviu Ionescu.
//

/// \file
/// \brief STM32F CMSIS simple test.

#include "portable/core/include/OS.h"

#if defined(OS_INCLUDE_HAL_MCU_DEVICE_STM32F103RB)
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_gpio.h"
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/lib/stm/include/stm32f10x_rcc.h"
#endif
#include "hal/architecture/arm/cortexm/stm32f/stm32f10x/include/InterruptNumbersSelector.h"

void
Delay(__IO uint32_t nCount);

void
init_SWO(uint32_t SWOSpeed, uint32_t CPUSpeed);

uint32_t
ITM_SendChar2(uint8_t ch);

int
main()
{
#if defined(DEBUG)
  os::diag::trace.putString(__PRETTY_FUNCTION__);
  os::diag::trace.putNewLine();
#endif

#define SWO_SPEED_BPS   (1000000)
//#define SWO_SPEED_BPS   (19200)

  init_SWO(SWO_SPEED_BPS, 72000000);

  /* At this stage the microcontroller clock setting is already configured,
   this is done through SystemInit() function which is called from startup
   file (startup_stm32f10x_xx.s) before to branch to application main.
   To reconfigure the default setting of SystemInit() function, refer to
   system_stm32f10x.c file
   */

  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC12 in output push/pull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

#define DELAY_DURATION  5000000

  int i;
  i = 0;

  while (1)
    {
      // Set PC12
      GPIOC ->BSRR = GPIO_Pin_12;

      Delay(DELAY_DURATION);
      // Reset PC12
      GPIOC ->BRR = GPIO_Pin_12;

      Delay(DELAY_DURATION);

      char ch;
      ch = i + ' ';
      int r = ITM_SendChar2(ch);

      i = (i + r) % 64;
    }

  return 0;
}

/**
 * @brief  Inserts a delay time.
 * @param  nCount: specifies the delay time length.
 * @retval None
 */
void
Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--)
    ;
}

// CoreSight Components: Technical Reference Manual (DDI0314H)

void
init_SWO(uint32_t SWOSpeed, uint32_t CPUSpeed)
{
  // Enable Trace
  CoreDebug ->DEMCR = CoreDebug_DEMCR_TRCENA_Msk; //1 << CoreDebug_DEMCR_TRCENA_Pos;

  // Early, since the TPIU APB registers can be read and written only
  // if the bit TRCENA of the Debug Exception and Monitor Control Register
  // (DEMCR) is set.

  // TPUI TRACE pin assignment

  // STM32 specific
  // RM0008 31.16.3 Debug MCU configuration register
  // Enable TRACE_IOEN, DBG_STANDBY, DBG_STOP, DBG_SLEEP
  // [31:8] = 0, watchdog, timers, CAN, I2C are NOT frozen
  // and continue to run when the core is halted
  // [7:6] = 0x00 TRACE_MODE=00: TRACE pin assignment for Asynchronous Mode
  // [5] = 1 TRACE_ IOEN enabled as above
  // [2] = 1 DBG_STANDBY DebugStandbymode
  // [1] = 1 DBG_STO: DebugStopmode
  // [0] = 1 DBG_SLEEP DebugSleepmode
  DBGMCU ->CR = 0x00000027;

  // SWO->SPPR Selected Pin Protocol Register,
  // STM32 TPIU "Selected PIN Protocol Register"
  // Select which protocol to use for trace output
  // [1:0] = 2: Serial Wire Output - NRZ, on PB3
  TPI ->SPPR = 0x00000002;
  // *((volatile unsigned *) (TPI_BASE + 0x0F0)) = 0x00000002;
  // *((volatile unsigned *) 0xE00400F0) = 0x00000002;

  // 31.17.8 TRACECLKIN connection inside the STM32F10xxx
  // In the STM32F10xxx, this TRACECLKIN input is internally connected to HCLK.

  // HCLK is the AHB clock

  // SWOSpeed is in Hz; compute prescaler for the 8MHz clock
  uint32_t SWOPrescaler = (CPUSpeed / SWOSpeed) - 1;

  // SWO->CODR Current Output Divisor Register,
  // STM32 TPIU "Async Clock Prescaler Register".
  // Scale the baud rate of the asynchronous output
  // [12:0]
  TPI ->ACPR = SWOPrescaler;
  // *((volatile unsigned *) (TPI_BASE + 0x010)) = SWOPrescaler;
  // *((volatile unsigned *) 0xE0040010) = SWOPrescaler;

  // TPIU Formatter and Flush Control Register, RW
  // Notice: STM32 Table 231
  // In asynchronous mode (Select_Pin_Protocol register bit1:0 <> 00),
  // bit [1] can be written to activate or not the formatter.
  // (as pe 31.17.3 TPUI formatter, this will switch to the 16 byte frames)
  TPI ->FFCR = 0x00000100;
  // *((volatile unsigned *) (TPI_BASE + 0x304)) = 0x00000100;
  // *((volatile unsigned *) 0xE0040304) = 0x00000100;

  // Note: If the formatter is bypassed, only ITM and DWT trace source passes,
  // ETM is discarded

  // RM0008: 31.14 ITM
  // The bit TRCEN of the Debug Exception and Monitor Control Register
  // must be enabled before you program or use the ITM.

  // A synchronisation packet is a time stamp packet control. It is emitted at
  // each DWT trigger. For this, the DWT must be configured to trigger the ITM:
  // the bit CYCCNTENA (bit0) of the DWT Control Register must be set. In
  // addition, the bit2 (SYNCENA) of the ITM Trace Control Register must be set.

  // ITM Lock Access Register, C5ACCE55 enables more write access to Control Register
  ITM ->LAR = 0xC5ACCE55;
  // *((volatile unsigned *) 0xE0000FB0) = 0xC5ACCE55;

  // ARMv7M: C1.7.1 Asynchronous configuration is selected by setting the TSENA
  // and SWOENA bits in the Trace Control register (see Trace Control Register
  // – ITM_TCR (0xE0000E80) on page C1-31)

  // ARMv7M: C1.7.1 Synchronisation packets should be disabled on asynchronous
  // TPIU ports. ???

  // ITM Trace Control Register
  // [22:16] ATB ID = 1
  // [9:8] = 0, no prescaler. TSPrescale = Time Stamp Prescaler
  // [4] SWOENA = 1 Enable SWV behaviour (to clock the time stamp counter by the
  // SWV clock).
  // [3] DWTENA/TXENA = 1 Enable hardware event packet emission to the TPIU from the DWT.
  // [2] SYNCENA = 1 this bit must be to 1 to enable the DWT to generate
  // synchronisation triggers so that the TPIU can then emit the synchronisation
  // packets.
  // [1] TSENA = 1 Time stamp Enable
  // [0] ITMENA = 1 Global Enable Bit of the ITM
  ITM ->TCR = 0x0001001F;
  //*((volatile unsigned *) 0xE0000E80) = 0x0001000D;

  // ITM Trace Privilege Register
  // mask to enable all 4 bytes
  ITM ->TPR = 0x0000000F;
  //*((volatile unsigned *) 0xE0000E40) = 0x0000000F;

  // ITM Trace Enable Register. Enabled tracing on stimulus ports.
  // Each bit enables the corresponding Stimulus port to generate trace.
  // Enable only stimulus port 0
  ITM ->TER = 0x00000001;
  // *((volatile unsigned *) 0xE0000E00) = 0x00000001;

  // Data Watchpoint and Trace (DWT)
  // DWT_CTRL
  // Table C1-24 ARMv7-M Architecture Reference manual ARM DDI 0403C page C1-48
  // [31:28] = 4 NUMCOMP Number of comparators available.
  // [11:10] = b00 SYNCTAP, Disabled. No synchronisation packets.
  // [9] = 1 CYCTAP, Tap at CYCCNT bit 10
  // [8:5] = 0xF POSTCNT 4-bit post-scalar counter
  // [4:1] = 0xF POSTPRESET Preset (reload) value for POSTCNT
  // [0] = 1 Enable CYCCNT

  DWT ->CTRL = 0x400003FF;
  // *((volatile unsigned *) (DWT_BASE + 0x000)) = 0x400003FF;
  // *((volatile unsigned *) 0xE0001000) = 0x400003FE;

}

uint32_t
ITM_SendChar2(uint8_t ch)
{
  uint32_t r;
  r = 0;

  if ((CoreDebug ->DEMCR & CoreDebug_DEMCR_TRCENA_Msk)&& // Trace enabled
  (ITM->TCR & ITM_TCR_ITMENA_Msk) &&// ITM enabled
  (ITM->TER & (1ul << 0)))// ITM Port #0 enabled
{  // Reading from any of the stimulus ports returns
  // the FIFO status (notFull(1) / Full(0))
  while (ITM->PORT[0].u32 == 0)
  ;

#define STIM_LEN 1
#if STIM_LEN == 1

      ITM->PORT[0].u8 = ch;
      // 01 28 01 29 01 2A

      r = 1;

#elif STIM_LEN == 2

      // 2 bytes

      uint16_t w;
      w = ch+1;
      w <<= 8;
      w |= ch;
      ITM->PORT[0].u16 = w;

      // Functional, with zero padding
      // 02 27 28 02 29 2A 02 2B 2C

      r = 3;

#elif STIM_LEN == 3

      // 3 bytes

      uint32_t w;
      w = ch+2;
      w = w << 8;
      w |= (ch+1);
      w = w << 8;
      w |= ch;
      ITM->PORT[0].u32 = w;

      // Functional, with zero padding
      // 03 27 28 29 00 03 2A 2B 2C 00

      r = 3;

#elif STIM_LEN == 4

      // 4 bytes

      uint32_t w;
      w = ch+3;
      w <<= 8;
      w |= (ch+2);
      w <<= 8;
      w |= (ch+1);
      w <<= 8;
      w |= ch;
      ITM->PORT[0].u32 = w;

      // Functional
      // 03 27 28 29 2A 03 2B 2C 2D 2E

      r = 4;

#else

      // This is a strange case inspired from
      // http://ww.segger2.com/index.php?page=Thread&threadID=1010
      // The reason for appending the 0x08 is not known

      uint16_t w;
      w = ch;
      w <<= 8;
      w |= 0x08;
      ITM->PORT[0].u16 =w;

      // 02 08 28 02 08 29 02 08 2A

      r = 1;
#endif
    }
  return r;
}

