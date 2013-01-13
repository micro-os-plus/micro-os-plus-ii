# -*- coding: utf-8 -*-

Package(
    id='package.os.portable.devices.debug',
    name='Debug tracing output support',
    description='Support for the device used to output tracing info.',
    
    sourceFiles=[
        'Debug.cpp',
    ],
          
    requires=[
        'enable("package.os.portable.kernel.greeting")',
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
