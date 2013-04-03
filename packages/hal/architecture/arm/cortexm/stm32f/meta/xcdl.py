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
        #'OS_Arch_Implementation.cpp',
        #'OSScheduler_Arch_Implementation.cpp'
    ],
       
    requirements=[
        #'enable("package.os.hal.architecture.cortexm")',
        'enable("package.os.hal.architecture.arm.cortexm")',
    ],
 
    implements=[
        # mark this is an architecture family
        'interface.os.architecture.family',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F',

)
