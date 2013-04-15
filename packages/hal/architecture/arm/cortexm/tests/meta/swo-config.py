# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

#RepositoryFolder('../..')

Configuration(
              
    id='config.os.hal.architecture.arm.cortexm.tests.swo',
    name='ARM Cortex-M SWO application configuration',
    description='Build the ARM Cortex-M SWO application.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "SWO")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable test artefact
        'enable("component.os.hal.architecture.arm.cortexm.tests.swo")',
    ],
                  
    includeFiles=[
        'swo-stm32h103-config.py',
    ],
)
