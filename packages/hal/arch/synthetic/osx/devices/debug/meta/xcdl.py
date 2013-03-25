# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.arch.synthetic.osx.debug',
    name='Synthetic OS X architecture debug implementation',
    description='Implementation for the debug device.',
    
    headerDefinition='OS_INCLUDE_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUGIMPLEMENTATION',

    implements=[
        'interface.os.portable.devices.debug',
    ],
          
    sourceFiles=[
        'DebugImplementation.cpp',
    ],
)
