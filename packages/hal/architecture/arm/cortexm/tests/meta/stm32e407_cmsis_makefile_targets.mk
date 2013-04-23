cmsis.hex: cmsis.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex cmsis.elf  "cmsis.hex"
	@echo 'Finished building: $@'
	@echo ' '

cmsis.bin: cmsis.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary cmsis.elf  "cmsis.bin"
	@echo 'Finished building: $@'
	@echo ' '

cmsis.lst: cmsis.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Listing'
	arm-none-eabi-objdump -h -S cmsis.elf > "cmsis.lst"
	@echo 'Finished building: $@'
	@echo ' '

cmsis.siz: cmsis.elf
	@echo 'Invoking: OS X ARM Embedded GNU Print Size'
	arm-none-eabi-size  --format=berkeley cmsis.elf > "cmsis.siz"
	@cat "cmsis.siz"
	@echo 'Finished building: $@'
	@echo ' '
