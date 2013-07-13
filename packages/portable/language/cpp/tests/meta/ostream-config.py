# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.ostream',
    name='Test C++ ostream configuration',
    description='Test some methods of the ostream class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ ostream")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable component under test
        'enable("component.os.portable.language.cpp.streams")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable test artefact
        'enable("component.os.portable.language.cpp.tests.ostream")',
        
        # this test does not need the scheduler related stuff
        'disable("component.os.portable.core.scheduler")',
    ],
    
    artefactName='ostream',
                           
    children=[
 
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.language.cpp.tests.ostream.osx',
            name='Test C++ ostream on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/ostream',
            
            includeFiles=[
                'ostream-osx-config.py',
            ],
        ),

        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.language.cpp.tests.ostream.linux',
            name='Test C++ ostream on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/ostream',
            
            includeFiles=[
                'ostream-linux-config.py',
            ],
        ),
    ],
)
