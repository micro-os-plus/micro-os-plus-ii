# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Toolchain(
          
    id='toolchain.osx.llvm.base',
    name='OS X Apple LLVM Base',
    description='The Apple OS X LLVM toolchain base',
    
    category='base',
    
    platformSystem='Darwin',
    
    compilerObjectsExtension='bc',
    makeObjectsVariable='BCS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    
    # These are options common for all versions (debug/release, 32/64)
    compilerWarningOptions='-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-documentation-unknown-command',
    compilerMiscOptions='-emit-llvm -fsigned-char -fsigned-bitfields -fmessage-length=0 -c',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',
    compilerDebugOptions='-g',
    
    # This is just an explicit default, will be usually overwritten by -O0/-O3
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions='-native',
    
    cc=Tool(
        programName='clang',
        description='Apple LLVM Clang',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='clang++',
        description='Apple LLVM Clang++',
        standard='-std=c++11',
        options='',
    ),
          
    asm=Tool(
        programName='clang',
        description='Apple LLVM Clang',
        options='',
    ),

    ld=Tool(
        programName='clang++',
        description='Apple LLVM Clang++ Linker',
        # options='-lc++abi',        
    ),
    
    children=[

        Toolchain(
                  
            id='toolchain.osx.debug.llvm.base',
            name='OS X Apple Debug LLVM Base',
            description='The Apple OS X LLVM toolchain base for debug builds.',
            
            category='base',
            
            compilerOptimisationOptions='-O0',
            #compilerOptimisationOptions='-O3',
            
            children=[
                      
                Toolchain(
                    id='toolchain.osx.debug.llvm.x64',
                    name='OS X Apple Debug LLVM x86_64',
                    description='The Apple OS X LLVM x86_64 toolchain for debug builds.',
                    
                    category='debug',
                    
                    compilerCpu='-m64',
                ),

                Toolchain(
                    id='toolchain.osx.debug.llvm.x32',
                    name='OS X Apple Debug LLVM i386',
                    description='The Apple OS X LLVM i386 toolchain for debug builds.',

                    category='debug',
                    
                    compilerCpu='-m32',
                ),                      
            ],
        ),
              
        Toolchain(
                  
            id='toolchain.osx.release.llvm.base',
            name='OS X Apple Release LLVM Base',
            description='The Apple OS X LLVM toolchain base for release builds.',
            
            category='base',
            
            compilerOptimisationOptions='-O3',
            #compilerOptimisationOptions='-O0',
            
            children=[
                      
                Toolchain(
                    id='toolchain.osx.release.llvm.x64',
                    name='OS X Apple Release LLVM x86_64',
                    description='The Apple OS X LLVM x86_64 toolchain for release builds.',
                    
                    category='release',

                    compilerCpu='-m64',
                ),

                Toolchain(
                    id='toolchain.osx.release.llvm.x32',
                    name='OS X Apple Release LLVM i386',
                    description='The Apple OS X LLVM i386 toolchain for release builds.',
                    
                    category='release',

                    compilerCpu='-m32',
                ),
                      
            ],
        ),
    ],
)


