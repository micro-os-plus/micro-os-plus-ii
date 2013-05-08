# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

#RepositoryFolder('../..')

Configuration(
              
    id='config.os.hal.architecture.arm.cortexm.tests.gpio',
    name='ARM Cortex-M GPIO application configuration',
    description='Build the ARM Cortex-M GPIO test application.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "GPIO")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable test artefact
        'enable("component.os.hal.architecture.arm.cortexm.tests.gpio")',
        'enable("option.os.portable.diagnostics.trace.ostream")',
    ],
                  
    includeFiles=[
        #'gpio-stm32h103-config.py',
        #'gpio-olimexinostm32-config.py',
        #'gpio-stm32p107-config.py',
        'gpio-stm32e407-config.py',
        'gpio-stm32f4discovery-config.py',
    ],

    artefactName='gpio',

    copyFiles=[
        ('makefile_defs.mk','makefile_defs.mk'),
        ('makefile_targets.mk','makefile_targets.mk'),
    ],
              
)
