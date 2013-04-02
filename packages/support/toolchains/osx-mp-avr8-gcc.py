# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Toolchain(
          
    id='toolchain.osx.mp.avr8.gcc.base',
    name='OS X MacPorts AVR8 GCC Base',
    description='The OS X MacPorts AVR8 GCC toolchain base',
    
    category='base',
    
    platformSystem='Darwin',
    targetArchitecture='avr8',

    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    
    compilerWarningOptions='-Wall -Wextra -Werror',
    compilerMiscOptions='-fsigned-char -fmessage-length=0 -c -ffunction-sections -fdata-sections',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',

    # These are just explicit defaults, will be usually overwritten
    compilerDebugOptions='-g',
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions= '',
    
    cc=Tool(
        programName='avr-gcc',
        description='MacPorts GNU AVR8 GCC',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='avr-g++',
        description='MacPorts GNU AVR8 G++',
        standard='-std=c++11',
        options='-fno-rtti -fno-exceptions -Wabi',
    ),
          
    asm=Tool(
        programName='avr-gcc',
        description='MacPorts GNU AVR8 GCC',
        options='',
    ),

    ld=Tool(
        programName='avr-g++',
        description='MacPorts GNU AVR8 G++ Linker',
    ),
    
    children=[

        Toolchain(
                  
            id='toolchain.osx.mp.avr8.gcc.debug',
            name='OS X MacPorts Debug GCC AVR8',
            description='The OS X MacPorts GCC AVR8 toolchain for debug builds.',
            
            category='debug',
            
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
                  
            id='toolchain.osx.mp.avr8.gcc.release',
            name='OS X MacPorts Release GCC AVR8',
            description='The OS X MacPorts GCC AVR8 toolchain for release builds.',
            
            category='release',
            compilerOptimisationOptions='-Os',
        ),
    ],
)
