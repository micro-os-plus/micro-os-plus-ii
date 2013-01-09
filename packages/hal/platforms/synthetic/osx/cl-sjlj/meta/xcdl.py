# -*- coding: utf-8 -*-

Package(
    id='package.os.hal.platforms.synthetic.osx.cl-sjlj',
    name='OS X command line setjump/longjump platform',
    description='Support for a simple OS X environment, running as a \
command line tool, without system threading.',
    
    category='synthetic',

    headerDefinition='OS_INCLUDE_PLATFORM_SYNTHETIC_OSX_SJLJ',

    # platform packages shall load corresponding hal packages
    loadPackages=[
        'package.os.hal.arch.synthetic.osx',
        'package.os.hal.arch.synthetic.osx.debug',
    ]
)
