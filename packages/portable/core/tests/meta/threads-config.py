# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.threads',
    name='Threads creation test configuration',
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
                                
    artefactName='threads',
    artefactDescription='Threads creation test',

    children=[
              
        # oCnfiguration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.threads.osx',
            name='OS X Threads creation test configuration',
            description='Common Debug/Release definitions for Threads creation test running on OS X.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx',
                
            includeFiles=[
                'threads-osx-config.py',
            ],            
        ),
        
        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.threads.linux',
            name='GNU/Linux Threads creation test configuration',
            description='Common Debug/Release definitions for Threads creation test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux',
            
            includeFiles=[
                'threads-linux-config.py',
            ],
        ),
              
        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.core.tests.threads..qemu',
            name='QEMU ARM Threads creation test configuration',
            description='Common Debug/Release definitions for Threads creation test running on QEMU.',
            
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
                      
            buildFolder='qemu',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'threads-qemu-config.py',
            ],
        ),

    ],

)
