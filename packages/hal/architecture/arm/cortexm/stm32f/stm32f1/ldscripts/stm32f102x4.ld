/* Memory layout for STM32F102[CR]4 */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 16K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 4K
}
