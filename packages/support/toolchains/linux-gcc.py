# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.


Toolchain(
          
    id='toolchain.linux.gcc.base',
    name='Linux GCC Base',
    description='The Linux GCC toolchain base',
    
    category='base',
    
    platformSystem='Linux',

    programNamePrefix='',
    
    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    compilerWarningOptions='-Wall -Wextra -Werror',
    
    compilerMiscOptions='-fsigned-char -fmessage-length=0 -c -ffunction-sections -fdata-sections',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',
    compilerDebugOptions='-g3',
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions='',
    
    cc=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='Linux GNU GCC',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='Linux GNU G++',
        standard='-std=c++11',
        options='-fno-rtti -fno-exceptions -Wabi',
    ),
          
    asm=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='Linux GNU GCC',
        options='',
    ),

    ld=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='Linux GNU G++',
    ),
    
    children=[
              
        Toolchain(
            id='toolchain.linux.debug.gcc.base',
            name='Linux Debug GCC Base',
            description='The Linux GCC toolchain base for debug builds',
            
            category='base',
            
            # to keep gdb happy, disable optimisations
            compilerOptimisationOptions='-O0',
            
            children=[
                      
                Toolchain(
                          
                    id='toolchain.linux.debug.gcc.x64',
                    name='Linux Debug GCC x86_64',
                    description='The Linux GCC x86_64 toolchain base for debug builds',
                    
                    category='debug',
                    
                    compilerCpu='-arch x86_64',
                ),

                Toolchain(
                          
                    id='toolchain.linux.debug.gcc.x32',
                    name='Linux Debug GCC i386',
                    description='The Linux GCC i386 toolchain base for debug builds',

                    category='debug',
                    
                    compilerCpu='-arch i386',
                ),
            ],            
        ),

        Toolchain(
            id='toolchain.linux.release.gcc.base',
            name='Linux Release GCC Base',
            description='The Linux GCC toolchain base for release builds',
            
            category='release',
            
            # use an aggressive optimisation level
            compilerOptimisationOptions='-Os',

            children=[
                      
                Toolchain(
                          
                    id='toolchain.linux.release.gcc.x64',
                    name='Linux Release GCC x86_64',
                    description='The Linux GCC x86_64 toolchain base for release builds',
                    
                    category='release',
                    
                    compilerCpu='-arch x86_64',
                ),

                Toolchain(
                          
                    id='toolchain.linux.release.gcc.x32',
                    name='Linux Release GCC i386',
                    description='The Linux GCC i386 toolchain base for release builds',

                    category='release',
                    
                    compilerCpu='-arch i386',
                ),
            ],              
        ),
    ],
)
