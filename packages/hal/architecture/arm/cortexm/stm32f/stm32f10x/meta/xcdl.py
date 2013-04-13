# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

              
Component(
    id='package.os.hal.architecture.arm.cortexm.stm32f10x',
    name='ST Micro ARM Cortex-M STM32F10X family',
    description='Support for STM32F10X ARM Cortex-M processors.',
    
    isEnabled=False,

    sourceFiles=[
        'InterruptVectors.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X',

    children=[
              
        Component(
            id='package.os.hal.architecture.arm.cortexm.stm32f10x.md',
            name='ST Micro ARM Cortex-M STM32F10X MD family',
            description='Support for STM32F10X Medium Density ARM Cortex-M3 processors.',
            
            isEnabled=False,
    
            requirements=[
                'enable("package.os.hal.architecture.arm.cortexm3")',
            ],
                  
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD',
                   
            children=[
                      
                Component(
                    id='package.os.hal.architecture.arm.cortexm.stm32f103rb',
                    name='ST Micro ARM Cortex-M STM32F103RB',
                    description='Support for STM32F10RB ARM Cortex-M3 processors.',
                    
                    isEnabled=False,
                    
                    sourceFiles=[
                        'InterruptVectorsMD.cpp',
                    ],
            
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F103RB',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f103xB.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                
            ],     
        ),

    ],
),
