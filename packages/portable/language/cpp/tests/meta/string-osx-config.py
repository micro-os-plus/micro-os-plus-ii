# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

# ----- LLVM x64 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.llvm.x64.debug',
    name='Debug OS X C++ string configuration with x86_64 LLVM',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_llvm_x64_string_Debug',
    
    buildFolder='$(PARENT)/llvm/x64/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.llvm.x64.release',
    name='Release OS X C++ string configuration with x86_64 LLVM',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_llvm_x64_string_Release',
    
    buildFolder='$(PARENT)/llvm/x64/string/Release',
                          
    toolchain='toolchain.osx.release.llvm.x64',                    
),

# ----- LLVM x32 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.llvm.x32.debug',
    name='Debug OS X C++ string configuration with i386 LLVM',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_llvm_x32_string_Debug',
    
    buildFolder='$(PARENT)/llvm/x32/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.llvm.x32.release',
    name='Release OS X C++ string configuration with i386 LLVM',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_llvm_x32_string_Release',
    
    buildFolder='$(PARENT)/llvm/x32/string/Release',

    toolchain='toolchain.osx.release.llvm.x32',                    
),


# ----- GCC 4.7 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.gcc47.x64.debug',
    name='Debug OS X C++ string configuration with x86_64 GCC 4.7',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc47_x64_string_Debug',
    
    buildFolder='$(PARENT)/gcc47/x64/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.gcc47.x64.release',
    name='Release OS X C++ string configuration with x86_64 GCC 4.7',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc47_x64_string_Release',
    
    buildFolder='$(PARENT)/gcc47/x64/string/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
),

# ----- GCC 4.7 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.gcc47.x32.debug',
    name='Debug OS X C++ string configuration with i386 GCC 4.7',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc47_x32_string_Debug',
    
    buildFolder='$(PARENT)/gcc47/x32/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.gcc47.x32.release',
    name='Release OS X C++ string configuration with i386 GCC 4.7',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc47_x32_string_Release',
    
    buildFolder='$(PARENT)/gcc47/x32/string/Release',

    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
),

# ----- GCC 4.8 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.gcc48.x64.debug',
    name='Debug OS X C++ string configuration with x86_64 GCC 4.8',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc48_x64_string_Debug',
    
    buildFolder='$(PARENT)/gcc48/x64/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.gcc48.x64.release',
    name='Release OS X C++ string configuration with x86_64 GCC 4.8',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc48_x64_string_Release',
    
    buildFolder='$(PARENT)/gcc48/x64/string/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc48.x64',                    
),

# ----- GCC 4.8 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.string.osx.gcc48.x32.debug',
    name='Debug OS X C++ string configuration with i386 GCC 4.8',
    description='Debug build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc48_x32_string_Debug',
    
    buildFolder='$(PARENT)/gcc48/x32/string/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.string.osx.gcc48.x32.release',
    name='Release OS X C++ string configuration with i386 GCC 4.8',
    description='Release build configuration for C++ string.',
    
    buildConfigurationName='osx_gcc48_x32_string_Release',
    
    buildFolder='$(PARENT)/gcc48/x32/string/Release',

    toolchain='toolchain.osx.release.mp.gcc48.x32',                    
),
# -----------------------------------------------------------------------------
