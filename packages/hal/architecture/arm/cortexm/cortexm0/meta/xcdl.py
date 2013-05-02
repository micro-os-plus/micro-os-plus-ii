# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='package.os.hal.architecture.arm.cortexm0',
    name='ARM Cortex-M0 Architecture',
    description='Support for ARM Cortex-M0 processors.',

    isEnabled=False,
    implements=[
        # mark this is an architecture
        'interface.os.architecture',
    ],

    sourceFiles=[
        #'InterruptVectors.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEX_M0',
    
)
