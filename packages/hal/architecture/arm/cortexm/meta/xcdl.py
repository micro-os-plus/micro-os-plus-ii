# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.arm.cortexm',
    name='ARM Cortex-M Architectures',
    description='Support for ARM Cortex-M processors.',
    
    isEnabled=False,
    
    sourceFiles=[
        'ArchitectureImplementation.cpp',
    ],
    
    copyFiles=[
        ('../ldscripts/sections.ld', 'ldscripts/'),
    ],

    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M',
    
    children=[
              
        Component(
            id='package.os.hal.architecture.arm.cortexm0',
            name='ARM Cortex-M0 Architecture',
            description='Support for ARM Cortex-M0 processors.',

            isEnabled=False,
            implements=[
                # mark this is an architecture
                'interface.os.architecture',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0',
            
        ),

        Component(
            id='package.os.hal.architecture.arm.cortexm0p',
            name='ARM Cortex-M0+ Architecture',
            description='Support for ARM Cortex-M0+ processors.',

            isEnabled=False,
            implements=[
                # mark this is an architecture
                'interface.os.architecture',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0P',
            
        ),

        Component(
            id='package.os.hal.architecture.arm.cortexm3',
            name='ARM Cortex-M3 Architecture',
            description='Support for ARM Cortex-M3 processors.',

            isEnabled=False,
            implements=[
                # mark this is an architecture
                'interface.os.architecture',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M3',
            
        ),

        Component(
            id='package.os.hal.architecture.arm.cortexm4',
            name='ARM Cortex-M4 Architecture',
            description='Support for ARM Cortex-M4 processors.',

            isEnabled=False,
            implements=[
                # mark this is an architecture
                'interface.os.architecture',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4',
            
        ),


    ],     
)
