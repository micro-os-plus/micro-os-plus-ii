# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for ST board STM32F4DISCOVERY
Configuration(
    id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32f4discovery',
    name='Test CMSIS on STM32F4DISCOVERY configuration',
    description='Common definitions for Debug/Release build configurations running on STM32F4DISCOVERY',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.stm.stm32f4discovery',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.stm.stm32f4discovery")',
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f40x.lib.stm.gpio")',              

        'enable("component.os.portable.diagnostics.trace.i2c")',        
    ],
              
    buildFolder='stm32f4discovery/cmsis',
    
    buildTargetCpuOptions='-mcpu=cortex-m4 -mthumb -mfloat-abi=soft',
    
    copyFiles=[
        ('cmsis_makefile_defs.mk','makefile_defs.mk'),
        ('cmsis_makefile_targets.mk','makefile_targets.mk'),
    ],
    
    artefactName='cmsis',
    
    children=[
               
        # ARM Embedded Processors   
        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32f4discovery.aep.gcc.debug',
            name='Debug STM32F4DISCOVERY CMSIS configuration with ARM Embedded GCC',
            description='Debug build configuration for CMSIS.',
            
            buildConfigurationName='stm32f4discovery_cmsis_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.hal.architecture.arm.cortexm.tests.cmsis.stm32f4discovery.aep.gcc.release',
            name='Release STM32F4DISCOVERY CMSIS configuration with ARM Embedded GCC',
            description='Release build configuration for CMSIS.',
            
            buildConfigurationName='stm32f4discovery_cmsis_aep_gcc_Release',
            
            buildFolder='$(PARENT)/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
    ],
)
