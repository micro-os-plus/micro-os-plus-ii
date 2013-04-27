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
                'simpleLed.cpp',
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
            description='Test sending characters over SWO.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'swo.cpp',
                'simpleLed.cpp',
            ],
                  
            includeFiles=[
                'swo-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.tests.semihosting',
            name='Test ARM Cortex-M semihosting configuration',
            description='Test sending characters over semihosting.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'semihosting.cpp',
                'simpleLed.cpp',
                'semihosting/sh_cmd.s',
                'semihosting/semihosting.c',
            ],
                  
            includeFiles=[
                'semihosting-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
