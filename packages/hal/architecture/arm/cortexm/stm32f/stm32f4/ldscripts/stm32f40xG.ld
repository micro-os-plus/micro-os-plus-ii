/* Memory layout for STM32F4[01]xG */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1024K
  CCMRAM (xrw) : ORIGIN = 0x10000000, LENGTH = 64K
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
  
  FLASHB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB0 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB1 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB2 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  EXTMEMB3 (rx) : ORIGIN = 0x00000000, LENGTH = 0
  MEMORY_ARRAY (xrw)  : ORIGIN = 0x20002000, LENGTH = 32
}
