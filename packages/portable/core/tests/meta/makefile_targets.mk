$(TARGET_NAME).hex: $(TARGET_NAME).elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex $(TARGET_NAME).elf  "$(TARGET_NAME).hex"
	@echo 'Finished building: $@'
	@echo ' '

$(TARGET_NAME).bin: $(TARGET_NAME).elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary $(TARGET_NAME).elf  "$(TARGET_NAME).bin"
	@echo 'Finished building: $@'
	@echo ' '

$(TARGET_NAME).lst: $(TARGET_NAME).elf
	@echo 'Invoking: OS X ARM Embedded GNU Create Listing'
	arm-none-eabi-objdump -h -S $(TARGET_NAME).elf > "$(TARGET_NAME).lst"
	@echo 'Finished building: $@'
	@echo ' '

$(TARGET_NAME).siz: $(TARGET_NAME).elf
	@echo 'Invoking: OS X ARM Embedded GNU Print Size'
	arm-none-eabi-size  --format=berkeley $(TARGET_NAME).elf > "$(TARGET_NAME).siz"
	@cat "$(TARGET_NAME).siz"
	@echo 'Finished building: $@'
	@echo ' '
