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
        # we also need gpio  
        'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio")',              
        # and the i2c trace implementation
        'enable("component.os.portable.diagnostics.trace.i2c")',        
    ],
              
    buildFolder='stm32h103/minimal',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
    
    copyFiles=[
        ('stm32h103_makefile_defs.mk','makefile_defs.mk'),
        ('stm32h103_makefile_targets.mk','makefile_targets.mk'),
    ],
    
    artefactName='minimal',
    
    children=[
               
        # GNU Tools for ARM Embedded Processors on OS X  
        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.osx.aep.gcc.debug',
            name='Debug STM32-H103 Minimal configuration with ARM Embedded GCC on OS X',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_osx_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.osx.aep.gcc.release',
            name='Release STM32-H103 Minimal configuration with ARM Embedded GCC on OS X',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_osx_aep_gcc_Release',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
              
              
        # GNU Tools for ARM Embedded Processors on GNU/Linux 
        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.linux.aep.gcc.debug',
            name='Debug STM32-H103 Minimal configuration with ARM Embedded GCC on GNU/Linux',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_linux_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.linux.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.stm32h103.linux.aep.gcc.release',
            name='Release STM32-H103 Minimal configuration with ARM Embedded GCC on GNU/Linux',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='stm32h103_minimal_linux_aep_gcc_Release',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Release',

            toolchain='toolchain.linux.aep.arm.gcc.release',
        ),
              

    ],
)
