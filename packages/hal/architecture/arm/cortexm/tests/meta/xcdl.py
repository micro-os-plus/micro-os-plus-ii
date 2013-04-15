# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.arm.cortexm.tests',
    name='Test ARM Cortex-M classes',
    description='General tests.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.hal.architecture.arm.cortexm.tests.cmsis',
            name='Test ARM Cortex-M CMSIS configuration',
            description='Test build a minimal application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'cmsis.cpp',
            ],
                  
            includeFiles=[
                'cmsis-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),

        Component(
            id='component.os.hal.architecture.arm.cortexm.tests.swo',
            name='Test ARM Cortex-M SWO configuration',
            description='Test build a SWO application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'swo.cpp',
            ],
                  
            includeFiles=[
                'swo-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
