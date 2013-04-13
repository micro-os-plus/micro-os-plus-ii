# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.arm.cortexm.stm32f',
    name='ST Micro ARM Cortex-M STM32F* families',
    description='Support for STM32F[124]xx ARM Cortex-M processors.',
    
    category='family',
    
    isEnabled=False,
    
    sourceFiles=[
        'FamilyImplementation.cpp',
    ],
       
    requirements=[
        'enable("package.os.hal.architecture.arm.cortexm")',
    ],
 
    implements=[
        # mark this is an architecture family
        'interface.os.architecture.family',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F',

)
