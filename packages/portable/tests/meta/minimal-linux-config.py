# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

      
# configuration specific for platform GNU/Linux
Configuration(
      
    id='config.os.portable.tests.minimal.linux',
    name='Test Minimal on GNU/Linux configuration',
    description='Common definitions for Debug/Release build configurations running on GNU/Linux',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.synthetic.linux',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.synthetic.linux")',                
    ],
              
    buildFolder='linux/minimal',
    
    artefactName='minimal',
    
    children=[
               
        # GCC x64
        Configuration(
            id='config.os.portable.tests.minimal.linux.x64.gcc.debug',
            name='Debug OS X Minimal configuration with x86_64 GCC',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='linux_minimal_x64_gcc_Debug',
            
            buildFolder='$(PARENT)/x64/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.linux.debug.gcc.x64',                    
        ),

        Configuration(
            id='config.os.portable.tests.minimal.linux.x64.gcc.release',
            name='Release OS X Minimal configuration with x86_64 GCC',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='linux_minimal_x64_gcc_Release',
            
            buildFolder='$(PARENT)/x64/gcc/Release',
                                  
            toolchain='toolchain.linux.release.gcc.x64',                    
        ),

        # GCC x32
        Configuration(
            id='config.os.portable.tests.minimal.linux.x32.gcc.debug',
            name='Debug OS X Minimal configuration with i386 GCC',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='linux_minimal_x32_gcc_Debug',
            
            buildFolder='$(PARENT)/x32/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.linux.debug.gcc.x32',                    
        ),

        Configuration(
            id='config.os.portable.tests.minimal.linux.x32.gcc.release',
            name='Release OS X Minimal configuration with i386 GCC',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='linux_minimal_x32_gcc_Release',
            
            buildFolder='$(PARENT)/x32/gcc/Release',

            toolchain='toolchain.linux.release.gcc.x32',                    
        ),
    ],
)
