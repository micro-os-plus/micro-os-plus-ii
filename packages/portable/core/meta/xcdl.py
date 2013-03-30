# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.core',
    name='The µOS++ SE core package',
    description='All µOS++ Second Edition portable core packages.',
    
    sourceFiles=[
        'PlatformBase.cpp',
    ],
        
    includeFiles=[
        'greeting.py',
    ],
        
    children=[
        Option(
            id='option.os.portable.core.debug',
            name='The main debug switch',
            description='Should be enabled for the debug output to be active.',
            
            isEnabled=False,
            
            headerDefinition='DEBUG',
            
            requirements=[
                'enable("component.os.portable.diagnostics.trace")',
            ],
        ),
              
        Option(
            id='option.os.portable.core.early',
            name='Early initialisation class',
            description='The constructor of this class should be run in the\
first place, to run all system initialisation.',
                
            # No other object should share this priority to ensure this
            # object is constructed first
            linkPriority=0,
                    
            sourceFiles=[
                'EarlyInitialisations.cpp',
            ],
        ),
              
    ],
)
