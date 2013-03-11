# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.streambuf',
    name='Test C++ streambuf configuration',
    description='Test some methods of the streambuf class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.templates.minimal',
        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ streambuf")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        'enable("component.os.portable.language.cpp.tests.streambuf")',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.language.cpp.tests.streambuf.osx',
            name='Test C++ streambuf on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platforms.synthetic.osx.cl-sjlj',
            ],
                      
            requirements=[
                'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
            ],
                      
            buildFolder='osx/streambuf',
            
            artifactFileName='streambuf.elf',
            
            children=[
                            
                Configuration(
                    id='config.os.portable.language.cpp.tests.streambuf.osx.x64.llvm.debug',
                    name='Debug OS X C++ streambuf configuration with x86_64 LLVM',
                    description='Debug build configuration for streambuf.',
                    
                    buildConfigurationName='osx_streambuf_x64_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x64/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.streambuf.osx.x64.llvm.release',
                    name='Release OS X C++ streambuf configuration with x86_64 LLVM',
                    description='Release build configuration for streambuf.',
                    
                    buildConfigurationName='osx_streambuf_x64_llvm_Release',
                    
                    buildFolder='$(PARENT)/x64/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.streambuf.osx.x64.gcc47.debug',
                    name='Debug OS X C++ streambuf configuration with x86_64 GCC 4.7',
                    description='Debug build configuration for streambuf.',
                    
                    buildConfigurationName='osx_streambuf_x64_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
                ),
            ],
        ),
    ],
)
