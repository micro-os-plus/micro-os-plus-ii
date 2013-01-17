# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.kernel',
    name='The µOS++ SE kernel',
    description='All µOS++ Second Edition portable kernel packages.',
    
    sourceFiles=[
        'OS_Inits.cpp',
    ],
        
    includes=[
        'greeting.py',
    ],
        
    children=[
        Option(
            id='option.os.portable.kernel.debug',
            name='The main debug swich',
            description='Should be enabled for the debug output to be active.',
            
            isEnabled=False,
            
            headerDefinition='DEBUG',
        ),
              
        Option(
            id='option.os.portable.kernel.os-init.early.priority',
            name='The earlyInitialyse() init_priority',
            description='The initialisation priority of the earlyInitialyse() function.',
            
            headerFile='include/portable/kernel/include/OS_Inits_Defines.h',
            headerDefinition='OS_INTEGER_EARLYINITIALISE_INIT_PRIORITY',
            
            valueType='int',
            defaultValue=101,
        ),

        Option(
            id='option.os.portable.kernel.os-init.debug.priority',
            name='The Debug() class init_priority',
            description='The static constructor priority of the Debug() class.',
            
            headerFile='include/portable/kernel/include/OS_Inits_Defines.h',
            headerDefinition='OS_INTEGER_DEBUG_INIT_PRIORITY',
            
            valueType='int',
            defaultValue=102,
        ),
    ],
)
