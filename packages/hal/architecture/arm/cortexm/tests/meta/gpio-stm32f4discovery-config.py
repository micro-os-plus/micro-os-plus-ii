# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for ST board STM32F4DISCOVERY
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32f4discovery',
    name='Test GPIO on STM32F4DISCOVERY configuration',
    description='Common definitions for Debug/Release build configurations running on STM32F4DISCOVERY',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.stm.stm32f4discovery',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.stm.stm32f4discovery")',
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.gpio")',              

        'enable("component.os.portable.diagnostics.trace.i2c")',        
    ],
              
    buildFolder='stm32f4discovery/gpio',
    
    buildTargetCpuOptions='-mcpu=cortex-m4 -mthumb -mfloat-abi=soft',
    
    children=[
               
        # GNU Tools for ARM Embedded Processors on OS X
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32f4discovery.osx.aep.gcc.debug',
            name='Debug STM32F4DISCOVERY GPIO configuration with ARM Embedded GCC on OS X',
            description='Debug build configuration for GPIO.',
            
            buildConfigurationName='stm32f4discovery_gpio_osx_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 4)',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32f4discovery.osx.aep.gcc.release',
            name='Release STM32F4DISCOVERY GPIO configuration with ARM Embedded GCC on OS X',
            description='Release build configuration for GPIO.',
            
            buildConfigurationName='stm32f4discovery_gpio_osx_aep_gcc_Release',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
               
        # GNU Tools for ARM Embedded Processors on GNU/Linux
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32f4discovery.linux.aep.gcc.debug',
            name='Debug STM32F4DISCOVERY GPIO configuration with ARM Embedded GCC on GNU/Linux',
            description='Debug build configuration for GPIO.',
            
            buildConfigurationName='stm32f4discovery_gpio_linux_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 4)',
            ],
              
            toolchain='toolchain.linux.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32f4discovery.linux.aep.gcc.release',
            name='Release STM32F4DISCOVERY GPIO configuration with ARM Embedded GCC on GNU/Linux',
            description='Release build configuration for GPIO.',
            
            buildConfigurationName='stm32f4discovery_gpio_linux_aep_gcc_Release',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Release',

            toolchain='toolchain.linux.aep.arm.gcc.release',
        ),

    ],
)
