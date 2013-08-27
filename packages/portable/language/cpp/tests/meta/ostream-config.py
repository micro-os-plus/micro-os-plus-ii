# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.ostream',
    name='C++ ostream test configuration',
    description='Test some methods of the C++ ostream class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.template.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ ostream")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable component under test
        'enable("component.os.portable.language.cpp.streams")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable test artefact
        'enable("component.os.portable.language.cpp.tests.ostream")',
        
        # this test does not need the scheduler related stuff
        'disable("component.os.portable.core.scheduler")',
    ],
    
    artefactName='ostream',
    artefactDescription='C++ ostream test',
                           
    children=[
 
        # Configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.language.cpp.tests.ostream.osx',
            name='OS X C++ ostream test configuration',
            description='Common Debug/Release definitions for C++ ostream test running on OS X.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/ostream',
            
            includeFiles=[
                'ostream-osx-config.py',
            ],
        ),

        # Configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.language.cpp.tests.ostream.linux',
            name='GNU/Linux C++ ostream test configuration',
            description='Common Debug/Release definitions for C++ ostream test running on GNU/Linux.',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/ostream',
            
            includeFiles=[
                'ostream-linux-config.py',
            ],
        ),
              
        # Configuration specific for QEMU generic Cortex-M3
        Configuration(
              
            id='config.os.portable.language.cpp.tests.ostream.qemu',
            name='QEMU ARM C++ ostream test configuration',
            description='Common Debug/Release definitions for C++ ostream test running on QEMU.',
            
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
                      
            buildFolder='qemu/ostream',
            
            buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
            
            copyFiles=[
                ('/support/makefile/aep_gcc_makefile_defs.mk', 'makefile_defs.mk'),
                ('/support/makefile/aep_gcc_makefile_targets.mk', 'makefile_targets.mk'),
            ],
            
            includeFiles=[
                'ostream-qemu-config.py',
            ],
        ),

    ],
)
