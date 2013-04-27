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
               
        # ARM Embedded Processors   
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.aep.gcc.debug',
            name='Debug STM32-E407 CMSIS configuration with ARM Embedded GCC',
            description='Debug build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 8)',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32e407.aep.gcc.release',
            name='Release STM32-E407 CMSIS configuration with ARM Embedded GCC',
            description='Release build configuration for CMSIS.',
            
            buildConfigurationName='stm32e407_cmsis_aep_gcc_Release',
            
            buildFolder='$(PARENT)/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
    ],
)
