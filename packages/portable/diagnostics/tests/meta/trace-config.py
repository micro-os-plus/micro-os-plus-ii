# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../..')

Configuration(
              
    id='config.os.portable.diagnostics.tests.trace',
    name='Trace test configuration',
    description='Test the diagnostics trace specific classes.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.diagnostics.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Trace")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',
                
        # enable test artefact
        'enable("component.os.portable.diagnostics.tests.trace")',
                
        # this test does not need the scheduler related stuff
        'disable("component.os.portable.core.scheduler")',
    ],
                  
    artefactName='trace',
    artefactDescription='Trace Diagnostics',
            
    children=[
 
        # Configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.osx',
            name='OS X Trace test configuration',
            description='Common Debug/Release definitions for Trace test running on OS X.',
      
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',                
            ],
                      
            buildFolder='osx/trace',
            
            includeFiles=[
                'trace-osx-config.py'
            ],
        ),
              
        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.linux',
            name='GNU/Linux Trace test configuration',
            description='Common Debug/Release definitions for Trace test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',                
            ],
                      
            buildFolder='linux/trace',
            
            includeFiles=[
                'trace-linux-config.py'
            ],
        ),

        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.qemu',
            name='QEMU ARM Trace test configuration',
            description='Common Debug/Release definitions for Trace test running on QEMU.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.qemu',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.qemu")',                

                # we also need the semihosting trace output
                'enable("component.os.hal.architecture.arm.cortexm.qemu.diagnostics.trace.semihosting")',
            ],
                      
            buildFolder='qemu/trace',

            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'trace-qemu-config.py'
            ],
        ),

    ],
)
