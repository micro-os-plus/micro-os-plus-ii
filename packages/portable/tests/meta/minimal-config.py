# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../..')

Configuration(
              
    id='config.os.portable.tests.minimal',
    name='Minimal test configuration',
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
    artefactDescription='Minimal test',
            
    children=[
              
        # Configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.tests.minimal.osx',
            name='OS X Minimal test configuration',
            description='Common Debug/Release definitions for Minimal test running on OS X.',
            
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
        ),

        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.tests.minimal.linux',
            name='GNU/Linux Minimal test configuration',
            description='Common Debug/Release definitions for Minimal test running on GNU/Linux.',
            
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
             
        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.tests.minimal.qemu',
            name='QEMU ARM Minimal test configuration',
            description='Common Debug/Release definitions for Minimal test running on QEMU.',
            
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
                      
            buildFolder='qemu/minimal',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'minimal-qemu-config.py',
            ],
        ),
              
        # Configuration specific for Olimex board STM32-H103
        Configuration(
              
            id='config.os.portable.tests.minimal.stm32h103',
            name='STM32-H103 Minimal test configuration',
            description='Common Debug/Release definitions for Minimal test running on STM32-H103.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.olimex.stm32h103',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.olimex.stm32h103")',    
                    
                # and the i2c trace output        
                'enable("component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace.i2c")',                       
            ],
                      
            buildFolder='stm32h103/minimal',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
                                         
            includeFiles=[
                'minimal-stm32h103-config.py',
            ],
        ),
              
    ],
)
