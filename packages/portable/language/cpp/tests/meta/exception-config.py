# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.exception',
    name='Test C++ exception configuration',
    description='Test the exception classes.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ exception")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable test artefact
        'enable("component.os.portable.language.cpp.tests.exception")',

        # enable wchar_t support
        # 'enable("option.os.portable.language.cpp.wide.wchar_t")',

        # enable string
        # 'enable("component.os.portable.language.cpp.string")',

        # enable exceptions
        'enable("component.os.portable.language.cpp.exceptions")',
        
        # this test does not need the scheduler related stuff
        'disable("component.os.portable.core.scheduler")',
    ],
    
    artefactName='exception',
                           
    children=[
 
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.language.cpp.tests.exception.osx',
            name='Test C++ exception on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/exception',
            
            includeFiles=[
                'exception-osx-config.py',
            ],
        ),

        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.language.cpp.tests.exception.linux',
            name='Test C++ exception on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/exception',
            
            includeFiles=[
                'exception-linux-config.py',
            ],
        ),
    ],
)
