# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.olimex.olimexinostm32',
    name='Olimex OLIMEXINO-STM32 board',
    description='Support for the Olimex OLIMEXINO-STM32 development board, \
based on STM32F103.',

    alias='olimexinostm32',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        'enable("component.os.hal.architecture.arm.cortexm.stm32f103rb")',
        
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "Olimex OLIMEXINO-STM32 development board")',        
        'setValue("OS_STRING_PLATFORM_GREETING_SECOND", "STM32F103RB Cortex-M3")',        

        'enable("component.os.portable.core.peripheral.activeled")',
        'setValue("OS_INTEGER_ACTIVELED_PORT", 0)', # port A
        'setValue("OS_INTEGER_ACTIVELED_BIT", 5)',        
        'setValue("OS_BOOL_ACTIVELED_ISACTIVELOW", False)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT", 0)', # port A
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT", 0)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT", 0)', # port A
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT", 8)',        

    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_BOARD_OLIMEX_OLIMEXINOSTM32',
    
    sourceFiles=[
        #'PlatformImplementation.cpp',
    ],
        
    copyFiles=[
        ('../include/PlatformImplementation.h', 'include/hal/platform/include/PlatformImplementation.h'),
        #('/hal/platform/olimex/olimexinostm32/include/PlatformImplementation.h', 'include/hal/platform/include/PlatformImplementation.h'),
    ],
)
