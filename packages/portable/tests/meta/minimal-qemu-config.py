# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# configuration specific for QEMU generic Cortex-M3
Configuration(
      
    id='config.os.portable.tests.minimal.qemu',
    name='Test Minimal on QEMU configuration',
    description='Common definitions for Debug/Release build configurations running on QEMU',
    
    loadPackages=[
        # mandatory platform requirement
        'package.os.hal.platform.synthetic.qemu',
    ],
              
    requirements=[
        # enable the platform    
        'enable("package.os.hal.platform.synthetic.qemu")',                

        # we also need gpio  
        #'enable("component.os.hal.architecture.arm.cortexm.stm32f.stm32f10x.lib.stm.gpio")',              

        # and the i2c trace implementation
        #'enable("component.os.portable.diagnostics.trace.i2c")', 
        
        # we also need the semihosting trace output
        'enable("component.os.hal.architecture.arm.cortexm.qemu.diagnostics.trace.semihosting")',       
    ],
              
    buildFolder='qemu/minimal',
    
    buildTargetCpuOptions='-mcpu=cortex-m3 -mthumb -mfloat-abi=soft',
    
    copyFiles=[
        ('arm_makefile_defs.mk','makefile_defs.mk'),
        ('arm_makefile_targets.mk','makefile_targets.mk'),
    ],
    
    artefactName='minimal',
    
    children=[
               
        # GNU Tools for ARM Embedded Processors on OS X  
        Configuration(
            id='config.os.portable.tests.minimal.qemu.osx.aep.gcc.debug',
            name='Debug QEMU Minimal configuration with ARM Embedded GCC on OS X',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='qemu_minimal_osx_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            #toolchain='toolchain.osx.aep.arm.gcc.debug',
            toolchain='toolchain.osx.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.qemu.osx.aep.gcc.release',
            name='Release QEMU Minimal configuration with ARM Embedded GCC on OS X',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='qemu_minimal_osx_aep_gcc_Release',
            
            buildFolder='$(PARENT)/osx/aep/gcc/Release',

            toolchain='toolchain.osx.aep.arm.gcc.release',
        ),
              
              
        # GNU Tools for ARM Embedded Processors on GNU/Linux 
        Configuration(
            id='config.os.portable.tests.minimal.qemu.linux.aep.gcc.debug',
            name='Debug QEMU Minimal configuration with ARM Embedded GCC on GNU/Linux',
            description='Debug build configuration for Minimal.',
            
            buildConfigurationName='qemu_minimal_linux_aep_gcc_Debug',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Debug',
            
            requirements=[
                'enable("DEBUG")',
            ],
              
            toolchain='toolchain.linux.aep.arm.gcc.debug',
        ),

        Configuration(
            id='config.os.portable.tests.minimal.qemu.linux.aep.gcc.release',
            name='Release QEMU Minimal configuration with ARM Embedded GCC on GNU/Linux',
            description='Release build configuration for Minimal.',
            
            buildConfigurationName='qemu_minimal_linux_aep_gcc_Release',
            
            buildFolder='$(PARENT)/linux/aep/gcc/Release',

            toolchain='toolchain.linux.aep.arm.gcc.release',
        ),
              

    ],
)
