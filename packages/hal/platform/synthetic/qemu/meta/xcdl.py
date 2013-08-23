# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.synthetic.qemu',
    name='QEMU platform',
    description='Support for the QEMU environment.',
    
    alias='qemu',
    
    category='synthetic',

    isEnabled=False, 

    sourceFiles=[
        'PlatformImplementation.cpp',
    ],

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.qemu',
    ],
        
    requirements=[
        'enable("package.os.hal.architecture.arm.cortexm.qemu")',
        
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "QEMU Processor Emulator")',        
        #'setValue("OS_STRING_PLATFORM_GREETING_SECOND", "Synthetic Cortex-M3")',        

    ],
        
    implements=[
        'interface.os.platform',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_QEMU',
        
    copyFiles=[
        ('../include/PlatformImplementation.h', 'include/hal/platform/include/PlatformImplementation.h'),
    ],
)
