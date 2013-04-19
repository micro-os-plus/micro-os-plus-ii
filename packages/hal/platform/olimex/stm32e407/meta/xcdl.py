# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.olimex.stm32e407',
    name='Olimex STM32-E407 board',
    description='Support for the Olimex STM32-E407 development board, \
based on STM32F103.',

    alias='stm32e407',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        #'enable("package.os.hal.architecture.arm.cortexm.stm32f")',
        'enable("component.os.hal.architecture.arm.cortexm.stm32f407ze")',
        'enable("component.os.hal.architecture.arm.cortexm.stm32f40x.diagnostics.trace")'
    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_BOARD_OLIMEX_stm32e407',
    
    sourceFiles=[
        'PlatformImplementation.cpp',
    ],
)
