# -*- coding: utf-8 -*-

Package(
    id='package.os.portable.devices.debug',
    name='Debug tracing output',
    description='Support for the device used to output tracing info.',
    
    compile=[
        'Debug.cpp',
    ],
          
    scripts=[
        'tests/conversions/meta/xcdl.py'
    ],
          
    children=[
        Interface(
            id='interface.os.portable.devices.debug',
            name='Debug tracing output implementation',
            description='Platform implementation for the Debug tracing output.',
        ),
    ],
)
