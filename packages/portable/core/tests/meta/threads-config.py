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
                  
    includeFiles=[
        'threads-posix-config.py',
    ],
              
    artefactName='threads',

)
