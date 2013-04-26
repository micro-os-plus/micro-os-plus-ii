# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.stm.stm32f4discovery',
    name='ST STM32F4DISCOVERY board',
    description='Support for the ST STM32F4DISCOVERY development board, based on STM32F407.',

    alias='stm32f4discovery',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        'enable("component.os.hal.architecture.arm.cortexm.stm32f407vg")',
        
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "ST STM32F4DISCOVERY development board")',        
        'setValue("OS_STRING_PLATFORM_GREETING_SECOND", "STM32F407VG Cortex-M4")',        

        'enable("component.os.portable.core.peripheral.activeled")',
        'setValue("OS_INTEGER_ACTIVELED_PORT", 3)', # port D 
        'setValue("OS_INTEGER_ACTIVELED_BIT", 12)',        
        'setValue("OS_BOOL_ACTIVELED_ISACTIVELOW", False)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT", 11)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT", 10)',        

    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_BOARD_STM_STM32F4DISCOVERY',
    
    sourceFiles=[
        'PlatformImplementation.cpp',
    ],
)
