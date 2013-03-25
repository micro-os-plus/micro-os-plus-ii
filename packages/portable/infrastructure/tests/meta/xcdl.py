# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.infrastructure.tests',
    name='Portable infrastructure tests',
    description='.',
    
    category='tests',

    children=[
              
        Component(
            id='component.os.portable.infrastructure.tests.testsuite',
            name='Test TestSuite output',
            description='Test all output methods of the TestSuite class, \
both for stdout and xml file.',
             
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'testsuite.cpp',
            ],
        
            includeFiles=[
                'testsuite-config.py',
            ],
     
            implements=[
                'interface.os.artefact',
            ],
        ),
    ],
        
)
