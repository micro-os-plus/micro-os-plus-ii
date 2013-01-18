# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.kernel',
    name='The µOS++ SE kernel',
    description='All µOS++ Second Edition portable kernel packages.',
    
        
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
            id='option.os.portable.kernel.early',
            name='Early initialisation class',
            description='The constructor of this class should be run in the\
first place, to run all system initialisation.',
                
            # No other object should share this priority to ensure this
            # object is constructed first
            linkPriority=0,
                    
            sourceFiles=[
                'OSEarlyInitialisation.cpp',
            ],
        ),
              
    ],
)
