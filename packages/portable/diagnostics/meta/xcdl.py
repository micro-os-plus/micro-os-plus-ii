# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.diagnostics',
    name='Diagnostics support',
    description='Support for all diagnostics functionality.',
              
    children=[
              
        Component(
            id='component.os.portable.diagnostics.trace',
            name='Diagnostics trace support',
            description='Support for trace output',
                  
            requirements=[
                # for the greeting strings
                'enable("package.os.portable.core.greeting")',
                
                # at least one implementation of the above interface
                'implementationsOf("interface.os.portable.diagnostics.trace") == 1',
            ],
                
            sourceFiles=[
                'Trace.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE',
              
            children=[
                Interface(
                    id='interface.os.portable.diagnostics.trace',
                    name='Diagnostics trace output interface',
                    description='Platform implementation for the diagnostics trace output.',
                ),
            ],
        ),
    ],
)