# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.language.cpp',
    name='C++ language support',
    description='Support for C++, similar to standard library.',
    
    sourceFiles=[
        'locale_tiny.cpp',
        'locale.cpp',
        'exception.cpp',
        'new.cpp',
        'malloc.cpp',
        'abort.cpp',
        'memory.cpp',
        'string.cpp',
    ],
         
    children=[
              
        Component(
            id='component.os.portable.language.cpp.streams',
            name='C++ language streams support',
            description='Support for C++ streams.',
            
            isEnabled=False,                      
            sourceFiles=[
                'ios.cpp',
                'streambuf.cpp',
                'ostream.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS',
              
        ),
              
        Component(
            id='component.os.portable.language.cpp.exceptions',
            name='C++ language exceptions support',
            description='Support for C++ exceptions.',
            
            isEnabled=False,                      

            headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS',
            
            children=[
                Option(
                    id='option.os.portable.language.cpp.exceptions.handlers',
                    name='C++ language exceptions handlers support',
                    description='Support for C++ exception handlers.',

                    isEnabled=False,                      

                    headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS',
                    
                ),
                
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.wide',
            name='C++ language wide characters support',
            description='Support for C++ wide characters.',

            isEnabled=False,                      

            children=[
                Option(
                    id='option.os.portable.language.cpp.wide.wchar_t',
                    name='C++ language wchar_t support',
                    description='Support for C++ wchar_t characters.',

                    isEnabled=False,                      

                    headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_WCHAR_T',
                    
                ),
                      
            ],
        ),
              
    ],
)
