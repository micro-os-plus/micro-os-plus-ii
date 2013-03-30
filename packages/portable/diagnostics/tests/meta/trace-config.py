# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../..')

Configuration(
              
    id='config.os.portable.diagnostics.tests.trace',
    name='Test diagnostics trace configuration',
    description='Test the diagnostics trace specific classes.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.diagnostics.tests',
        
        # the minimal template
        'package.os.templates.minimal',
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "Trace")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        'enable("component.os.portable.language.cpp.streams")',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',
                
        # enable test artefact
        'enable("component.os.portable.diagnostics.tests.trace")',
    ],
                  
    children=[
 
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.osx',
            name='Test Trace on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.osx")',                
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
              
        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.diagnostics.tests.trace.linux',
            name='Test Trace on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                # enable the platform    
                'enable("package.os.hal.platform.synthetic.linux")',                
            ],
                      
            buildFolder='linux/trace',
            
            artifactFileName='trace.elf',
            
            children=[
                       
                # GCC x64
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.linux.x64.gcc.debug',
                    name='Debug OS X Trace configuration with x86_64 GCC',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='linux_trace_x64_gcc_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.linux.debug.gcc.x64',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.linux.x64.gcc.release',
                    name='Release OS X Trace configuration with x86_64 GCC',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='linux_trace_x64_gcc_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc/Release',
                                          
                    toolchain='toolchain.linux.release.gcc.x64',                    
                ),

                # GCC x32
                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.linux.x32.gcc.debug',
                    name='Debug OS X Trace configuration with i386 GCC',
                    description='Debug build configuration for Trace.',
                    
                    buildConfigurationName='linux_trace_x32_gcc_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.linux.debug.gcc.x32',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.trace.linux.x32.gcc.release',
                    name='Release OS X Trace configuration with i386 GCC',
                    description='Release build configuration for Trace.',
                    
                    buildConfigurationName='linux_trace_x32_gcc_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc/Release',

                    toolchain='toolchain.linux.release.gcc.x32',                    
                ),
            ],
        ),

    ],
)
