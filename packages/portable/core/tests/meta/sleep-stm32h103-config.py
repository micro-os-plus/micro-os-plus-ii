# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# ---- GNU Tools for ARM Embedded Processors on OS X --------------------------
Configuration(
    id='config.os.portable.core.tests.sleep.stm32h103.osx.aep.gcc.debug',
    name='Debug OS X STM32-H103 Sleep configuration with ARM Embedded GCC',
    description='Debug build configuration for Sleep.',
    
    buildConfigurationName='stm32h103_osx_aep_gcc_sleep_Debug',
    
    buildFolder='$(PARENT)/osx/aep/gcc/sleep/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.sleep.stm32h103.osx.aep.gcc.release',
    name='Release OS X STM32-H103 Sleep configuration with ARM Embedded GCC',
    description='Release build configuration for Sleep.',
    
    buildConfigurationName='stm32h103_osx_aep_gcc_sleep_Release',
    
    buildFolder='$(PARENT)/osx/aep/gcc/sleep/Release',

    toolchain='toolchain.osx.arm.ep.gcc.release',
),
      
      
# ---- GNU Tools for ARM Embedded Processors on GNU/Linux ---------------------
Configuration(
    id='config.os.portable.core.tests.sleep.stm32h103.linux.aep.gcc.debug',
    name='Debug GNU/Linux STM32-H103 Sleep configuration with ARM Embedded GCC',
    description='Debug build configuration for Sleep.',
    
    buildConfigurationName='stm32h103_linux_aep_gcc_sleep_Debug',
    
    buildFolder='$(PARENT)/linux/aep/gcc/sleep/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.sleep.stm32h103.linux.aep.gcc.release',
    name='Release GNU/Linux STM32-H103 Sleep configuration with ARM Embedded GCC',
    description='Release build configuration for Sleep.',
    
    buildConfigurationName='stm32h103_linux_aep_gcc_sleep_Release',
    
    buildFolder='$(PARENT)/linux/aep/gcc/sleep/Release',

    toolchain='toolchain.linux.arm.ep.gcc.release',
),
# -----------------------------------------------------------------------------
