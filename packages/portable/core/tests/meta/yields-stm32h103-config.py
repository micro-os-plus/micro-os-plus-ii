# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# ---- GNU Tools for ARM Embedded Processors on OS X --------------------------
Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.osx.aep.gcc.debug.sh',
    name='Semi-hosting Debug OS X STM32-H103 Yields configuration with ARM Embedded GCC',
    description='Semi-hosting Debug build configuration for Yields.',
    
    buildConfigurationName='stm32h103_osx_aep_gcc_yields_Debug_sh',
    
    buildFolder='$(PARENT)/osx/aep/gcc/yields/Debug/sh',
    
    requirements=[
        'enable("DEBUG")',
        
        # the semi-hosting trace output
        'enable("component.os.hal.architecture.arm.cortexm.diagnostics.trace.semihosting")', 
        
        # and the semi-hosting test suite output             
        'enable("component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.semihosting")',              
    ],
      
    toolchain='toolchain.osx.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.osx.aep.gcc.debug.i2c',
    name='I2C Debug OS X STM32-H103 Yields configuration with ARM Embedded GCC',
    description='I2C Debug build configuration for Yields.',
    
    buildConfigurationName='stm32h103_osx_aep_gcc_yields_Debug_i2c',
    
    buildFolder='$(PARENT)/osx/aep/gcc/yields/Debug/i2c',
    
    requirements=[
        'enable("DEBUG")',
        
        # and the i2c trace output        
        'enable("component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace.i2c")',    
        
        # and the i2c test suite output             
        'enable("component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.i2c")',  
    ],
      
    toolchain='toolchain.osx.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.osx.aep.gcc.release',
    name='Release OS X STM32-H103 Yields configuration with ARM Embedded GCC',
    description='Release build configuration for Yields.',
    
    buildConfigurationName='stm32h103_osx_aep_gcc_yields_Release',
    
    buildFolder='$(PARENT)/osx/aep/gcc/yields/Release',

    toolchain='toolchain.osx.arm.ep.gcc.release',
),
      
      
# ---- GNU Tools for ARM Embedded Processors on GNU/Linux ---------------------
Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.linux.aep.gcc.debug.sh',
    name='Semi-hosting Debug GNU/Linux STM32-H103 Yields configuration with ARM Embedded GCC',
    description='Semi-hosting Debug build configuration for Yields.',
    
    buildConfigurationName='stm32h103_linux_aep_gcc_yields_Debug_sh',
    
    buildFolder='$(PARENT)/linux/aep/gcc/yields/Debug/sh',
    
    requirements=[
        'enable("DEBUG")',
        
        # the semi-hosting trace output
        'enable("component.os.hal.architecture.arm.cortexm.diagnostics.trace.semihosting")',              
        
        # and the semi-hosting test suite output             
        'enable("component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.semihosting")',              
    ],
      
    toolchain='toolchain.linux.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.linux.aep.gcc.debug.i2c',
    name='I2C Debug GNU/Linux STM32-H103 Yields configuration with ARM Embedded GCC',
    description='I2C Debug build configuration for Yields.',
    
    buildConfigurationName='stm32h103_linux_aep_gcc_yields_Debug_i2c',
    
    buildFolder='$(PARENT)/linux/aep/gcc/yields/Debug/i2c',
    
    requirements=[
        'enable("DEBUG")',
        
        # and the i2c trace output        
        'enable("component.os.hal.architecture.arm.cortexm.stm32f1.diagnostics.trace.i2c")',      
        
        # and the i2c test suite output             
        'enable("component.os.hal.architecture.arm.cortexm.infrastructure.testsuite.i2c")',  
    ],
      
    toolchain='toolchain.linux.arm.ep.gcc.debug',
),

Configuration(
    id='config.os.portable.core.tests.yields.stm32h103.linux.aep.gcc.release',
    name='Release GNU/Linux STM32-H103 Yields configuration with ARM Embedded GCC',
    description='Release build configuration for Yields.',
    
    buildConfigurationName='stm32h103_linux_aep_gcc_yields_Release',
    
    buildFolder='$(PARENT)/linux/aep/gcc/yields/Release',

    toolchain='toolchain.linux.arm.ep.gcc.release',
),
# -----------------------------------------------------------------------------
