# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for platform OS X
Configuration(
      
    id='config.os.portable.tests.minimal.osx',
    name='Test Minimal on OS X configuration',
    description='Common definitions for Debug/Release build configurations running on OS X',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.synthetic.osx',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.synthetic.osx")',                
    ],
              
    buildFolder='osx/minimal',
    
    artefactName='minimal',
    
    children=[
               
        # LLVM x64   
        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.llvm.debug',
            name='Debug OS X Minimal configuration with x86_64 LLVM',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_llvm_Debug',
            
            buildFolder='$(PARENT)/x64/llvm/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.llvm.x64',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.llvm.release',
            name='Release OS X Minimal configuration with x86_64 LLVM',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_llvm_Release',
            
            buildFolder='$(PARENT)/x64/llvm/Release',
                                  
            toolchain='toolchain.osx.release.llvm.x64',
        ),

        # LLVM x32   
        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.llvm.debug',
            name='Debug OS X Minimal configuration with i386 LLVM',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_llvm_Debug',
            
            buildFolder='$(PARENT)/x32/llvm/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.llvm.x32',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.llvm.release',
            name='Release OS X Minimal configuration with i386 LLVM',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_llvm_Release',
            
            buildFolder='$(PARENT)/x32/llvm/Release',
                                  
            toolchain='toolchain.osx.release.llvm.x32',
        ),

        # GCC 4.7 x64
        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.gcc47.debug',
            name='Debug OS X Minimal configuration with x86_64 GCC 4.7',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_gcc47_Debug',
            
            buildFolder='$(PARENT)/x64/gcc47/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
        ),

        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.gcc47.release',
            name='Release OS X Minimal configuration with x86_64 GCC 4.7',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_gcc47_Release',
            
            buildFolder='$(PARENT)/x64/gcc47/Release',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.release.mp.gcc47.x64',                    
        ),

        # GCC 4.7 x32
        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.gcc47.debug',
            name='Debug OS X Minimal configuration with i386 GCC 4.7',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_gcc47_Debug',
            
            buildFolder='$(PARENT)/x32/gcc47/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
        ),

        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.gcc47.release',
            name='Release OS X Minimal configuration with i386 GCC 4.7',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_gcc47_Release',
            
            buildFolder='$(PARENT)/x32/gcc47/Release',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.release.mp.gcc47.x32',                    
        ),
          
        # GCC 4.6 x64   
        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.gcc46.debug',
            name='Debug OS X Minimal configuration with x86_64 GCC 4.6',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_gcc46_Debug',
            
            buildFolder='$(PARENT)/x64/gcc46/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.mp.gcc46.x64',                    
        ),
              
        Configuration(
            id='config.os.portable.tests.minimal.osx.x64.gcc46.release',
            name='Release OS X Minimal configuration with x86_64 GCC 4.6',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x64_gcc46_Release',
            
            buildFolder='$(PARENT)/x64/gcc46/Release',
                                  
            toolchain='toolchain.osx.release.mp.gcc46.x64',                    
        ),

        # GCC 4.6 x32
        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.gcc46.debug',
            name='Debug OS X Minimal configuration with i386 GCC 4.6',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_gcc46_Debug',
            
            buildFolder='$(PARENT)/x32/gcc46/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.debug.mp.gcc46.x32',                    
        ),
              
        Configuration(
            id='config.os.portable.tests.minimal.osx.x32.gcc46.release',
            name='Release OS X Minimal configuration with i386 GCC 4.6',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='osx_minimal_x32_gcc46_Release',
            
            buildFolder='$(PARENT)/x32/gcc46/Release',
            
            toolchain='toolchain.osx.release.mp.gcc46.x32',                    
        ),

    ],
)
      