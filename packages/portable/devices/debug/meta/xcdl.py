# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.devices.debug',
    name='Debug tracing output support',
    description='Support for the device used to output tracing info.',
    
    sourceFiles=[
        'Debug.cpp',
    ],
          
    requires=[
        'enable("package.os.portable.core.greeting")',
        'implementationsOf("interface.os.portable.devices.debug") == 1',
    ],
          
    children=[
        Interface(
            id='interface.os.portable.devices.debug',
            name='Debug tracing output interface',
            description='Platform implementation for the Debug tracing output.',
        ),
    ],
)
