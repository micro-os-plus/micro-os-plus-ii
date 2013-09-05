# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# ---- GNU Tools for ARM Embedded Processors on OS X --------------------------
Configuration(
    id='config.os.portable.core.tests.mutexstress.qemu.osx.aep.gcc.debug',
    name='Debug OS X QEMU Mutex Stress configuration with ARM Embedded GCC',
    description='Debug build configuration for Mutex Stress.',
    
    buildConfigurationName='qemu_osx_aep_gcc_mutexstress_Debug',
    
    buildFolder='$(PARENT)/osx/aep/gcc/mutexstress/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.mutexstress.qemu.osx.aep.gcc.release',
    name='Release OS X QEMU Mutex Stress configuration with ARM Embedded GCC',
    description='Release build configuration for Mutex Stress.',
    
    buildConfigurationName='qemu_osx_aep_gcc_mutexstress_Release',
    
    buildFolder='$(PARENT)/osx/aep/gcc/mutexstress/Release',

    toolchain='toolchain.osx.arm.ep.gcc.release',
),
      
      
# ---- GNU Tools for ARM Embedded Processors on GNU/Linux ---------------------
Configuration(
    id='config.os.portable.core.tests.mutexstress.qemu.linux.aep.gcc.debug',
    name='Debug GNU/Linux QEMU Mutex Stress configuration with ARM Embedded GCC',
    description='Debug build configuration for Mutex Stress.',
    
    buildConfigurationName='qemu_linux_aep_gcc_mutexstress_Debug',
    
    buildFolder='$(PARENT)/linux/aep/gcc/mutexstress/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.mutexstress.qemu.linux.aep.gcc.release',
    name='Release GNU/Linux QEMU Mutex Stress configuration with ARM Embedded GCC',
    description='Release build configuration for Mutex Stress.',
    
    buildConfigurationName='qemu_linux_aep_gcc_mutexstress_Release',
    
    buildFolder='$(PARENT)/linux/aep/gcc/mutexstress/Release',

    toolchain='toolchain.linux.arm.ep.gcc.release',
),
# -----------------------------------------------------------------------------
