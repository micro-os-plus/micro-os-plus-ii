# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.basic_ios',
    name='Test C++ basic_ios configuration',
    description='Test some methods of the basic_ios class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.templates.minimal',
        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ basic_ios")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        'enable("component.os.portable.language.cpp.tests.basic_ios")',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.language.cpp.tests.basic_ios.osx',
            name='Test C++ basic_ios on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platforms.synthetic.osx.cl-sjlj',
            ],
                      
            requirements=[
                'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
            ],
                      
            buildFolder='osx/basic_ios',
            
            artifactFileName='basic_ios.elf',
            
            children=[
                      
                # LLVM x64      
                Configuration(
                    id='config.os.portable.language.cpp.tests.basic_ios.osx.x64.llvm.debug',
                    name='Debug OS X C++ basic_ios configuration with x86_64 LLVM',
                    description='Debug build configuration for basic_ios.',
                    
                    buildConfigurationName='osx_basic_ios_x64_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x64/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.basic_ios.osx.x64.llvm.release',
                    name='Release OS X C++ basic_ios configuration with x86_64 LLVM',
                    description='Release build configuration for basic_ios.',
                    
                    buildConfigurationName='osx_basic_ios_x64_llvm_Release',
                    
                    buildFolder='$(PARENT)/x64/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x64',
                ),

                # GCC 4.7 x64
                Configuration(
                    id='config.os.portable.language.cpp.tests.basic_ios.osx.x64.gcc47.debug',
                    name='Debug OS X C++ basic_ios configuration with x86_64 GCC 4.7',
                    description='Debug build configuration for basic_ios.',
                    
                    buildConfigurationName='osx_basic_ios_x64_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
                ),
                      
                # GCC 4.7 x32
                Configuration(
                    id='config.os.portable.language.cpp.tests.basic_ios.osx.x32.gcc47.debug',
                    name='Debug OS X C++ basic_ios configuration with i386 GCC 4.7',
                    description='Debug build configuration for basic_ios.',
                    
                    buildConfigurationName='osx_basic_ios_x32_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
                ),

                # GCC 4.6 x32
                Configuration(
                    id='config.os.portable.language.cpp.tests.basic_ios.osx.x32.gcc46.debug',
                    name='Debug OS X C++ basic_ios configuration with i386 GCC 4.6',
                    description='Debug build configuration for basic_ios.',
                    
                    buildConfigurationName='osx_basic_ios_x32_gcc46_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc46/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc46.x32',                    
                ),

            ],
        ),
    ],
)
