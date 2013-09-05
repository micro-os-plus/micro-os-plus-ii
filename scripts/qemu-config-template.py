# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.


# ---- GNU Tools for ARM Embedded Processors on OS X --------------------------
Configuration(
    id='IDPREFIX.ARTEFACTNAME.qemu.osx.aep.gcc.debug',
    name='Debug OS X QEMU ARTEFACTDESCRIPTION configuration with ARM Embedded GCC',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='qemu_osx_aep_gcc_ARTEFACTNAME_Debug',
    
    buildFolder='$(PARENT)/osx/aep/gcc/ARTEFACTNAME/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.osx.arm.ep.gcc.debug',
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.qemu.osx.aep.gcc.release',
    name='Release OS X QEMU ARTEFACTDESCRIPTION configuration with ARM Embedded GCC',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='qemu_osx_aep_gcc_ARTEFACTNAME_Release',
    
    buildFolder='$(PARENT)/osx/aep/gcc/ARTEFACTNAME/Release',

    toolchain='toolchain.osx.arm.ep.gcc.release',
),
      
      
# ---- GNU Tools for ARM Embedded Processors on GNU/Linux ---------------------
Configuration(
    id='IDPREFIX.ARTEFACTNAME.qemu.linux.aep.gcc.debug',
    name='Debug GNU/Linux QEMU ARTEFACTDESCRIPTION configuration with ARM Embedded GCC',
    description='Debug build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='qemu_linux_aep_gcc_ARTEFACTNAME_Debug',
    
    buildFolder='$(PARENT)/linux/aep/gcc/ARTEFACTNAME/Debug',
    
    requirements=[
        'enable("DEBUG")',
    ],
      
    toolchain='toolchain.linux.arm.ep.gcc.debug',
),

Configuration(
    id='IDPREFIX.ARTEFACTNAME.qemu.linux.aep.gcc.release',
    name='Release GNU/Linux QEMU ARTEFACTDESCRIPTION configuration with ARM Embedded GCC',
    description='Release build configuration for ARTEFACTDESCRIPTION.',
    
    buildConfigurationName='qemu_linux_aep_gcc_ARTEFACTNAME_Release',
    
    buildFolder='$(PARENT)/linux/aep/gcc/ARTEFACTNAME/Release',

    toolchain='toolchain.linux.arm.ep.gcc.release',
),
# -----------------------------------------------------------------------------
