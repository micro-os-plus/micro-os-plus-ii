# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

              
Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f4',
    name='ST Micro ARM Cortex-M4 STM32F4 family',
    description='Support for STM32F4XX ARM Cortex-M4 processors.',
    
    isEnabled=False,

    sourceFiles=[
        'InterruptVectors.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F4',

    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f40x',
            name='ST Micro ARM Cortex-M4 STM32F40X family',
            description='Support for STM32F40X Medium Density ARM Cortex-M3 processors.',
            
            isEnabled=False,
    
            requirements=[
                'enable("component.os.hal.architecture.arm.cortexm4")',
            ],
                  
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F40X',
                   
            children=[
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f407ze',
                    name='ST Micro ARM Cortex-M4 STM32F407ZE',
                    description='Support for STM32F407ZE ARM Cortex-M4 processors.',
                    
                    isEnabled=False,
                    
                    sourceFiles=[
                        'InterruptVectors0X.cpp',
                    ],
            
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F407ZE',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f40xE.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                
            ],     
        ),

    ],
),
