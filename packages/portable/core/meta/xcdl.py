# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

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

        Component(
            id='component.os.portable.core.platform',
            name='Core platform definitions',
            description='.',
            
            isEnabled=False,
            
            children=[
                Component(
                    id='component.os.portable.core.platform.greetings',
                    name='Core platform greeting definitions',
                    description='Platform greeting strings.',

                    isEnabled=False,
                    
                    children=[
                        Component(
                            id='component.os.portable.core.platform.greetings.first',
                            name='Core platform first greeting message',
                            description='First message to be displayed as the platform greeting.',
                            
                            isEnabled=False,

                            valueType='string',
                            
                            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
                            headerDefinition='OS_STRING_PLATFORM_GREETING_FIRST',
                        ),
                              
                        Component(
                            id='component.os.portable.core.platform.greetings.second',
                            name='Core platform second greeting message',
                            description='Second message to be displayed as the platform greeting.',
                            
                            isEnabled=False,

                            valueType='string',
                            
                            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
                            headerDefinition='OS_STRING_PLATFORM_GREETING_SECOND',
                        ),

                    ],
                ),
            ],
        ),
    ],
)
