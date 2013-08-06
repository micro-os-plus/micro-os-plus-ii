# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.mutexstress',
    name='Test mutex stress creation configuration',
    description='Stress test the mutex calls.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.core.tests',
        
        # the minimal template
        'package.os.template.minimal',
        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: MutexStress")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',

        # enable test artefact
        'enable("component.os.portable.core.tests.mutexstress")',
        
        
        'setValue("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS", 11)',

        'setValue("OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND", 1000)',
        
    ],
                                
    artefactName='mutexstress',

    children=[
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.mutexstress.osx',
            name='Test mutex stress on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/mutexstress',
                
            includeFiles=[
                'mutexstress-osx-config.py',
            ],
            
        ),
        
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.mutexstress.linux',
            name='Test mutex stress on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/mutexstress',
            
            includeFiles=[
                 'mutexstress-linux-config.py',
            ],
        ),
              
    ],

)
