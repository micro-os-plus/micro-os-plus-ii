# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.tests',
    name='Test portable classes',
    description='General tests.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.portable.tests.minimal',
            name='Test minimal configuration',
            description='Test build a minimal application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'minimal.cpp',
            ],
                  
            includeFiles=[
                'minimal-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
