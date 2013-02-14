# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.hal.arch.synthetic.posix.infrastructure',
    name='Synthetic POSIX infrastructrue implementation',
    description='Implementation for the infrastructure classes.',
            
    children=[
              
        Component(
            id='component.os.hal.arch.synthetic.posix.infrastructure.testsuite',
            name='Synthetic POSIX unit tests implementation',
            description='Implementation to output data from the unit tests.',
            
            headerDefinition='OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION',
        
            implements=[
                'interface.os.portable.infrastructure.testsuite',
            ],
                  
            sourceFiles=[
                'TestSuiteImplementation.cpp',
            ],
            
        ),
    ],
)
