# -*- coding: utf-8 -*-

Package(
    id = 'os.package.platforms.synthetic.osx.cl-sjlj',
    name = 'OS X command line setjump/longjump platform',
    description = 'Support for a simple OS X environment, running as a \
command line tool, without system threading.',
    
    platform = 'synthetic',

    headerDefinition = 'OS_INCLUDE_PLATFORM_SYNTHETIC_OSX_SJLJ',

    requires = [
        'os.package.hal.arch.synthetic.osx',
    ]
)