minimal.hex: minimal.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex minimal.elf  "minimal.hex"
	@echo 'Finished building: $@'
	@echo ' '

minimal.lst: minimal.elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Listing'
	arm-none-eabi-objdump -h -S minimal.elf > "minimal.lst"
	@echo 'Finished building: $@'
	@echo ' '

minimal.siz: minimal.elf
	@echo 'Invoking: OS X ARM Embedded GNU Print Size'
	arm-none-eabi-size  --format=berkeley minimal.elf > "minimal.siz"
	@cat "minimal.siz"
	@echo 'Finished building: $@'
	@echo ' '
