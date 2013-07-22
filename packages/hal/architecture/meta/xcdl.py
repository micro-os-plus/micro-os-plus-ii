# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture',
    name='Generic architecture',
    description='Generic architecture classes.',

    children=[
              
        Component(
            id='component.os.hal.architecture.custom',
            name='Custom architecture',
            description='Custom architecture classes.',
            
            category='architecture',
                    
            isEnabled=False,
                
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_CUSTOM',
               
        ),
 
        Component(
            id='component.os.hal.architecture.family.custom',
            name='Custom architecture family',
            description='Custom architecture family classes.',
            
            isEnabled=False,
                
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_FAMILY_CUSTOM',
               
        ),
             
        Component(
            id='component.os.hal.architecture.infrastructure.testsuite.implementation.custom',
            name='Custom infrastructure unit tests implementation',
            description='Support for unit tests custom implementation.',

            isEnabled=False,

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION_CUSTOM',

        ),      

        Component(
            id='component.os.hal.architecture.diagnostics.trace.implementation.custom',
            name='Custom diagnostics trace implementation',
            description='Support for diagnostics trace custom implementation.',

            isEnabled=False,

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_DIAGNOSTICS_TRACEIMPLEMENTATION_CUSTOM',

        ),      
              
    ],
                  
)
