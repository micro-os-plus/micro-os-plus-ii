# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.kernel',
    name='The µOS++ SE kernel',
    description='All µOS++ Second Edition portable kernel packages.',
    
    sourceFiles=[
        'OS.cpp',
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
    ],
)
