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
    ],

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.architecture.arm.cortexm.qemu',
    ],
        
    requirements=[
        # use the QEMU architecture definitions
        'enable("package.os.hal.architecture.arm.cortexm.qemu")',
        
        # use the custom QEMU platform
        'setValue("OS_PATH_HAL_PLATFORM_PLATFORMIMPLEMENTATION", "hal/platform/synthetic/qemu/include/PlatformImplementation.h")',
        
        'setValue("OS_STRING_PLATFORM_GREETING_FIRST", "QEMU Processor Emulator")',        
    ],
        
    implements=[
        'interface.os.platform',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_QEMU',
        
)
