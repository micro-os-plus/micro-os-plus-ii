# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.core.tests',
    name='Test portable core classes',
    description='Core tests.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.portable.core.tests.threads',
            name='Test threads configuration',
            description='Test thread creation application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'threads.cpp',
                'FakeScheduler.cpp'
            ],
                  
            includeFiles=[
                'threads-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),

        Component(
            id='component.os.portable.core.tests.yields',
            name='Test yields configuration',
            description='Test build a minimal application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'yields.cpp',
            ],
                  
            includeFiles=[
                'yields-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
