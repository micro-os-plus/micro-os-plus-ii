# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.infrastructure.tests.testsuite',
    name='Test TestSuite configuration',
    description='Test the TestSuite class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.infrastructure.tests.testsuite',
        
        # the minimal template
        'package.os.templates.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: TestSuite output")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.infrastructure.tests.testsuite.osx',
            name='Test TestSuite on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platforms.synthetic.osx.cl-sjlj',
            ],
                      
            requirements=[
                'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
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
