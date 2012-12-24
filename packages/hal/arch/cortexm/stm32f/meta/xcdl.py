# -*- coding: utf-8 -*-

Component(
    id='component.os.hal.arch.cortexm.stm32f',
    name='ST ARM Cortex-M STM32F* families',
    description='Support for STM32F[124]xx ARM Cortex-M processors.',
    
    kind='family',
    
    compile=[
        'OS_Arch_Implementation.cpp',
        'OSScheduler_Arch_Implementation.cpp'
    ],
)
