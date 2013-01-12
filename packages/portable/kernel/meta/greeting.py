# -*- coding: utf-8 -*-

Component(
    id='package.os.portable.kernel.greeting',
    name='Application specific greeting',
    description='The greeting string to be displayed \
either by the debug inits, when enabled, or by the application itself.',
    
    sourceFiles=[
        'OS_Greeting.cpp',
    ],
         
    headerDefinition='OS_INCLUDE_GREETING',
    
    # debug will require it
    isEnabled='False',
          
    children=[
        
        Option(
            id='package.os.portable.kernel.greeting.app.name',
            name='Application Name',
            description='A short string defining the application name.',
            
            valueType='string',
            defaultValue='Sample Application',
            
            headerFile='include/xcdl/OS_Greeting_Defines.h',
            headerDefinition='APP_CFGSTR_APPLICATION_NAME',

        ),

        Option(
            id='package.os.portable.kernel.greeting.app.manufacturer',
            name='Application Manufacturer',
            description='A short string defining the application manufacturer',
            
            valueType='string',
            defaultValue='livius.net',

            headerFile='include/xcdl/OS_Greeting_Defines.h',
            headerDefinition='APP_CFGSTR_APPLICATION_MANUFACTURER',
            
        ),

        Option(
            id='package.os.portable.kernel.greeting.app.version.major',
            name='Application Version Major',
            description='A number defining the application version major',
            
            valueType='number',
            defaultValue='1',

            headerFile='include/xcdl/OS_Greeting_Defines.h',
            headerDefinition='APP_CFGINT_VERSION_MAJOR',
            
            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',
            
        ),

        Option(
            id='package.os.portable.kernel.greeting.app.version.minor',
            name='Application Version Minor',
            description='A number defining the application version minor',
            
            valueType='number',
            defaultValue='1',

            headerFile='include/xcdl/OS_Greeting_Defines.h',
            headerDefinition='APP_CFGINT_VERSION_MINOR',

            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',
            
        ),

        Option(
            id='package.os.portable.kernel.greeting.app.version.revision',
            name='Application Version Revision',
            description='A number defining the application version revision',
            
            valueType='number',
            defaultValue='1',

            headerFile='include/xcdl/OS_Greeting_Defines.h',
            headerDefinition='APP_CFGINT_VERSION_REVISION',
            
            # This value needs to be stringified, so no parenthesis 
            # should be used here
            valueFormat='{0}',
            
        ),

    ],
)
