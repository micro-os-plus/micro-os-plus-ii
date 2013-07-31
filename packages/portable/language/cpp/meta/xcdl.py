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
                    id='component.os.portable.language.cpp.exceptions.handlers',
                    name='C++ language exceptions handlers support',
                    description='Support for C++ exception handlers.',

                    isEnabled=False,                      

                    headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_EXCEPTIONS_HANDLERS',
                    
                ),
                
            ],
        ),
              
    ],
)
