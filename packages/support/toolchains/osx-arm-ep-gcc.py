# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Toolchain(
          
    id='toolchain.osx.arm.ep.gcc.base',
    name='OS X ARM Embedded GCC Base',
    description='The OS X ARM Embedded GCC toolchain base',
    
    category='base',
    
    platformSystem='Darwin',
    targetArchitecture='arm',

    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    
    compilerWarningOptions='-Wall -Wextra -Werror -Wabi',
    compilerMiscOptions='-fsigned-char -fsigned-bitfields -fmessage-length=0 -c -ffunction-sections -fdata-sections   -mlittle-endian',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',

    # These are just explicit defaults, will be usually overwritten
    compilerDebugOptions='-g',
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions= '-Wl,--gc-sections -Wl,-Map,map.txt -Wl,--cref -nostartfiles  -Wl,-T,ldscripts/mem_layout.ld -Wl,-T,ldscripts/sections.ld',
    #linkerMiscOptions= '-Wl,--gc-sections -Wl,-Map,map.txt -Wl,--cref -v',
    
    cc=Tool(
        programName='arm-none-eabi-gcc',
        description='OS X ARM Embedded GNU GCC',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='arm-none-eabi-g++',
        description='OS X ARM Embedded GNU G++',
        standard='-std=c++11',
        options='-fno-rtti -fno-exceptions -Wabi -fno-use-cxa-atexit -fno-threadsafe-statics',
    ),
          
    asm=Tool(
        programName='arm-none-eabi-gcc',
        description='OS X ARM Embedded GNU GCC',
        options='',
    ),

    ld=Tool(
        programName='arm-none-eabi-g++',
        description='OS X ARM Embedded GNU G++ Linker',
    ),
    
    children=[

        Toolchain(
                  
            id='toolchain.osx.arm.ep.gcc.debug',
            name='OS X ARM Embedded Debug GCC -O0',
            description='The OS X ARM Embedded GCC toolchain for debug builds, with all optimisations disabled.',
            
            category='debug',
            
            compilerDebugOptions='-g3',
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
                  
            id='toolchain.osx.arm.ep.gcc.debug.o',
            name='OS X ARM Embedded Debug GCC -O',
            description='The OS X ARM Embedded GCC toolchain for debug builds, with default optimisations.',
            
            category='debug',
            
            compilerDebugOptions='-g3',
            compilerOptimisationOptions='-O',
        ),

        Toolchain(
                  
            id='toolchain.osx.arm.ep.gcc.release',
            name='OS X ARM Embedded Release GCC -Os',
            description='The OS X ARM Embedded GCC toolchain for release builds, with space optimisations.',
            
            category='release',
            compilerOptimisationOptions='-Os',
        ),
              
        Toolchain(
                  
            id='toolchain.osx.arm.ep.gcc.release.o0',
            name='OS X ARM Embedded Release GCC -O0',
            description='The OS X ARM Embedded GCC toolchain for release builds, with all optimisations disabled.',
            
            category='release',
            compilerOptimisationOptions='-O0',
        ),

    ],
)
