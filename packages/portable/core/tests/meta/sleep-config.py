# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../..')

Configuration(
              
    id='config.os.portable.core.tests.sleep',
    name='Sleep test configuration',
    description='Test the sleep functions.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.core.tests',
        
        # the minimal template
        'package.os.template.minimal',        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: Sleep")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',

        # enable test artefact
        'enable("component.os.portable.core.tests.sleep")',
        
        
        'setValue("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS", 5)',

        'setValue("OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND", 1000)',        
    ],
                                
    artefactName='sleep',
    artefactDescription='Sleep test',

    children=[
              
        # Configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.core.tests.sleep.osx',
            name='OS X Sleep test configuration',
            description='Common Debug/Release definitions for Sleep test running on OS X.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/sleep',
                
            includeFiles=[
                'sleep-osx-config.py',
            ],            
        ),
        
        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.core.tests.sleep.linux',
            name='GNU/Linux Sleep test configuration',
            description='Common Debug/Release definitions for Sleep test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/sleep',
            
            includeFiles=[
                'sleep-linux-config.py',
            ],
        ),
              
        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.core.tests.sleep.qemu',
            name='QEMU ARM Sleep test configuration',
            description='Common Debug/Release definitions for Sleep test running on QEMU.',
            
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
                      
            buildFolder='qemu/sleep',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'sleep-qemu-config.py',
            ],
        ),

        # Configuration specific for Olimex board STM32-H103
        Configuration(
              
            id='config.os.portable.core.tests.sleep.stm32h103',
            name='STM32-H103 Sleep test configuration',
            description='Common Debug/Release definitions for Sleep test running on STM32-H103.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.olimex.stm32h103',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.olimex.stm32h103")',    
                    
                # and the i2c trace output        
                'enable("component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace.i2c")',   
                
                'enable("component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.i2c")',                    
            ],
                      
            buildFolder='stm32h103/sleep',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
                                         
            includeFiles=[
                'sleep-stm32h103-config.py',
            ],
        ),
                 
    ],

)
