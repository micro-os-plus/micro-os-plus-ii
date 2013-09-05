# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.
               
# ----- GCC x64 ---------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc.x64.debug',
    name='Debug GNU/Linux C++ exception configuration with x86_64 GCC',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc_x64_exception_Debug',
    
    buildFolder='$(PARENT)/gcc/x64/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc.x64.release',
    name='Release GNU/Linux C++ exception configuration with x86_64 GCC',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc_x64_exception_Release',
    
    buildFolder='$(PARENT)/gcc/x64/exception/Release',
                          
    toolchain='toolchain.linux.release.gcc.x64',                    
),

# ----- GCC x32 ---------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc.x32.debug',
    name='Debug GNU/Linux C++ exception configuration with i386 GCC',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc_x32_exception_Debug',
    
    buildFolder='$(PARENT)/gcc/x32/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc.x32.release',
    name='Release GNU/Linux C++ exception configuration with i386 GCC',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc_x32_exception_Release',
    
    buildFolder='$(PARENT)/gcc/x32/exception/Release',

    toolchain='toolchain.linux.release.gcc.x32',                    
),

# ----- GCC 4.7 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc47.x64.debug',
    name='Debug GNU/Linux C++ exception configuration with x86_64 GCC 4.7',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc47_x64_exception_Debug',
    
    buildFolder='$(PARENT)/gcc47/x64/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc47.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc47.x64.release',
    name='Release GNU/Linux C++ exception configuration with x86_64 GCC 4.7',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc47_x64_exception_Release',
    
    buildFolder='$(PARENT)/gcc47/x64/exception/Release',
                          
    toolchain='toolchain.linux.release.gcc47.x64',                    
),

# ----- GCC 4.7 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc47.x32.debug',
    name='Debug GNU/Linux C++ exception configuration with i386 GCC 4.7',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc47_x32_exception_Debug',
    
    buildFolder='$(PARENT)/gcc47/x32/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc47.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc47.x32.release',
    name='Release GNU/Linux C++ exception configuration with i386 GCC 4.7',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc47_x32_exception_Release',
    
    buildFolder='$(PARENT)/gcc47/x32/exception/Release',

    toolchain='toolchain.linux.release.gcc47.x32',                    
),

# ----- GCC 4.8 x64 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc48.x64.debug',
    name='Debug GNU/Linux C++ exception configuration with x86_64 GCC 4.8',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc48_x64_exception_Debug',
    
    buildFolder='$(PARENT)/gcc48/x64/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc48.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc48.x64.release',
    name='Release GNU/Linux C++ exception configuration with x86_64 GCC 4.8',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc48_x64_exception_Release',
    
    buildFolder='$(PARENT)/gcc48/x64/exception/Release',
                          
    toolchain='toolchain.linux.release.gcc48.x64',                    
),

# ----- GCC 4.8 x32 -----------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc48.x32.debug',
    name='Debug GNU/Linux C++ exception configuration with i386 GCC 4.8',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc48_x32_exception_Debug',
    
    buildFolder='$(PARENT)/gcc48/x32/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc48.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.gcc48.x32.release',
    name='Release GNU/Linux C++ exception configuration with i386 GCC 4.8',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_gcc48_x32_exception_Release',
    
    buildFolder='$(PARENT)/gcc48/x32/exception/Release',

    toolchain='toolchain.linux.release.gcc48.x32',                    
),


# ----- LLVM x64 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.llvm.x64.debug',
    name='Debug GNU/Linux C++ exception configuration with x86_64 LLVM',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_llvm_x64_exception_Debug',
    
    buildFolder='$(PARENT)/llvm/x64/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.llvm.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.llvm.x64.release',
    name='Release GNU/Linux C++ exception configuration with x86_64 LLVM',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_llvm_x64_exception_Release',
    
    buildFolder='$(PARENT)/llvm/x64/exception/Release',
                          
    toolchain='toolchain.linux.release.llvm.x64',                    
),

# ----- LLVM x32 --------------------------------------------------------------
Configuration(
    id='config.os.portable.core.tests.exception.linux.llvm.x32.debug',
    name='Debug GNU/Linux C++ exception configuration with i386 LLVM',
    description='Debug build configuration for C++ exception.',
    
    buildConfigurationName='linux_llvm_x32_exception_Debug',
    
    buildFolder='$(PARENT)/llvm/x32/exception/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.llvm.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.exception.linux.llvm.x32.release',
    name='Release GNU/Linux C++ exception configuration with i386 LLVM',
    description='Release build configuration for C++ exception.',
    
    buildConfigurationName='linux_llvm_x32_exception_Release',
    
    buildFolder='$(PARENT)/llvm/x32/exception/Release',

    toolchain='toolchain.linux.release.llvm.x32',                    
),
# -----------------------------------------------------------------------------
