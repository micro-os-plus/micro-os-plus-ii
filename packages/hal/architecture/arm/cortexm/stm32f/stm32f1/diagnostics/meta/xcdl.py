# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics',
    name='ST Micro STM32F10X diagnostics implementation',
    description='Implementation for the diagnostics classes.',

    # DISABLED!
    isEnabled=False,
    #isEnabled=True,
            
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace',
            name='ST Micro STM32F10X trace implementation',
            description='Implementation to output data from the trace class.',
            
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_STM32F_STM32F1_DIAGNOSTICS_TRACEIMPLEMENTATION',
        
            implements=[
                'interface.os.portable.diagnostics.trace',
            ],
                  
            sourceFiles=[
                'TraceImplementation.cpp',
            ],
            
            activeIf=[
                'component.os.portable.diagnostics.trace',
            ],
            
        ),
    ],
)
