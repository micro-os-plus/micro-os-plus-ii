# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

# ----- LLVM x64 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.llvm.x64.debug',
    name='Debug OS X C++ basic_ios configuration with x86_64 LLVM',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_llvm_x64_basic_ios_Debug',
    
    buildFolder='$(PARENT)/llvm/x64/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.llvm.x64.release',
    name='Release OS X C++ basic_ios configuration with x86_64 LLVM',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_llvm_x64_basic_ios_Release',
    
    buildFolder='$(PARENT)/llvm/x64/basic_ios/Release',
                          
    toolchain='toolchain.osx.release.llvm.x64',                    
),

# ----- LLVM x32 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.llvm.x32.debug',
    name='Debug OS X C++ basic_ios configuration with i386 LLVM',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_llvm_x32_basic_ios_Debug',
    
    buildFolder='$(PARENT)/llvm/x32/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.llvm.x32.release',
    name='Release OS X C++ basic_ios configuration with i386 LLVM',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_llvm_x32_basic_ios_Release',
    
    buildFolder='$(PARENT)/llvm/x32/basic_ios/Release',

    toolchain='toolchain.osx.release.llvm.x32',                    
),


# ----- GCC 4.7 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc47.x64.debug',
    name='Debug OS X C++ basic_ios configuration with x86_64 GCC 4.7',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc47_x64_basic_ios_Debug',
    
    buildFolder='$(PARENT)/gcc47/x64/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc47.x64.release',
    name='Release OS X C++ basic_ios configuration with x86_64 GCC 4.7',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc47_x64_basic_ios_Release',
    
    buildFolder='$(PARENT)/gcc47/x64/basic_ios/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
),

# ----- GCC 4.7 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc47.x32.debug',
    name='Debug OS X C++ basic_ios configuration with i386 GCC 4.7',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc47_x32_basic_ios_Debug',
    
    buildFolder='$(PARENT)/gcc47/x32/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc47.x32.release',
    name='Release OS X C++ basic_ios configuration with i386 GCC 4.7',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc47_x32_basic_ios_Release',
    
    buildFolder='$(PARENT)/gcc47/x32/basic_ios/Release',

    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
),

# ----- GCC 4.8 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc48.x64.debug',
    name='Debug OS X C++ basic_ios configuration with x86_64 GCC 4.8',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc48_x64_basic_ios_Debug',
    
    buildFolder='$(PARENT)/gcc48/x64/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc48.x64.release',
    name='Release OS X C++ basic_ios configuration with x86_64 GCC 4.8',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc48_x64_basic_ios_Release',
    
    buildFolder='$(PARENT)/gcc48/x64/basic_ios/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc48.x64',                    
),

# ----- GCC 4.8 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc48.x32.debug',
    name='Debug OS X C++ basic_ios configuration with i386 GCC 4.8',
    description='Debug build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc48_x32_basic_ios_Debug',
    
    buildFolder='$(PARENT)/gcc48/x32/basic_ios/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.basic_ios.osx.gcc48.x32.release',
    name='Release OS X C++ basic_ios configuration with i386 GCC 4.8',
    description='Release build configuration for C++ basic_ios.',
    
    buildConfigurationName='osx_gcc48_x32_basic_ios_Release',
    
    buildFolder='$(PARENT)/gcc48/x32/basic_ios/Release',

    toolchain='toolchain.osx.release.mp.gcc48.x32',                    
),
# -----------------------------------------------------------------------------
