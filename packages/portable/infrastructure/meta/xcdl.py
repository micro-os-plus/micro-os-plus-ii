# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.infrastructure',
    name='Infrastructure support',
    description='Support for all infrastructure functionality.',
          
    children=[
              
        Component(
            id='component.os.portable.infrastructure.testsuite',
            name='Infrastructure unit tests support',
            description='Support for unit tests',
                  
            isEnabled=False, 

            requirements=[
                # for the greeting strings
                'enable("package.os.portable.core.greeting")',

                'implementationsOf("interface.os.portable.infrastructure.testsuite") == 1',
            ],
                
            sourceFiles=[
                'TestSuite.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_INFRASTRUCTURE_TESTSUITE',
              
            children=[
                      
                Interface(
                    id='interface.os.portable.infrastructure.testsuite',
                    name='Unit tests output interface',
                    description='Platform implementation for the unit tests output.',
                ),
                      
            ],
        ),
    ],
)
