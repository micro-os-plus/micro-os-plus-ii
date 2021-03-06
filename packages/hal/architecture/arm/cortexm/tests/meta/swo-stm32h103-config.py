# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for Olimex board STM32-H103
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.swo.stm32h103',
    name='Test SWO on STM32-H103 configuration',
    description='Common definitions for Debug/Release build configurations running on STM32-H103',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.olimex.stm32h103',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.olimex.stm32h103")',  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio")',              

        # and the trace i2c bit-banged implementation
        'enable("component.os.portable.diagnostics.trace.i2c")',        
    ],
              
    buildFolder='stm32h103/swo',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
    
    children=[
               
        # ARM Embedded Processors   
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.swo.stm32h103.aep.gcc.debug',
            name='Debug STM32-H103 SWO configuration with ARM Embedded GCC',
            description='Debug build configuration for SWO.',
            
            buildConfigurationName='stm32h103_swo_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.swo.stm32h103.aep.gcc.release',
            name='Release STM32-H103 SWO configuration with ARM Embedded GCC',
            description='Release build configuration for SWO.',
            
            buildConfigurationName='stm32h103_swo_aep_gcc_Release',
            
            buildFolder='$(PARENT)/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.swo.stm32h103.aep.gcc.release0',
            name='Release -O0 STM32-H103 SWO configuration with ARM Embedded GCC',
            description='Release build configuration for SWO.',
            
            buildConfigurationName='stm32h103_swo_aep_gcc_Release0',
            
            buildFolder='$(PARENT)/aep/gcc/Release0',

            toolchain='toolchain.osx.aep.arm.gcc.release.o0',
        ),

    ],
)
