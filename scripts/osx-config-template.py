# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

# ----- LLVM x64 --------------------------------------------------------------
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.llvm.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with x86_64 LLVM',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_llvm_Debug',
    
    buildFolder='$(PARENT)/x64/llvm/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x64',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.llvm.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with x86_64 LLVM',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_llvm_Release',
    
    buildFolder='$(PARENT)/x64/llvm/Release',
                          
    toolchain='toolchain.osx.release.llvm.x64',                    
),

# LLVM x32
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.llvm.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with i386 LLVM',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_llvm_Debug',
    
    buildFolder='$(PARENT)/x32/llvm/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.llvm.x32',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.llvm.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with i386 LLVM',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_llvm_Release',
    
    buildFolder='$(PARENT)/x32/llvm/Release',

    toolchain='toolchain.osx.release.llvm.x32',                    
),


# ----- GCC 4.7 x64 -----------------------------------------------------------
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.gcc47.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with x86_64 GCC 4.7',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_gcc47_Debug',
    
    buildFolder='$(PARENT)/x64/gcc47/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x64',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.gcc47.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with x86_64 GCC 4.7',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_gcc47_Release',
    
    buildFolder='$(PARENT)/x64/gcc47/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc47.x64',                    
),

# GCC 4.7 x32
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.gcc47.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with i386 GCC 4.7',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_gcc47_Debug',
    
    buildFolder='$(PARENT)/x32/gcc47/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc47.x32',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.gcc47.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with i386 GCC 4.7',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_gcc47_Release',
    
    buildFolder='$(PARENT)/x32/gcc47/Release',

    toolchain='toolchain.osx.release.mp.gcc47.x32',                    
),

# ----- GCC 4.8 x64 -----------------------------------------------------------
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.gcc48.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with x86_64 GCC 4.8',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_gcc48_Debug',
    
    buildFolder='$(PARENT)/x64/gcc48/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x64',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x64.gcc48.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with x86_64 GCC 4.8',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x64_gcc48_Release',
    
    buildFolder='$(PARENT)/x64/gcc48/Release',
                          
    toolchain='toolchain.osx.release.mp.gcc48.x64',                    
),

# GCC 4.8 x32
Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.gcc48.debug',
    name='Debug OS X ARTEFACTDESCRIPTION configuration with i386 GCC 4.8',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_gcc48_Debug',
    
    buildFolder='$(PARENT)/x32/gcc48/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.debug.mp.gcc48.x32',                    
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.osx.x32.gcc48.release',
    name='Release OS X ARTEFACTDESCRIPTION configuration with i386 GCC 4.8',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='osx_ARTEFACTNAME_x32_gcc48_Release',
    
    buildFolder='$(PARENT)/x32/gcc48/Release',

    toolchain='toolchain.osx.release.mp.gcc48.x32',                    
),

