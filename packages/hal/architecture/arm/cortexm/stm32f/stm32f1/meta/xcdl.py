# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

              
Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f1',
    name='ST Micro ARM Cortex-M3 STM32F10X family',
    description='Support for STM32F10X ARM Cortex-M processors.',
    
    isEnabled=False,

    sourceFiles=[
        #'InterruptVectors.cpp',
        'FamilyImplementation.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F1',

    copyFiles=[
        ('../include/FamilyImplementation.h', 'include/hal/architecture/include/FamilyImplementation.h'),
    ],
          
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f10x.md',
            name='ST Micro ARM Cortex-M3 STM32F10X MD family',
            description='Support for STM32F10X Medium Density ARM Cortex-M3 processors.',
            
            isEnabled=False,
    
            requirements=[
                'enable("package.os.hal.architecture.arm.cortexm3")',
            ],
                  
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_MD',
               
            copyFiles=[
                ('../include/InterruptNumbersMD.h','include/hal/architecture/include/InterruptNumbers.h'),
            ],
                
            children=[
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f103rb',
                    name='ST Micro ARM Cortex-M3 STM32F103RB',
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

        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f10x.cl',
            name='ST Micro ARM Cortex-M3 STM32F10X CL family',
            description='Support for STM32F10X Connectivity Line ARM Cortex-M3 processors.',
            
            isEnabled=False,
    
            requirements=[
                'enable("package.os.hal.architecture.arm.cortexm3")',
            ],
                  
            headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_STM32F10X_CL',

            copyFiles=[
                ('../include/InterruptNumbersCL.h','include/hal/architecture/include/InterruptNumbers.h'),
            ],
                                   
            children=[
                      
                Component(
                    id='component.os.hal.architecture.arm.cortexm.stm32f107vc',
                    name='ST Micro ARM Cortex-M3 STM32F103VC',
                    description='Support for STM32F10VC ARM Cortex-M3 processors.',
                    
                    isEnabled=False,
                    
                    sourceFiles=[
                        'InterruptVectorsCL.cpp',
                    ],
            
                    headerDefinition='OS_INCLUDE_HAL_MCU_DEVICE_STM32F103VC',
                    
                    copyFiles=[
                        ('../ldscripts/stm32f107xC.ld', 'ldscripts/mem_layout.ld'),
                    ],       
                ),
                
            ],     
        ),

    ],
),
