# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../..')

Configuration(
              
    id='config.os.portable.diagnostics.tests.trace',
    name='Test diagnostics trace configuration',
    description='Test the diagnostics trace specific classes.',
    
    loadPackages=[
        # mandatory test code package;
        'package.os.portable.diagnostics.tests',
        
        # the minimal template
        'package.os.templates.minimal',
        
        'package.os.portable.language.cpp',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Trace")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        'enable("component.os.portable.language.cpp.streams")',
        
        # enable test artefact
        'enable("component.os.portable.diagnostics.tests.trace")',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.osx',
            name='Test Trace on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                #'package.os.hal.platforms.synthetic.osx.cl-sjlj',
                'package.os.hal.platforms.synthetic.osx',
            ],
                      
            requirements=[
                #'enable("component.os.hal.arch.synthetic.posix.infrastructure.testsuite")',
                'enable("component.os.portable.infrastructure.testsuite")',
                'enable("package.os.hal.platforms.synthetic.osx")',                
        ],
                      
            buildFolder='osx/trace',
            
            artifactFileName='trace.elf',
            
            children=[
                       
                # LLVM x64   
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.llvm.debug',
                    name='Debug OS X Trace configuration with x86_64 LLVM',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x64/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.llvm.release',
                    name='Release OS X Trace configuration with x86_64 LLVM',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_llvm_Release',
                    
                    buildFolder='$(PARENT)/x64/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x64',
                ),

                # LLVM x32   
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.llvm.debug',
                    name='Debug OS X Trace configuration with i386 LLVM',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x32/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x32',
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.llvm.release',
                    name='Release OS X Trace configuration with i386 LLVM',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_llvm_Release',
                    
                    buildFolder='$(PARENT)/x32/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x32',
                ),

                # GCC 4.7 x64
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.gcc47.debug',
                    name='Debug OS X Trace configuration with x86_64 GCC 4.7',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.gcc47.release',
                    name='Release OS X Trace configuration with x86_64 GCC 4.7',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_gcc47_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Release',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
                ),

                # GCC 4.7 x32
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.gcc47.debug',
                    name='Debug OS X Trace configuration with i386 GCC 4.7',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.gcc47.release',
                    name='Release OS X Trace configuration with i386 GCC 4.7',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_gcc47_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc47/Release',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
                ),
                  
                # GCC 4.6 x64   
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.gcc46.debug',
                    name='Debug OS X Trace configuration with x86_64 GCC 4.6',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_gcc46_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc46/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc46.x64',                    
                ),
                      
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x64.gcc46.release',
                    name='Release OS X Trace configuration with x86_64 GCC 4.6',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x64_gcc46_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc46/Release',
                                          
                    toolchain='toolchain.osx.release.mp.gcc46.x64',                    
                ),

                # GCC 4.6 x32
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.gcc46.debug',
                    name='Debug OS X Trace configuration with i386 GCC 4.6',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_gcc46_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc46/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc46.x32',                    
                ),
                      
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.osx.x32.gcc46.release',
                    name='Release OS X Trace configuration with i386 GCC 4.6',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='osx_trace_x32_gcc46_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc46/Release',
                    
                    toolchain='toolchain.osx.release.mp.gcc46.x32',                    
                ),

            ],
        ),
    ],
)