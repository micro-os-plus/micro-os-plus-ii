# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.qemu.diagnostics',
    name='QEMU Cortex-M diagnostics implementation',
    description='Implementation for the diagnostics classes.',

    # must be DISABLED!
    isEnabled=False,
    #isEnabled=True,
            
    children=[

        Component(
            id='component.os.hal.architecture.arm.cortexm.qemu.diagnostics.semihosting',
            name='QEMU Cortex-M semihosting implementation',
            description='Semihosting output functions.',

            isEnabled=False,
            
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_SEMIHOSTING',
        
            sourceFiles=[
                'SemiHosting.cpp',
            ],
                  
            requirements=[
                'enable("component.os.hal.architecture.arm.cortexm.diagnostics.semihosting")',
            ],
        ),
              
        Component(
            id='component.os.hal.architecture.arm.cortexm.qemu.diagnostics.trace.semihosting',
            name='QEMU Cortex-M semihosting trace implementation',
            description='Implementation to output data from the trace class.',

            isEnabled=False,
            
            headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ARM_CORTEXM_QEMU_DIAGNOSTICS_TRACEIMPLEMENTATIONSEMIHOSTING',
        
            implements=[
                'interface.os.portable.diagnostics.trace',
            ],
                  
            sourceFiles=[
                'TraceImplementationSemihosting.cpp',
            ],
            
            activeIf=[
                'component.os.portable.diagnostics.trace',
            ],
            
            requirements=[
                'enable("component.os.hal.architecture.arm.cortexm.qemu.diagnostics.semihosting")',
            ],

        ),
    ],
)
