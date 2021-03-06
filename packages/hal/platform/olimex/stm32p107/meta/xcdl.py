# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.olimex.stm32p107',
    name='Olimex STM32-P107 board',
    description='Support for the Olimex STM32-P107 development board, \
based on STM32F103.',

    alias='stm32p107',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        #'enable("package.os.hal.architecture.arm.cortexm.stm32f")',
        'enable("component.os.hal.architecture.arm.cortexm.stm32f107vc")',
        #'enable("component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace")',
        
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "Olimex SMT32-P107 development board")',        
        'setValue("OS_STRING_PLATFORM_GREETING_SECOND", "STM32F107VC Cortex-M3")',        

        'enable("component.os.portable.core.peripheral.activeled")',
        'setValue("OS_INTEGER_ACTIVELED_PORT", 2)', # port C
        'setValue("OS_INTEGER_ACTIVELED_BIT", 6)',        
        'setValue("OS_BOOL_ACTIVELED_ISACTIVELOW", False)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT", 15)',        

        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT", 3)', # port D
        'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT", 14)',        

    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_BOARD_OLIMEX_STM32P107',
    
    sourceFiles=[
    ],
        
    copyFiles=[
        ('/hal/architecture/arm/cortexm/include/PlatformImplementationDefault.h', 'include/hal/platform/include/PlatformImplementation.h'),
    ],
)
