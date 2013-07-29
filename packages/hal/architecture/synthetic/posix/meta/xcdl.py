# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.synthetic.posix',
    name='Synthetic POSIX architecture',
    description='POSIX architecture classes.',

    category='architecture',
            
    isEnabled=False,

    sourceFiles=[
        'ArchitectureImplementation.cpp',
        'TimerTicksImplementation.cpp',
    ],

    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_SYNTHETIC_POSIX',
      
    requirements=[
        'disable("OS_INCLUDE_PORTABLE_CORE_EARLYINITIALISATIONS_RESET")',
    ],
          
    implements=[
        # mark this is an architecture
        'interface.os.architecture',
    ],
                  
)
