# -*- coding: utf-8 -*-

Component(
    id='component.os.portable.devices.debug',
    name='Debug tracing output',
    description='Support for the device used to output tracing info.',
    
    compile=[
        'Debug.cpp',
    ],
          
    scripts=[
        'tests/conversions/meta/xcdl.py'
    ],
)
