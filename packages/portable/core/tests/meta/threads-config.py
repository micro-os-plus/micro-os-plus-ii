# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.threads',
    name='Test threads creation configuration',
    description='Test the creation of Thread objects.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.core.tests',
        
        # the minimal template
        'package.os.template.minimal',
        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: Threads")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',

        # enable test artefact
        'enable("component.os.portable.core.tests.threads")',
        
        
        'setValue("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS", 7)',
        
        'enable("component.os.portable.core.scheduler.custom")',

        'setValue("OS_STRING_CORE_SCHEDULER_CUSTOM_HEADER", "portable/core/tests/include/FakeScheduler.h")',
        
    ],
                                
    artefactName='threads',

    children=[
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.threads.osx',
            name='Test threads creation on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/threads',
                
            includeFiles=[
                'threads-osx-config.py',
            ],
            
        ),
        
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.threads.linux',
            name='Test threads creation on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/threads',
            
            includeFiles=[
                'threads-linux-config.py',
            ],
        ),
              
    ],

)
