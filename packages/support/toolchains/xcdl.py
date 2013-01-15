# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.toolchains.base',
    name='Toolchains base',
    description='The package where all toolchain definition are linked.',

    category='root',    
)


Toolchain(
    id='toolchain.osx.llvm.base',
    name='OS X LLVM x86_64 Base',
    description='The default Mac OS X Apple LLVM x86_64 toolchain base',
    
    category='base',
    parent='package.os.toolchains.base',
    
    platformSystem='Darwin',
    
    compilerObjectsExtension='bc',
    makeObjectsVariable='BCS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    compilerWarningOptions='-Wall',
    compilerMiscOptions='-emit-llvm -fsigned-char -fmessage-length=0 -c',
    compilerDebugOptions='-g3',
    compilerOptimisationOptions='-O0',
    
    linkerMiscOptions='-native',
    
    cc=Tool(
        programName='clang',
        description='LLVM Clang',
        options='',
    ),
          
    cpp=Tool(
        programName='clang++',
        description='LLVM Clang++',    
        options='',
    ),
          
    asm=Tool(
        programName='clang',
        description='LLVM Clang',
        options='',
    ),

    ld=Tool(
        programName='clang++',
        description='LLVM Clang++',    
    ),
    
    children=[
              
        Toolchain(
            id='toolchain.osx.llvm.debug',
            name='OS X LLVM x86_64 Debug',
            description='The default Mac OS X Apple LLVM x86_64 toolchain for debug builds',
            
            category='debug',
            
            # to keep gdb happy, disable optimisations
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
            id='toolchain.osx.llvm.release',
            name='OS X LLVM x86_64 Release',
            description='The default Mac OS X Apple LLVM x86_64 toolchain for release builds',
            
            category='release',
            
            # use an agressive optimisation level
            compilerOptimisationOptions='-O3',
        ),              
    ],
)
