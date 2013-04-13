# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='package.os.portable.core.greeting',
    name='Application specific greeting',
    description='The greeting string to be displayed \
either by the debug inits, when enabled, or by the application itself.',
    
    sourceFiles=[
        'Greeting.cpp',
    ],
         
    headerDefinition='OS_INCLUDE_GREETING',
    
    # debug will require it
    isEnabled=False,
          
    children=[
        
        Option(
            id='package.os.portable.core.greeting.app.name',
            name='Application Name',
            description='A short string defining the application name.',
            
            valueType='string',
            defaultValue='Sample Application',
            
            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
            headerDefinition='APP_STRING_APPLICATION_NAME',
        ),

        Option(
            id='package.os.portable.core.greeting.app.manufacturer',
            name='Application Manufacturer',
            description='A short string defining the application manufacturer',
            
            valueType='string',
            defaultValue='livius.net',

            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
            headerDefinition='APP_STRING_APPLICATION_MANUFACTURER',            
        ),

        Option(
            id='package.os.portable.core.greeting.app.version.major',
            name='Application Version Major',
            description='A number defining the application version major',
            
            valueType='int',
            defaultValue='1',

            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
            headerDefinition='APP_INTEGER_VERSION_MAJOR',
            
            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',            
        ),

        Option(
            id='package.os.portable.core.greeting.app.version.minor',
            name='Application Version Minor',
            description='A number defining the application version minor',
            
            valueType='int',
            defaultValue='1',

            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
            headerDefinition='APP_INTEGER_VERSION_MINOR',

            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',            
        ),

        Option(
            id='package.os.portable.core.greeting.app.version.revision',
            name='Application Version Revision',
            description='A number defining the application version revision',
            
            valueType='int',
            defaultValue='1',

            headerFile='include/portable/core/include/XCDL_GreetingDefines.h',
            headerDefinition='APP_INTEGER_VERSION_REVISION',
            
            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',            
        ),

    ],
)
