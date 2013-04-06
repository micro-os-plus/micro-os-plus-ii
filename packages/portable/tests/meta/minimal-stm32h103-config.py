# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for Olimex board STM32-H103
Configuration(
      
    id='config.os.portable.tests.minimal.stm32h103',
    name='Test Minimal on STM32-H103 configuration',
    description='Common definitions for Debug/Release build configurations running on STM32-H103',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.olimex.stm32h103',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.olimex.stm32h103")',                
    ],
              
    buildFolder='stm32h103/minimal',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
    
    copyFiles=[
        ('stm32h104_makefile_defs.mk','makefile_defs.mk'),
        ('stm32h104_makefile_targets.mk','makefile_targets.mk'),
        ('../../../hal/architecture/arm/cortexm/stm32f/ldscripts/stm32f103xB.ld','ldscripts/mem.ld',),
        ('../../../hal/architecture/arm/cortexm/ldscripts/sections.ld','ldscripts/sections.ld'),
    ],
    
    artefactName='minimal',
    
    children=[
               
        # ARM Embedded Processors   
        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.aep.gcc.debug',
            name='Debug STM32-H103 Minimal configuration with ARM Embedded GCC',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.aep.gcc.release',
            name='Release STM32-H103 Minimal configuration with ARM Embedded GCC',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_aep_gcc_Release',
            
            buildFolder='$(PARENT)/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
    ],
)
