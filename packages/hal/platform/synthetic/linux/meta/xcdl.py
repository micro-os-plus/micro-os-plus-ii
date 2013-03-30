# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.synthetic.linux',
    name='GNU/Linux platform',
    description='Support for a simple GNU/Linux environment, running as a \
command line tool, without system threading.',
    
    category='synthetic',

    isEnabled=False, 

    sourceFiles=[
        'PlatformImplementation.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_LINUX',

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.architecture.synthetic.posix',
        #'package.os.hal.architecture.synthetic.linux',
    ],
        
    requirements=[
        'enable("package.os.hal.architecture.synthetic.posix")',
    ],
        
    implements=[
        'interface.os.platform',
    ],
)
