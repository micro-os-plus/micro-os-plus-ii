# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platform.synthetic.linux',
    name='GNU/Linux platform',
    description='Support for a simple GNU/Linux environment, running as a \
command line tool, without system threading.',
    
    alias='linux',
    
    category='synthetic',

    isEnabled=False, 

    sourceFiles=[
    ],

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.architecture.synthetic.posix',
    ],
        
    requirements=[
        # use the POSIX architecture
        'enable("package.os.hal.architecture.synthetic.posix")',
        
        # use the default platform implementation
        'enable("option.os.portable.core.platform.implementation.default")',
    ],
        
    implements=[
        'interface.os.platform',
    ],

    headerDefinition='OS_INCLUDE_HAL_PLATFORM_SYNTHETIC_LINUX',
        
)
