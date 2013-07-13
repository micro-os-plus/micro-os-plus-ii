# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../..')

Configuration(
              
    id='config.os.portable.diagnostics.tests.trace',
    name='Test diagnostics trace configuration',
    description='Test the diagnostics trace specific classes.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.diagnostics.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Trace")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',
                
        # enable test artefact
        'enable("component.os.portable.diagnostics.tests.trace")',
                
        # this test does not need the scheduler related stuff
        'disable("component.os.portable.core.scheduler")',
    ],
                  
    artefactName='trace',
            
    children=[
 
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.osx',
            name='Test Trace on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',                
            ],
                      
            buildFolder='osx/trace',
            
            includeFiles=[
                'trace-osx-config.py'
            ],
        ),
              
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.linux',
            name='Test Trace on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',                
            ],
                      
            buildFolder='linux/trace',
            
            includeFiles=[
                'trace-linux-config.py'
            ],
        ),

    ],
)
