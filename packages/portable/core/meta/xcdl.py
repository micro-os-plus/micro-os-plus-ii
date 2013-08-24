# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.core',
    name='The µOS++ SE core package',
    description='All µOS++ Second Edition portable core packages.',
    
    sourceFiles=[
    ],
        
    includeFiles=[
        'greeting.py',
        'scheduler.py',
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
              
        Component(
            id='component.os.portable.core.early',
            name='Early initialisation class',
            description='The constructor of this class should be run in the\
first place, to run all system initialisation.',
                
            # No other object should share this priority to ensure this
            # object is constructed first
            linkPriority=0,
                    
            sourceFiles=[
                'EarlyInitialisations.cpp',
            ],
                  
            children=[
                
                Option(
                    id='component.os.portable.core.early.destructor.reset',
                    name='Late destructor reset',
                    description='The destructor will reset the platform',
                    
                    isEnabled=True,
            
                    headerDefinition='OS_INCLUDE_PORTABLE_CORE_EARLYINITIALISATIONS_DESTRUCTOR_RESET',

                ),
                
            ],
        ),

        Component(
            id='component.os.portable.core.platform',
            name='Core platform definitions',
            description='.',
            
            isEnabled=True,
            
            children=[
                Component(
                    id='component.os.portable.core.platform.greetings',
                    name='Core platform greeting definitions',
                    description='Platform greeting strings.',

                    # must be true, to save an explicit enable before setValue()
                    isEnabled=True,
                    
                    childrenHeaderFile='include/portable/core/include/XCDL_GreetingDefines.h',
                    
                    children=[
                        Component(
                            id='component.os.portable.core.platform.greetings.first',
                            name='Core platform first greeting message',
                            description='First message to be displayed as the platform greeting.',
                            
                            isEnabled=False,

                            valueType='string',
                            
                            headerDefinition='OS_STRING_PLATFORM_GREETING_FIRST',
                        ),
                              
                        Component(
                            id='component.os.portable.core.platform.greetings.second',
                            name='Core platform second greeting message',
                            description='Second message to be displayed as the platform greeting.',
                            
                            isEnabled=False,

                            valueType='string',
                            
                            headerDefinition='OS_STRING_PLATFORM_GREETING_SECOND',
                        ),

                    ],
                ),
                      
                Option(
                    id='option.os.portable.core.platform.implementation.default',
                    name='Use the default platform implementation definitions',
                    description='Default platform implementation.',

                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_PORTABLE_CORE_PLATFORMIMPLEMENTATIONDEFAULT',
                ),

                Option(
                    id='option.os.portable.core.platform.implementation.custom',
                    name='Use custom platform implementation definitions',
                    description='Custom platform implementation.',

                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_PORTABLE_CORE_PLATFORMIMPLEMENTATION_CUSTOM',
                ),

            ],
        ),              
 
    ],
)
