# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.core.tests',
    name='Test portable core classes',
    description='Core tests.',
    
    category='tests',
        
    children=[
         
        Component(
            id='component.os.portable.core.tests.threads',
            name='Test threads configuration',
            description='Test thread creation application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'threads.cpp',
                'FakeScheduler.cpp'
            ],
                  
            includeFiles=[
                'threads-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),

        Component(
            id='component.os.portable.core.tests.yields',
            name='Test yields configuration',
            description='Test yields application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'yields.cpp',
            ],
                  
            includeFiles=[
                'yields-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),

        Component(
            id='component.os.portable.core.tests.sleep',
            name='Test sleep configuration',
            description='Test sleep application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'sleep.cpp',
            ],
                  
            includeFiles=[
                'sleep-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
        Component(
            id='component.os.portable.core.tests.sleepstress',
            name='Test sleep stress configuration',
            description='Test sleep stress application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'sleepStress.cpp',
            ],
                  
            includeFiles=[
                'sleepStress-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
        Component(
            id='component.os.portable.core.tests.mutex',
            name='Test mutex configuration',
            description='Test mutex application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'mutex.cpp',
            ],
                  
            includeFiles=[
                'mutex-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
        Component(
            id='component.os.portable.core.tests.mutexstress',
            name='Test mutex stress configuration',
            description='Test mutex stress application.',
    
            category='test',
    
            isEnabled=False,
            sourceFiles=[
                'mutexStress.cpp',
            ],
                  
            includeFiles=[
                'mutexStress-config.py',
            ],
                  
            implements=[
                'interface.os.artefact',
            ],

        ),
              
    ],
)
