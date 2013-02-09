# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.infra',
    name='Infrastructure support',
    description='Support for all infrastructure functionality.',
    
          
    children=[
              
        Component(
            id='component.os.portable.infra.testsuite',
            name='Infrastructure unit tests support',
            description='Support for unit tests',
                  
            requires=[
                'enable("package.os.portable.core.greeting")',
                'implementationsOf("interface.os.portable.infra.testsuite") == 1',
            ],
                
            sourceFiles=[
                'TestSuite.cpp',
                'TestSuiteImplementation.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_INFRA_TESTSUITE',
              
            children=[
                Interface(
                    id='interface.os.portable.infra.testsuite',
                    name='Unit tests output interface',
                    description='Platform implementation for the unit tests output.',
                ),
            ],
        ),
    ],
)
