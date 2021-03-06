# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.infrastructure',
    name='Cortex-M infrastructrue implementation',
    description='Implementation for the infrastructure classes.',
            
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.i2c',
            name='Trace i2c Cortex-M unit tests implementation',
            description='Implementation to output data from the unit tests.',
            
            isEnabled=False, 
            activeIf=[
                'component.os.portable.infrastructure.testsuite',
            ],
            
            implements=[
                'interface.os.portable.infrastructure.testsuite',
            ],
                  
            sourceFiles=[
                'TestSuiteImplementationI2c.cpp',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONI2C',
                                
        ),

        Component(
            id='component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.semihosting',
            name='Trace Semi-hosting Cortex-M unit tests implementation',
            description='Implementation to output data from the unit tests.',
            
            isEnabled=False, 
            activeIf=[
                'component.os.portable.infrastructure.testsuite',
            ],
            
            implements=[
                'interface.os.portable.infrastructure.testsuite',
            ],
                  
            sourceFiles=[
                'TestSuiteImplementationSemiHosting.cpp',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_INFRASTRUCTURE_TESTSUITEIMPLEMENTATIONSEMIHOSTING',
                                
        ),
    
    ],
)
