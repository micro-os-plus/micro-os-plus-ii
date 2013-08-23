# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm',
    name='ST Micro ARM Cortex-M3 STM32F10x library',
    description='ST Micro library for STM32F10X ARM Cortex-M processors.',
    
    category='lib',
    
    isEnabled=False,
    
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.cmsis',
            name='ST Micro ARM Cortex-M STM32F10x library CMSIS',
            description='CMSIS source code for STM32F10X.',
            
            category='cmsis',
            
            isEnabled=True,
            
            sourceFiles=[
                'system_stm32f10x.c',
            ],
        ),

        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.rcc',
            name='ST Micro ARM Cortex-M STM32F10x library RCC support',
            description='RCC source code for STM32F10X.',
            
            category='lib',
            
            isEnabled=False,
            
            sourceFiles=[
                'stm32f10x_rcc.c',
            ],
        ),
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio',
            name='ST Micro ARM Cortex-M STM32F10x library GPIO support',
            description='GPIO source code for STM32F10X.',
            
            category='lib',
            
            isEnabled=False,
            
            sourceFiles=[
                'stm32f10x_gpio.c',
            ],
                  
            requirements=[
                'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.rcc")',
            ],
        ),
              
    ],
)
