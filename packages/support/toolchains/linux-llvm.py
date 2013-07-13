# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Toolchain(
          
    id='toolchain.linux.llvm.base',
    name='GNU/Linux LLVM Base',
    description='The GNU/Linux LLVM toolchain base',
    
    category='base',
    
    platformSystem='Linux',
    
    compilerObjectsExtension='bc',
    makeObjectsVariable='BCS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    
    # These are options common for all versions (debug/release, 32/64)
    compilerWarningOptions='-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic',
    compilerMiscOptions='-emit-llvm -fsigned-char -fsigned-bitfields -fmessage-length=0 -c',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',
    compilerDebugOptions='-g',
    
    # This is just an explicit default, will be usually overwritten by -O0/-O3
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions='-native',
    
    cc=Tool(
        programName='clang',
        description='GNU/Linux LLVM Clang',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='clang++',
        description='GNU/Linux LLVM Clang++',
        standard='-std=c++11',
        options='',
    ),
          
    asm=Tool(
        programName='clang',
        description='GNU/Linux LLVM Clang',
        options='',
    ),

    ld=Tool(
        programName='clang++',
        description='GNU/Linux LLVM Clang++ Linker',
    ),
    
    children=[

        Toolchain(
                  
            id='toolchain.linux.debug.llvm.base',
            name='GNU/Linux Debug LLVM Base',
            description='The GNU/Linux LLVM toolchain base for debug builds.',
            
            category='base',
            
            compilerOptimisationOptions='-O0',
            #compilerOptimisationOptions='-O3',
            
            children=[
                      
                Toolchain(
                    id='toolchain.linux.debug.llvm.x64',
                    name='GNU/Linux Debug LLVM x86_64',
                    description='The GNU/Linux LLVM x86_64 toolchain for debug builds.',
                    
                    category='debug',
                    
                    compilerCpu='-m64',
                ),

                Toolchain(
                    id='toolchain.linux.debug.llvm.x32',
                    name='GNU/Linux Debug LLVM i386',
                    description='The GNU/Linux LLVM i386 toolchain for debug builds.',

                    category='debug',
                    
                    compilerCpu='-m32',
                ),                      
            ],
        ),
              
        Toolchain(
                  
            id='toolchain.linux.release.llvm.base',
            name='GNU/Linux Release LLVM Base',
            description='The GNU/Linux LLVM toolchain base for release builds.',
            
            category='base',
            
            compilerOptimisationOptions='-O3',
            #compilerOptimisationOptions='-O0',
            
            children=[
                      
                Toolchain(
                    id='toolchain.linux.release.llvm.x64',
                    name='GNU/Linux Release LLVM x86_64',
                    description='The GNU/Linux LLVM x86_64 toolchain for release builds.',
                    
                    category='release',

                    compilerCpu='-m64',
                ),

                Toolchain(
                    id='toolchain.linux.release.llvm.x32',
                    name='GNU/Linux Release LLVM i386',
                    description='The GNU/Linux LLVM i386 toolchain for release builds.',
                    
                    category='release',

                    compilerCpu='-m32',
                ),
                      
            ],
        ),
    ],
)


