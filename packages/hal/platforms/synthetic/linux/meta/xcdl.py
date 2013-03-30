# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.platforms.synthetic.linux',
    name='GNU/Linux platform',
    description='Support for a simple GNU/Linux environment, running as a \
command line tool, without system threading.',
    
    category='synthetic',

    isEnabled=False, 

    headerDefinition='OS_INCLUDE_PLATFORM_SYNTHETIC_LINUX',

    # platform packages shall load corresponding architecture packages
    loadPackages=[
        'package.os.hal.arch.synthetic.posix',
        #'package.os.hal.arch.synthetic.linux',
    ],
        
    requirements=[
        'enable("package.os.hal.arch.synthetic.posix")',
    ],
        
    implements=[
        'interface.os.platform',
    ],
)
