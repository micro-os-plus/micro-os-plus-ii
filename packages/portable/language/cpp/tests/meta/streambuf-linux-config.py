# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.
               
# GCC x64
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc.debug',
    name='Debug GNU/Linux C++ streambuf configuration with x86_64 GCC',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc_Debug',
    
    buildFolder='$(PARENT)/x64/gcc/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc.release',
    name='Release GNU/Linux C++ streambuf configuration with x86_64 GCC',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc_Release',
    
    buildFolder='$(PARENT)/x64/gcc/Release',
                          
    toolchain='toolchain.linux.release.gcc.x64',                    
),

# GCC x32
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc.debug',
    name='Debug GNU/Linux C++ streambuf configuration with i386 GCC',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc_Debug',
    
    buildFolder='$(PARENT)/x32/gcc/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc.release',
    name='Release GNU/Linux C++ streambuf configuration with i386 GCC',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc_Release',
    
    buildFolder='$(PARENT)/x32/gcc/Release',

    toolchain='toolchain.linux.release.gcc.x32',                    
),

# GCC 4.6 x64
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc46.debug',
    name='Debug GNU/Linux C++ streambuf configuration with x86_64 GCC 4.6',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc46_Debug',
    
    buildFolder='$(PARENT)/x64/gcc46/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc46.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc46.release',
    name='Release GNU/Linux C++ streambuf configuration with x86_64 GCC 4.6',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc46_Release',
    
    buildFolder='$(PARENT)/x64/gcc46/Release',
                          
    toolchain='toolchain.linux.release.gcc46.x64',                    
),

# GCC 4.6 x32
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc46.debug',
    name='Debug GNU/Linux C++ streambuf configuration with i386 GCC 4.6',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc46_Debug',
    
    buildFolder='$(PARENT)/x32/gcc46/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc46.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc46.release',
    name='Release GNU/Linux C++ streambuf configuration with i386 GCC 4.6',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc46_Release',
    
    buildFolder='$(PARENT)/x32/gcc46/Release',

    toolchain='toolchain.linux.release.gcc46.x32',                    
),

# GCC 4.7 x64
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc47.debug',
    name='Debug GNU/Linux C++ streambuf configuration with x86_64 GCC 4.7',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc47_Debug',
    
    buildFolder='$(PARENT)/x64/gcc47/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc47.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.gcc47.release',
    name='Release GNU/Linux C++ streambuf configuration with x86_64 GCC 4.7',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_gcc47_Release',
    
    buildFolder='$(PARENT)/x64/gcc47/Release',
                          
    toolchain='toolchain.linux.release.gcc47.x64',                    
),

# GCC 4.7 x32
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc47.debug',
    name='Debug GNU/Linux C++ streambuf configuration with i386 GCC 4.7',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc47_Debug',
    
    buildFolder='$(PARENT)/x32/gcc47/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.gcc47.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.gcc47.release',
    name='Release GNU/Linux C++ streambuf configuration with i386 GCC 4.7',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_gcc47_Release',
    
    buildFolder='$(PARENT)/x32/gcc47/Release',

    toolchain='toolchain.linux.release.gcc47.x32',                    
),

# LLVM x64
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.llvm.debug',
    name='Debug GNU/Linux C++ streambuf configuration with x86_64 LLVM',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_llvm_Debug',
    
    buildFolder='$(PARENT)/x64/llvm/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.llvm.x64',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x64.llvm.release',
    name='Release GNU/Linux C++ streambuf configuration with x86_64 LLVM',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x64_llvm_Release',
    
    buildFolder='$(PARENT)/x64/llvm/Release',
                          
    toolchain='toolchain.linux.release.llvm.x64',                    
),

# LLVM x32
Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.llvm.debug',
    name='Debug GNU/Linux C++ streambuf configuration with i386 LLVM',
    description='Debug build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_llvm_Debug',
    
    buildFolder='$(PARENT)/x32/llvm/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.debug.llvm.x32',                    
),

Configuration(
    id='config.os.portable.core.tests.streambuf.linux.x32.llvm.release',
    name='Release GNU/Linux C++ streambuf configuration with i386 LLVM',
    description='Release build configuration for C++ streambuf.',
    
    buildConfigurationName='linux_streambuf_x32_llvm_Release',
    
    buildFolder='$(PARENT)/x32/llvm/Release',

    toolchain='toolchain.linux.release.llvm.x32',                    
),
