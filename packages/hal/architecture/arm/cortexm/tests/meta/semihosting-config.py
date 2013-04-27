# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

#RepositoryFolder('../..')

Configuration(
              
    id='config.os.hal.architecture.arm.cortexm.tests.semihosting',
    name='ARM Cortex-M semihosting application configuration',
    description='Build the ARM Cortex-M semihosting test application.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "semi-hosting")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable test artefact
        'enable("component.os.hal.architecture.arm.cortexm.tests.semihosting")',
    ],
                  
    includeFiles=[
        'semihosting-stm32h103-config.py',
    ],

    artefactName='semihosting',
    
    copyFiles=[
        ('makefile_defs.mk','makefile_defs.mk'),
        ('makefile_targets.mk','makefile_targets.mk'),
    ],
              
)
