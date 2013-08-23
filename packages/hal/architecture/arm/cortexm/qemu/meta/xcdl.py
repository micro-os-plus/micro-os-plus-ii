# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.arm.cortexm.qemu',
    name='QEMU Cortex-M3 family',
    description='Support for QEMU ARM Cortex-M3 processors.',
    
    category='family',
    
    isEnabled=False,
    
    sourceFiles=[
        #'FamilyBase.cpp',
        'FamilyImplementation.cpp',
        'InterruptVectors.cpp',
    ],

    loadPackages=[
        'package.os.hal.architecture.arm.cortexm',
    ],
       
    requirements=[
        'enable("package.os.hal.architecture.arm.cortexm3")',
    ],
 
    implements=[
        # mark this is an architecture family
        'interface.os.architecture.family',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_MCU_FAMILY_QEMU',

    copyFiles=[
        ('../ldscripts/qemu.ld', 'ldscripts/mem_layout.ld'),
    ],

)

