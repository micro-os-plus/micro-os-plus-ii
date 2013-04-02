# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

RepositoryFolder('../../../../..')

Configuration(
              
    id='config.os.portable.language.cpp.tests.fpos',
    name='Test C++ fpos configuration',
    description='Test some methods of the fpos class.',
    
    loadPackages=[
        # mandatory test code package
        'package.os.portable.language.cpp.tests',
        
        # the minimal template
        'package.os.template.minimal',        
    ],
    
    requirements=[
        'setValue("APP_STRING_APPLICATION_NAME", "UnitTest: C++ fpos")',        
        'setValue("APP_INTEGER_VERSION_REVISION", 1)',
        
        # enable the test suite code
        'enable("component.os.portable.infrastructure.testsuite")',

        # enable component under test
        'enable("component.os.portable.language.cpp.streams")',

        # enable ostream support for Trace
        'enable("option.os.portable.diagnostics.trace.ostream")',
        
        # enable test artefact
        'enable("component.os.portable.language.cpp.tests.fpos")',
    ],
                  
    children=[
 
        # configuration specific for platform OS X
        Configuration(
              
            id='config.os.portable.language.cpp.tests.fpos.osx',
            name='Test C++ fpos on OS X configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.osx',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.osx")',
            ],
                      
            buildFolder='osx/fpos',
            
            artifactFileName='fpos.elf',
            
            children=[
                   
                # LLVM x64   
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.llvm.debug',
                    name='Debug OS X C++ fpos configuration with x86_64 LLVM',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x64/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x64',
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.llvm.release',
                    name='Release OS X C++ fpos configuration with x86_64 LLVM',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_llvm_Release',
                    
                    buildFolder='$(PARENT)/x64/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x64',
                ),

                # LLVM x32   
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.llvm.debug',
                    name='Debug OS X C++ fpos configuration with i386 LLVM',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_llvm_Debug',
                    
                    buildFolder='$(PARENT)/x32/llvm/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.llvm.x32',
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.llvm.release',
                    name='Release OS X C++ fpos configuration with i386 LLVM',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_llvm_Release',
                    
                    buildFolder='$(PARENT)/x32/llvm/Release',
                                          
                    toolchain='toolchain.osx.release.llvm.x32',
                ),

                # GCC 4.7 x64
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.gcc47.debug',
                    name='Debug OS X C++ fpos configuration with x86_64 GCC 4.7',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.gcc47.release',
                    name='Release OS X C++ fpos configuration with x86_64 GCC 4.7',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_gcc47_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc47/Release',
                    
                    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
                ),

                # GCC 4.7 x32
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.gcc47.debug',
                    name='Debug OS X C++ fpos configuration with i386 GCC 4.7',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_gcc47_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc47/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
                ),

                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.gcc47.release',
                    name='Release OS X C++ fpos configuration with i386 GCC 4.7',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_gcc47_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc47/Release',
                    
                    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
                ),
                  
                # GCC 4.6 x64   
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.gcc46.debug',
                    name='Debug OS X C++ fpos configuration with x86_64 GCC 4.6',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_gcc46_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc46/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc46.x64',                    
                ),
                      
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x64.gcc46.release',
                    name='Release OS X C++ fpos configuration with x86_64 GCC 4.6',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x64_gcc46_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc46/Release',
                                          
                    toolchain='toolchain.osx.release.mp.gcc46.x64',                    
                ),

                # GCC 4.6 x32
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.gcc46.debug',
                    name='Debug OS X C++ fpos configuration with i386 GCC 4.6',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_gcc46_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc46/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.debug.mp.gcc46.x32',                    
                ),
                      
                Configuration(
                    id='config.os.portable.language.cpp.tests.fpos.osx.x32.gcc46.release',
                    name='Release OS X C++ fpos configuration with i386 GCC 4.6',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='osx_fpos_x32_gcc46_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc46/Release',
                    
                    toolchain='toolchain.osx.release.mp.gcc46.x32',                    
                ),
            ],
        ),

        # configuration specific for platform GNU/Linux
        Configuration(
              
            id='config.os.portable.language.cpp.tests.fpos.linux',
            name='Test C++ fpos on GNU/Linux configuration',
            description='Common definitions for Debug/Release build configurations running on GNU/Linux',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platform.synthetic.linux',
            ],
                      
            requirements=[
                'enable("package.os.hal.platform.synthetic.linux")',
            ],
                      
            buildFolder='linux/fpos',
            
            artifactFileName='fpos.elf',
            
            children=[
                   
                # GCC x64
                Configuration(
                    id='config.os.portable.diagnostics.tests.fpos.linux.x64.gcc.debug',
                    name='Debug GNU/Linux fpos configuration with x86_64 GCC',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='linux_fpos_x64_gcc_Debug',
                    
                    buildFolder='$(PARENT)/x64/gcc/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.linux.debug.gcc.x64',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.fpos.linux.x64.gcc.release',
                    name='Release GNU/Linux fpos configuration with x86_64 GCC',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='linux_fpos_x64_gcc_Release',
                    
                    buildFolder='$(PARENT)/x64/gcc/Release',
                                          
                    toolchain='toolchain.linux.release.gcc.x64',                    
                ),

                # GCC x32
                Configuration(
                    id='config.os.portable.diagnostics.tests.fpos.linux.x32.gcc.debug',
                    name='Debug GNU/Linux fpos configuration with i386 GCC',
                    description='Debug build configuration for fpos.',
                    
                    buildConfigurationName='linux_fpos_x32_gcc_Debug',
                    
                    buildFolder='$(PARENT)/x32/gcc/Debug',
                    
                    requirements=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.linux.debug.gcc.x32',                    
                ),

                Configuration(
                    id='config.os.portable.diagnostics.tests.fpos.linux.x32.gcc.release',
                    name='Release GNU/Linux fpos configuration with i386 GCC',
                    description='Release build configuration for fpos.',
                    
                    buildConfigurationName='linux_fpos_x32_gcc_Release',
                    
                    buildFolder='$(PARENT)/x32/gcc/Release',

                    toolchain='toolchain.linux.release.gcc.x32',                    
                ),
            ],
        ),	
    ],
)
