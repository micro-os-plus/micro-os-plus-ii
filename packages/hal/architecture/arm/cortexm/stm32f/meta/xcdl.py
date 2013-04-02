# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.cortexm.stm32f',
    name='ST Micro ARM Cortex-M STM32F* families',
    description='Support for STM32F[124]xx ARM Cortex-M processors.',
    
    category='family',
    
    isEnabled=False,
    
    sourceFiles=[
        #'OS_Arch_Implementation.cpp',
        #'OSScheduler_Arch_Implementation.cpp'
    ],
        
    implements=[
        # mark this is an architecture family
        'interface.os.architecture.family',
    ],

)
