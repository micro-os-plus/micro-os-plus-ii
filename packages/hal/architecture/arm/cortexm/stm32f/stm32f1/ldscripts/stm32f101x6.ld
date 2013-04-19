/* Memory layout for STM32F101[CR]6 */

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 32K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 6K
}
