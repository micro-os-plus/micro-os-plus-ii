# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for Olimex board STM32-E407
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407',
    name='Test CMSIS on STM32-E407 configuration',
    description='Common definitions for Debug/Release build configurations running on STM32-E407',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.olimex.stm32e407',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.olimex.stm32e407")',
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.gpio")',        
        
        'enable("component.os.portable.diagnostics.trace.i2c")',        
    ],
              
    buildFolder='stm32e407/cmsis',
    
    buildTargetCpuOptions='-mcpu=cortex-m4 -mthumb -mfloat-abi=soft',
    
    children=[
               
        # GNU Tools for ARM Embedded Processors on OS X
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.osx.aep.gcc.debug',
            name='Debug STM32-E407 CMSIS configuration with ARM Embedded GCC on OS X',
            description='Debug build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_osx_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 8)',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.osx.aep.gcc.release',
            name='Release STM32-E407 CMSIS configuration with ARM Embedded GCC on OS X',
            description='Release build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_osx_aep_gcc_Release',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
               
        # GNU Tools for ARM Embedded Processors on GNU/Linux
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.linux.aep.gcc.debug',
            name='Debug STM32-E407 CMSIS configuration with ARM Embedded GCC on GNU/Linux',
            description='Debug build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_linux_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 8)',
            ],
              
            toolchain='toolchain.linux.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.linux.aep.gcc.release',
            name='Release STM32-E407 CMSIS configuration with ARM Embedded GCC on GNU/Linux',
            description='Release build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_linux_aep_gcc_Release',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Release',

            toolchain='toolchain.linux.aep.arm.gcc.release',
        ),

    ],
)
