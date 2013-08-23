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

    artefactName='minimal',
    artefactDescription='Minimal Test',
            
    children=[
              
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.tests.minimal.linux',
            name='GNU/Linux Minimal Test configuration',
            description='Common Debug/Release definitions for Minimal Test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',                
            ],
                      
            buildFolder='linux/minimal',
            
            includeFiles=[
                'minimal-linux-config.py'
            ],
        ),   
              
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.tests.minimal.osx',
            name='OS X Minimal Test configuration',
            description='Common Debug/Release definitions for Minimal Test running on OS X.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',                
            ],
                      
            buildFolder='osx/minimal',
            
            includeFiles=[
                'minimal-osx-config.py'
            ],
        )      
                 
    ],
                      
    includeFiles=[
        'minimal-qemu-config.py',
        'minimal-stm32h103-config.py',
    ],
)
