# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.language.cpp.tests',
    name='Test C++ language classes',
    description='Test the C++ language specific classes.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.portable.language.cpp.tests.streambuf',
            name='Test C++ streambuf',
            description='Test some methods of the streambuf class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'streambuf.cpp',
            ],
                  
            includeFiles=[
                'streambuf-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),

        Component(
            id='component.os.portable.language.cpp.tests.fpos',
            name='Test C++ fpos',
            description='Test some methods of the fpos class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'fpos.cpp',
            ],
                  
            includeFiles=[
                'fpos-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.ios_base',
            name='Test C++ ios_base',
            description='Test some methods of the ios_base class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'ios_base.cpp',
            ],
                  
            includeFiles=[
                'ios_base-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.basic_ios',
            name='Test C++ basic_ios',
            description='Test some methods of the basic_ios class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'basic_ios.cpp',
            ],
                  
            includeFiles=[
                'basic_ios-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.ostream',
            name='Test C++ ostream',
            description='Test some methods of the ostream class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'ostream.cpp',
            ],
                  
            includeFiles=[
                'ostream-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.ostreamconv',
            name='Test C++ ostream conversions',
            description='Test conversion methods of the ostream class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'ostreamConversions.cpp',
            ],
                  
            includeFiles=[
                'ostreamconv-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.string',
            name='Test C++ string',
            description='Test some methods of the string class.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'string.cpp',
            ],
                  
            includeFiles=[
                'string-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

        Component(
            id='component.os.portable.language.cpp.tests.exception',
            name='Test C++ exception',
            description='Test the exception classes.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'exception.cpp',
            ],
                  
            includeFiles=[
                'exception-config.py',
            ],

            implements=[
                'interface.os.artefact',
            ],
        ),

              
#        Component(
#            id='component.os.portable.language.cpp.tests.ostrstream',
#            name='Test C++ ostrstream',
#            description='Test some methods of the ostrstream class.',
#    
#            category='test',
#    
#            isEnabled=False,
#            sourceFiles=[
#                'ostrstream.cpp',
#            ],
#                  
#            includeFiles=[
#                'ostrstream-config.py',
#            ],
#        ),
              
    ],
)
