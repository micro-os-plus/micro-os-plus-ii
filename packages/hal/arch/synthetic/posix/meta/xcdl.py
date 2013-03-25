# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.arch.synthetic.posix',
    name='Synthetic POSIX architecture',
    description='POSIX architecture classes.',

    category='arch',
            
    headerDefinition='OS_INCLUDE_HAL_ARCH_SYNTHETIC_POSIX',
      
    isEnabled=False,
      
    implements=[
        # mark this is an architecture
        'interface.os.arch',
    ],
                  
)
