# -*- coding: utf-8 -*-

# Copyright (c) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.portable.language.cpp',
    name='C++ language support',
    description='Support for C++, similar to standard library.',
    
          
    children=[
              
        Component(
            id='component.os.portable.language.cpp.streams',
            name='C++ language streams support',
            description='Support for C++ streams.',
                                  
            sourceFiles=[
                'ios.cpp',
                'streambuf.cpp',
                'ostream.cpp',
                'locale_tiny.cpp',
                'locale.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_LANGUAGE_CPP_STREAMS',
              
        ),
    ],
)
