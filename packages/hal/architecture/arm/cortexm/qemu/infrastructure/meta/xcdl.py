# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.qemu.infrastructure',
    name='QEMU Cortex-M infrastructrue implementation',
    description='Implementation for the infrastructure classes.',
            
    children=[
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.qemu.infrastructure.testsuite',
            name='QEMU Cortex-M unit tests implementation',
            description='Implementation to output data from the unit tests.',
            
            isEnabled=True, 
            # always enabled, but active only when portable part is active
            activeIf=[
                'component.os.portable.infrastructure.testsuite',
            ],
            
            implements=[
                'interface.os.portable.infrastructure.testsuite',
            ],
                  
            sourceFiles=[
                'TestSuiteImplementation.cpp',
            ],

            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_INFRASTRUCTURE_TESTSUITEIMPLEMENTATION',
                                
        ),
    ],
)
