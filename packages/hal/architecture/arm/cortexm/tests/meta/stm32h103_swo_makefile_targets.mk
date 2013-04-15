swo.hex: swo.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex swo.elf  "swo.hex"
	@echo 'Finished building: $@'
	@echo ' '

swo.bin: swo.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary swo.elf  "swo.bin"
	@echo 'Finished building: $@'
	@echo ' '

swo.lst: swo.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Listing'
	arm-none-eabi-objdump -h -S swo.elf > "swo.lst"
	@echo 'Finished building: $@'
	@echo ' '

swo.siz: swo.elf
	@echo 'Invoking: OS X ARM Embedded GNU Print Size'
	arm-none-eabi-size  --format=berkeley swo.elf > "swo.siz"
	@cat "swo.siz"
	@echo 'Finished building: $@'
	@echo ' '
