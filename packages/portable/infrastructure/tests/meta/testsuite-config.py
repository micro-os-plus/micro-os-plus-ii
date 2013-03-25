# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../..')

Configuration(
              
    id='config.os.portable.infrastructure.tests.testsuite',
    name='Test TestSuite configuration',
    description='Test the TestSuite class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.infrastructure.tests',
        
        # the minimal template
        'package.os.templates.minimal',
        
        'package.os.portable.language.cpp',

    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: TestSuite output")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable component under test
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable test artefact
        'enable("component.os.portable.infrastructure.tests.testsuite")',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.infrastructure.tests.testsuite.osx',
            name='Test TestSuite on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                #'package.os.hal.platforms.synthetic.osx.cl-sjlj',
                'package.os.hal.platforms.synthetic.osx',
            ],
                      
            requirements=[
                #'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
                'enable("package.os.hal.platforms.synthetic.osx")',                
            ],
                      
            buildFolder='osx/testsuite',
            
            artifactFileName='testsuite.elf',
            
            children=[
                       
                # LLVM x64     
                Configuration(
                    id='config.os.portable.infrastructure.tests.testsuite.osx.x64.llvm.debug',
                    name='Debug OS X TestSuite configuration with x86_64 LLVM',
                    description='Debug build configuration for TestSuite',
                    
                    buildConfigurationName='osx_testsuite_x64_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x64/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.infrastructure.tests.testsuite.osx.x64.llvm.release',
                    name='Release OS X TestSuite configuration with x86_64 LLVM',
                    description='Release build configuration for TestSuite',
                    
                    buildConfigurationName='osx_testsuite_x64_llvm_Release',
                    
                    buildFolder='$(PARENT)/x64/llvm/Release',
                    
                    toolchain='toolchain.osx.release.llvm.x64',
                ),


            ],
        ),
    ],
)
