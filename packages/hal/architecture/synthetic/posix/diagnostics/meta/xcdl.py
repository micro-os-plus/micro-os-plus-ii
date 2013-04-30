# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.synthetic.posix.diagnostics',
    name='Synthetic POSIX diagnostics implementation',
    description='Implementation for the diagnostics classes.',
            
    children=[
              
        Component(
            id='component.os.hal.architecture.synthetic.posix.diagnostics.trace',
            name='Synthetic POSIX trace implementation',
            description='Implementation to output data from the trace class.',
            
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX_DIAGNOSTICS_TRACEIMPLEMENTATION',
        
            implements=[
                'interface.os.portable.diagnostics.trace',
            ],
                  
            sourceFiles=[
                'TraceImplementation.cpp',
            ],
            
            copyFiles=[
                ('../include/TraceImplementation.h','include/hal/architecture/diagnostics/include/TraceImplementation.h'),
            ],
                  
            activeIf=[
                'component.os.portable.diagnostics.trace',
            ],
            
        ),
    ],
)
