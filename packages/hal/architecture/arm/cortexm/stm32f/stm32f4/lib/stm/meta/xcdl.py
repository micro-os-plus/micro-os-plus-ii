# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm',
    name='ST Micro ARM Cortex-M4 STM32F40x library',
    description='ST Micro library for STM32F40X ARM Cortex-M processors.',
    
    category='lib',
    
    isEnabled=True,
    
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.cmsis',
            name='ST Micro ARM Cortex-M4 STM32F40x library CMSIS',
            description='CMSIS source code for STM32F40X.',
            
            category='cmsis',
            
            isEnabled=True,
            
            sourceFiles=[
                'system_stm32f4xx.c',
            ],
        ),

        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.rcc',
            name='ST Micro ARM Cortex-M4 STM32F40x library RCC support',
            description='RCC source code for STM32F40X.',
            
            category='lib',
            
            isEnabled=False,
            
            sourceFiles=[
                'stm32f4xx_rcc.c',
            ],
        ),
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.gpio',
            name='ST Micro ARM Cortex-M4 STM32F40x library GPIO support',
            description='GPIO source code for STM32F40X.',
            
            category='lib',
            
            isEnabled=False,
            
            sourceFiles=[
                'stm32f4xx_gpio.c',
            ],
                  
            requirements=[
                'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.rcc")',
            ],
        ),
              
    ],
)
