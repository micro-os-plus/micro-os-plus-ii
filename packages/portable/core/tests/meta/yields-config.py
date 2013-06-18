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
        
        # enable test artefact
        'enable("component.os.portable.core.tests.yields")',
    ],
                  
    includeFiles=[
        'yields-stm32f4discovery-config.py',
    ],
              
    artefactName='yields',

    copyFiles=[
        ('makefile_defs.mk','makefile_defs.mk'),
        ('makefile_targets.mk','makefile_targets.mk'),
    ],

)
