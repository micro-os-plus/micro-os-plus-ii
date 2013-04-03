# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.arm.cortexm',
    name='ARM Cortex-M Architecture',
    description='Support for ARM Cortex-M processors.',
    
    category='architecture',
    
    isEnabled=False,
    
    sourceFiles=[
        'ArchitectureImplementation.cpp',
    ],
    
    implements=[
        # mark this is an architecture
        'interface.os.architecture',
    ],

    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM',
          
)
