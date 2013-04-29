# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for Olimex board OLIMEXINO-STM32
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.cmsis.olimexinostm32',
    name='Test CMSIS on OLIMEXINO-STM32 configuration',
    description='Common definitions for Debug/Release build configurations running on OLIMEXINO-STM32',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.olimex.olimexinostm32',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.olimex.olimexinostm32")',
        
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio")',  
        
        # and the trace i2c bit-banged implementation
        'enable("component.os.portable.diagnostics.trace.i2c")',        
            
    ],
              
    buildFolder='olimexinostm32/cmsis',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
        
    children=[
               
        # ARM Embedded Processors   
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.olimexinostm32.aep.gcc.debug',
            name='Debug OLIMEXINO-STM32 CMSIS configuration with ARM Embedded GCC',
            description='Debug build configuration for CMSIS.',
            
            buildConfigurationName='olimexinostm32_cmsis_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
                'setValue("OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DURATION_CLK", 6)',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.olimexinostm32.aep.gcc.release',
            name='Release OLIMEXINO-STM32 CMSIS configuration with ARM Embedded GCC',
            description='Release build configuration for CMSIS.',
            
            buildConfigurationName='olimexinostm32_cmsis_aep_gcc_Release',
            
            buildFolder='$(PARENT)/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
    ],
)
