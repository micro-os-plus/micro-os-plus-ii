# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.yields',
    name='Yields application configuration',
    description='Build the yields test application.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.core.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Yields")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',

        # enable test artefact
        'enable("component.os.portable.core.tests.yields")',
        
        'setValue("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS", 3)',

    ],
                                
    artefactName='yields',

    children=[
              
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.yields.osx',
            name='Test yields on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/yields',
            
            includeFiles=[
                'yields-osx-config.py',
            ],
        ),
        
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.yields.linux',
            name='Test yields on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/yields',
            
            includeFiles=[
                'yields-linux-config.py',
            ],
        ),
    ],

    includeFiles=[
        'yields-stm32f4discovery-config.py',
    ],

)
