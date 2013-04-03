# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../..')

Configuration(
              
    id='config.os.portable.tests.minimal',
    name='Minimal application configuration',
    description='Build the minimal application.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Minimal")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable test artefact
        'enable("component.os.portable.tests.minimal")',
    ],
                  
    includeFiles=[
        'minimal-osx-config.py',
        'minimal-linux-config.py',
        'minimal-stm32h103-config.py',
    ],
)
