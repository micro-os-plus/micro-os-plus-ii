# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.synthetic.osx',
    name='OS X platform',
    description='Support for a simple OS X environment, running as a \
command line tool, without system threading.',
    
    alias='osx',
    
    category='synthetic',

    isEnabled=False, 

    sourceFiles=[
        'PlatformImplementation.cpp',
    ],

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.architecture.synthetic.posix',
        #'package.os.hal.architecture.synthetic.osx',
    ],
        
    requirements=[
        'enable("package.os.hal.architecture.synthetic.posix")',
    ],
        
    implements=[
        'interface.os.platform',
    ],
        
    headerDefinition='OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_OSX',
        
    copyFiles=[
        ('../include/PlatformImplementation.h', 'include/hal/platform/include/PlatformImplementation.h'),
    ],
)
