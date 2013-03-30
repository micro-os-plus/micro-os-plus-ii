# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.hal.architecture.cortexm.stm32f',
    name='ST ARM Cortex-M STM32F* families',
    description='Support for STM32F[124]xx ARM Cortex-M processors.',
    
    category='family',
    
    sourceFiles=[
        'OS_Arch_Implementation.cpp',
        'OSScheduler_Arch_Implementation.cpp'
    ],
)
