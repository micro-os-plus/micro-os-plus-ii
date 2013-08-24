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
        'TimerTicksImplementation.cpp',
    ],
    
    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M',
    
    children=[

        Option(
            id='option.os.hal.architecture.arm.cortexm.platform.implementation.default',
            name='Use the default Cortex-M platform implementation definitions',
            description='Default platform implementation.',

            isEnabled=False,
                    
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_PLATFORMIMPLEMENTATIONDEFAULT',
        ),

        Component(
            id='component.os.hal.architecture.arm.cortexm.ldscript',
            name='ARM Cortex-M generic linker script',
            description='The linker script sections.',

            isEnabled=True,
            copyFiles=[
                ('../ldscripts/sections.ld', 'ldscripts/'),
            ],            
        ),
            
        # TODO: move this to a separate folder  
        Component(
            id='component.os.hal.architecture.arm.cortexm0p',
            name='ARM Cortex-M0+ Architecture',
            description='Support for ARM Cortex-M0+ processors.',

            isEnabled=False,
            implements=[
                # mark this is an architecture
                'interface.os.architecture',
            ],

            sourceFiles=[
                'CM0InterruptVectors.cpp',
            ],
                  
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0P',
            
        ),

    ],     
)
