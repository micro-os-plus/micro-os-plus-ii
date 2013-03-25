# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.diagnostics.tests',
    name='Test diagnostics trace classes',
    description='Test the diagnostics trace specific classes.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.portable.diagnostics.tests.trace',
            name='Test Trace',
            description='Test some methods of the Trace class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'trace.cpp',
            ],
                  
            includeFiles=[
                'trace-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
