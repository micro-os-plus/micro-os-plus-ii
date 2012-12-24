# -*- coding: utf-8 -*-

Component(
    id='component.os.platforms.synthetic.osx.cl-sjlj',
    name='OS X command line setjump/longjump platform',
    description='Support for a simple OS X environment, running as a \
command line tool, without system threading.',
    
    kind='synthetic',

    headerDefinition='OS_INCLUDE_PLATFORM_SYNTHETIC_OSX_SJLJ',

    enable=[
        'component.os.hal.arch.synthetic.osx',
    ]
)
