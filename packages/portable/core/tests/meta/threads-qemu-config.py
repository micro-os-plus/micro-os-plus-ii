# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# ---- GNU Tools for ARM Embedded Processors on OS X --------------------------
Configuration(
    id='config.os.portable.core.tests.threads.qemu.osx.aep.gcc.debug',
    name='Debug OS X QEMU Threads configuration with ARM Embedded GCC',
    description='Debug build configuration for Threads.',
    
    buildConfigurationName='qemu_threads_osx_aep_gcc_Debug',
    
    buildFolder='$(PARENT)/osx/aep/gcc/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.aep.arm.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.threads.qemu.osx.aep.gcc.release',
    name='Release OS X QEMU Threads configuration with ARM Embedded GCC',
    description='Release build configuration for Threads.',
    
    buildConfigurationName='qemu_threads_osx_aep_gcc_Release',
    
    buildFolder='$(PARENT)/osx/aep/gcc/Release',

    toolchain='toolchain.osx.aep.arm.gcc.release',
),
      
      
# ---- GNU Tools for ARM Embedded Processors on GNU/Linux ---------------------
Configuration(
    id='config.os.portable.core.tests.threads.qemu.linux.aep.gcc.debug',
    name='Debug GNU/Linux QEMU Threads configuration with ARM Embedded GCC',
    description='Debug build configuration for Threads.',
    
    buildConfigurationName='qemu_threads_linux_aep_gcc_Debug',
    
    buildFolder='$(PARENT)/linux/aep/gcc/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.aep.arm.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.threads.qemu.linux.aep.gcc.release',
    name='Release GNU/Linux QEMU Threads configuration with ARM Embedded GCC',
    description='Release build configuration for Threads.',
    
    buildConfigurationName='qemu_threads_linux_aep_gcc_Release',
    
    buildFolder='$(PARENT)/linux/aep/gcc/Release',

    toolchain='toolchain.linux.aep.arm.gcc.release',
),
# -----------------------------------------------------------------------------
