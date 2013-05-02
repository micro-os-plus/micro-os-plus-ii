# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for Olimex board STM32-P107
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32p107',
    name='Test GPIO on STM32-P107 configuration',
    description='Common definitions for Debug/Release build configurations running on STM32-P107',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.olimex.stm32p107',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.olimex.stm32p107")',
        
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio")',  
        
        # and the trace i2c bit-banged implementation
        'enable("component.os.portable.diagnostics.trace.i2c")',        
            
    ],
              
    buildFolder='stm32p107/gpio',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
        
    children=[
               
        # GNU Tools for ARM Embedded Processors on OS X
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32p107.osx.aep.gcc.debug',
            name='Debug STM32-P107 GPIO configuration with ARM Embedded GCC on OS X',
            description='Debug build configuration for GPIO.',
            
            buildConfigurationName='stm32p107_gpio_osx_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 8)',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32p107.osx.aep.gcc.release',
            name='Release STM32-P107 GPIO configuration with ARM Embedded GCC on OS X',
            description='Release build configuration for GPIO.',
            
            buildConfigurationName='stm32p107_gpio_osx_aep_gcc_Release',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),

        # GNU Tools for ARM Embedded Processors on GNU/Linux
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32p107.linux.aep.gcc.debug',
            name='Debug STM32-P107 GPIO configuration with ARM Embedded GCC on GNU/Linux',
            description='Debug build configuration for GPIO.',
            
            buildConfigurationName='stm32p107_gpio_linux_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 8)',
            ],
              
            toolchain='toolchain.linux.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.gpio.stm32p107.linux.aep.gcc.release',
            name='Release STM32-P107 GPIO configuration with ARM Embedded GCC on GNU/Linux',
            description='Release build configuration for GPIO.',
            
            buildConfigurationName='stm32p107_gpio_linux_aep_gcc_Release',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Release',

            toolchain='toolchain.linux.aep.arm.gcc.release',
        ),

    ],
)
