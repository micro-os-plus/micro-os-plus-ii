# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.platform.olimex.stm32h103',
    name='Olimex STM32-H103 board diagnostics implementation',
    description='Implementation for the diagnostics classes.',
     
    isEnabled=False,       
    children=[
              
        Component(
            id='component.os.hal.platform.olimex.stm32h103.diagnostics.trace',
            name='Olimex STM32-H103 board trace implementation',
            description='Implementation to output data from the trace class.',
            
            headerDefinition='OS_INCLUDE_HAL_PLATFORM_OLIMEX_STM32H103_DIAGNOSTICS_TRACEIMPLEMENTATION',
        
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
