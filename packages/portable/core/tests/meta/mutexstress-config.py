# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.mutexstress',
    name='Mutex stress test configuration',
    description='Stress test the mutex calls.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.core.tests',
        
        # the minimal template
        'package.os.template.minimal', 
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: MutexStress")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',

        # enable test artefact
        'enable("component.os.portable.core.tests.mutexstress")',
        
        
        'setValue("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS", 11)',

        'setValue("OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND", 1000)',        
    ],
                                
    artefactName='mutexstress',
    artefactDescription='Mutex stress test',

    children=[
              
        # Configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.mutexstress.osx',
            name='OS X Mutex stress test configuration',
            description='Common Debug/Release definitions for Mutex stress test running on OS X.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/mutexstress',
                
            includeFiles=[
                'mutexstress-osx-config.py',
            ],            
        ),
        
        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.mutexstress.linux',
            name='GNU/Linux Mutex stress test configuration',
            description='Common Debug/Release definitions for Mutex stress test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/mutexstress',
            
            includeFiles=[
                 'mutexstress-linux-config.py',
            ],
        ),
              
        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.core.tests.mutexstress.qemu',
            name='QEMU ARM Mutex stress test configuration',
            description='Common Debug/Release definitions for Mutex stress test running on QEMU.',
            
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
                      
            buildFolder='qemu/mutexstress',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'mutexstress-qemu-config.py',
            ],
        ),
                 
    ],

)
