# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.olimex.stm32e407',
    name='Olimex STM32-E407 board',
    description='Support for the Olimex STM32-E407 development board, based on STM32F407.',

    alias='stm32e407',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        'enable("component.os.hal.architecture.arm.cortexm.stm32f407zg")',
              
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "Olimex SMT32-E407 development board")',        
        'setValue("OS_STRING_PLATFORM_GREETING_SECOND", "STM32F407ZG Cortex-M4")',        

        'enable("component.os.portable.core.peripheral.activeled")',
        'setValue("OS_INTEGER_ACTIVELED_PORT", 2)', # port C
        'setValue("OS_INTEGER_ACTIVELED_BIT", 13)',        
        'setValue("OS_BOOL_ACTIVELED_ISACTIVELOW", True)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT", 15)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT", 14)',        

    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_BOARD_OLIMEX_STM32E407',
    
    sourceFiles=[
    ],
        
    copyFiles=[
        ('/hal/architecture/arm/cortexm/include/PlatformImplementationDefault.h', 'include/hal/platform/include/PlatformImplementation.h'),
    ],
)
