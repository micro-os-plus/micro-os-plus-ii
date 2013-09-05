# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

# ----- LLVM x64 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.llvm.x64.debug',
    name='Debug OS X C++ ios_base configuration with x86_64 LLVM',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_llvm_x64_ios_base_Debug',
    
    buildFolder='$(PARENT)/llvm/x64/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.llvm.x64.release',
    name='Release OS X C++ ios_base configuration with x86_64 LLVM',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_llvm_x64_ios_base_Release',
    
    buildFolder='$(PARENT)/llvm/x64/ios_base/Release',
                          
    toolchain='toolchain.osx.release.llvm.x64',                    
),

# ----- LLVM x32 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.llvm.x32.debug',
    name='Debug OS X C++ ios_base configuration with i386 LLVM',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_llvm_x32_ios_base_Debug',
    
    buildFolder='$(PARENT)/llvm/x32/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.llvm.x32.release',
    name='Release OS X C++ ios_base configuration with i386 LLVM',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_llvm_x32_ios_base_Release',
    
    buildFolder='$(PARENT)/llvm/x32/ios_base/Release',

    toolchain='toolchain.osx.release.llvm.x32',                    
),


# ----- GCC 4.7 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc47.x64.debug',
    name='Debug OS X C++ ios_base configuration with x86_64 GCC 4.7',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc47_x64_ios_base_Debug',
    
    buildFolder='$(PARENT)/gcc47/x64/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc47.x64.release',
    name='Release OS X C++ ios_base configuration with x86_64 GCC 4.7',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc47_x64_ios_base_Release',
    
    buildFolder='$(PARENT)/gcc47/x64/ios_base/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
),

# ----- GCC 4.7 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc47.x32.debug',
    name='Debug OS X C++ ios_base configuration with i386 GCC 4.7',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc47_x32_ios_base_Debug',
    
    buildFolder='$(PARENT)/gcc47/x32/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc47.x32.release',
    name='Release OS X C++ ios_base configuration with i386 GCC 4.7',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc47_x32_ios_base_Release',
    
    buildFolder='$(PARENT)/gcc47/x32/ios_base/Release',

    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
),

# ----- GCC 4.8 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc48.x64.debug',
    name='Debug OS X C++ ios_base configuration with x86_64 GCC 4.8',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc48_x64_ios_base_Debug',
    
    buildFolder='$(PARENT)/gcc48/x64/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc48.x64.release',
    name='Release OS X C++ ios_base configuration with x86_64 GCC 4.8',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc48_x64_ios_base_Release',
    
    buildFolder='$(PARENT)/gcc48/x64/ios_base/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc48.x64',                    
),

# ----- GCC 4.8 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc48.x32.debug',
    name='Debug OS X C++ ios_base configuration with i386 GCC 4.8',
    description='Debug build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc48_x32_ios_base_Debug',
    
    buildFolder='$(PARENT)/gcc48/x32/ios_base/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.ios_base.osx.gcc48.x32.release',
    name='Release OS X C++ ios_base configuration with i386 GCC 4.8',
    description='Release build configuration for C++ ios_base.',
    
    buildConfigurationName='osx_gcc48_x32_ios_base_Release',
    
    buildFolder='$(PARENT)/gcc48/x32/ios_base/Release',

    toolchain='toolchain.osx.release.mp.gcc48.x32',                    
),
# -----------------------------------------------------------------------------
