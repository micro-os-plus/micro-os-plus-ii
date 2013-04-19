# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm4',
    name='ARM Cortex-M4 Architecture',
    description='Support for ARM Cortex-M4 processors.',

    isEnabled=False,
    implements=[
        # mark this is an architecture
        'interface.os.architecture',
    ],

    sourceFiles=[
        'InterruptVectors.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M4',
    
)
