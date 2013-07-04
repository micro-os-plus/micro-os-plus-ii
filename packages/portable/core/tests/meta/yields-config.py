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
                  
    includeFiles=[
        'yields-stm32f4discovery-config.py',
        'yields-posix-config.py',
    ],
              
    artefactName='yields',

)
