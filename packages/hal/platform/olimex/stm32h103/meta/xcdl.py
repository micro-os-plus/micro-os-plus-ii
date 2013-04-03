# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.olimex.stm32h103',
    name='Olimex STM32-H103 board',
    description='Support for the Olimex STM32-H103 development board, \
based on STM32F103.',

    alias='stm32h103',
        
    category='board',
    
    # platform packages shall load corresponding hal architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.stm32f',
    ],
        
    requirements=[
        'enable("package.os.hal.architecture.arm.cortexm.stm32f")',
    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_PLATFORM_OLIMEX_STM32H103',
)
