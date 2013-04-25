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
          
    requirements=[
        'enable("component.os.hal.architecture.arm.cortexm4")',
    ],
                  

    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F4',

    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f40xx',
            name='ST Micro ARM Cortex-M4 STM32F40XX family',
            description='Support for STM32F40XX connectivity line ARM Cortex-M4 processors.',
            
            isEnabled=False,
    
            sourceFiles=[
                'InterruptVectors40XX.cpp',
            ],
          
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F40XX',
                   
            children=[
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f407ze',
                    name='ST Micro ARM Cortex-M4 STM32F407ZE',
                    description='Support for STM32F407ZE ARM Cortex-M4 processors (512K flash).',
                    
                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F407ZE',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f40xE.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f407zg',
                    name='ST Micro ARM Cortex-M4 STM32F407ZG',
                    description='Support for STM32F407ZG ARM Cortex-M4 processors (1024K Flash).',
                    
                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F407ZG',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f40xG.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f407vg',
                    name='ST Micro ARM Cortex-M4 STM32F407VG',
                    description='Support for STM32F407VG ARM Cortex-M4 processors (1024K Flash).',
                    
                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F407VG',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f40xG.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                
            ],     
        ),
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f427x',
            name='ST Micro ARM Cortex-M4 STM32F427X family',
            description='Support for STM32F427X connectivity line ARM Cortex-M4 processors.',
            
            isEnabled=False,
    
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F427X',
            
            children=[
                # add
            ],
        ),

    ],
),
