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
    name='OS X Apple LLVM Base',
    description='The Apple OS X LLVM toolchain base',
    
    category='base',
    
    parent='package.os.toolchains.base',
    
    platformSystem='Darwin',
    
    compilerObjectsExtension='bc',
    makeObjectsVariable='BCS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    compilerWarningOptions='-Weverything',
    compilerMiscOptions='-emit-llvm -fsigned-char -fmessage-length=0 -c',
    compilerDebugOptions='-g',
    compilerOptimisationOptions='-O0',
    
    linkerMiscOptions='-native',
    
    cc=Tool(
        programName='clang',
        description='Apple LLVM Clang',
        options='',
    ),
          
    cpp=Tool(
        programName='clang++',
        description='Apple LLVM Clang++',    
        options='',
    ),
          
    asm=Tool(
        programName='clang',
        description='Apple LLVM Clang',
        options='',
    ),

    ld=Tool(
        programName='clang++',
        description='Apple LLVM Clang++',    
    ),
    
    children=[
              
        Toolchain(
                  
            id='toolchain.osx.x64.llvm.base',
            name='OS X Apple x86_64 LLVM Base',
            description='The Apple OS X x86_64 LLVM toolchain base',
            
            category='base',

            compilerCpu='-arch x86_64',
            
            children=[
                      
                Toolchain(
                    id='toolchain.osx.x64.llvm.debug',
                    name='OS X Apple x86_64 LLVM Debug',
                    description='The Apple OS X x86_64 LLVM toolchain for debug builds',
                    
                    category='debug',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.osx.x64.llvm.release',
                    name='OS X Apple x86_64 LLVM Release',
                    description='The Apple OS X x86_64 LLVM toolchain for release builds',
                    
                    category='release',
                    
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),              
            ],
        ), 

        Toolchain(
                  
            id='toolchain.osx.x32.llvm.base',
            name='OS X Apple i386 LLVM Base',
            description='The Apple OS X i386 LLVM toolchain base',
            
            category='base',

            compilerCpu='-arch i386',
            
            children=[
                      
                Toolchain(
                    id='toolchain.osx.x32.llvm.debug',
                    name='OS X Apple i386 LLVM Debug',
                    description='The Apple OS X i386 LLVM toolchain for debug builds',
                    
                    category='debug',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.osx.x32.llvm.release',
                    name='OS X Apple i386 LLVM Release',
                    description='The Apple OS X i386 LLVM toolchain for release builds',
                    
                    category='release',
                    
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),              
            ],
        ), 

    ],
)


Toolchain(
          
    id='toolchain.osx.mp.gcc.base',
    name='OS X MacPorts x86_64 GCC Base',
    description='The OS X MacPorts x86_64 GCC toolchain base',
    
    category='base',
    parent='package.os.toolchains.base',
    
    platformSystem='Darwin',

    programNamePrefix='x86_64-apple-darwin12-',
    
    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    compilerWarningOptions='-Wall',
    
    compilerMiscOptions='-fsigned-char -fmessage-length=0 -c',
    compilerDebugOptions='-g3',
    compilerOptimisationOptions='-O0',
    
    compilerCpu='-arch x86_64',
    
    linkerMiscOptions='',
    
    cc=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='MacPorts GNU GCC',
        options='',
    ),
          
    cpp=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='MacPorts GNU G++',    
        options='',
    ),
          
    asm=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='MacPorts GNU GCC',
        options='',
    ),

    ld=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='MacPorts GNU G++',    
    ),
    
    children=[
              
        Toolchain(
            id='toolchain.osx.mp.gcc46.debug',
            name='OS X MacPorts x86_64 GCC 4.6 Debug',
            description='The OS X MacPorts x86_64 GCC 4.6 toolchain for debug builds',
            
            category='debug',
            
            programNameSuffix='-mp-4.6',
            
            # to keep gdb happy, disable optimisations
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
            id='toolchain.osx.mp.gcc46.release',
            name='OS X Mac Ports x86_64 GCC 4.6 Release',
            description='The OS X MacPorts x86_64 GCC 4.6 toolchain for release builds',
            
            category='release',
            
            programNameSuffix='-mp-4.6',
            
            # use an aggressive optimisation level
            compilerOptimisationOptions='-O3',
        ),

        Toolchain(
            id='toolchain.osx.mp.gcc47.debug',
            name='OS X Mac Ports x86_64 GCC 4.7 Debug',
            description='The OS X MacPorts x86_64 GCC 4.7 toolchain for debug builds',
            
            category='debug',
            
            programNameSuffix='-mp-4.7',
            
            # to keep gdb happy, disable optimisations
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
            id='toolchain.osx.mp.gcc47.release',
            name='OS X Mac Ports x86_64 GCC 4.7.2 Release',
            description='The OS X MacPorts x86_64 GCC 4.7 toolchain for release builds',
            
            category='release',
            
            programNameSuffix='-mp-4.7',
            
            # use an aggressive optimisation level
            compilerOptimisationOptions='-O3',
        ),
    
    ],
)


Toolchain(
          
    id='toolchain.linux.gcc.base',
    name='Linux GCC Base',
    description='The Linux GCC toolchain base',
    
    category='base',
    parent='package.os.toolchains.base',
    
    platformSystem='Linux',

    programNamePrefix='',
    
    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    compilerWarningOptions='-Wall',
    
    compilerMiscOptions='-fsigned-char -fmessage-length=0 -c',
    compilerDebugOptions='-g3',
    compilerOptimisationOptions='-O0',
    
    linkerMiscOptions='',
    
    cc=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='Linux GNU GCC',
        options='',
    ),
          
    cpp=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='Linux GNU G++',    
        options='',
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
            id='toolchain.linux.gcc.debug',
            name='Linux GCC Debug',
            description='The Linux GCC toolchain for debug builds',
            
            category='debug',
            
            # to keep gdb happy, disable optimisations
            compilerOptimisationOptions='-O0',
        ),

        Toolchain(
            id='toolchain.linux.gcc.release',
            name='Linux GCC Release',
            description='The Linux GCC toolchain for release builds',
            
            category='release',
            
            # use an aggressive optimisation level
            compilerOptimisationOptions='-O3',
        ),


        Toolchain(
                  
            id='toolchain.linux.x64.gcc.base',
            name='Linux x86_64 GCC Base',
            description='The Linux x86_64 GCC toolchain base',
            
            category='base',

            programNameSuffix='',
            
            compilerCpu='-arch x86_64',
                        
            children=[
                      
                Toolchain(
                    id='toolchain.linux.x64.gcc46.debug',
                    name='Linux x86_64 GCC 4.6 Debug',
                    description='The Linux x86_64 GCC 4.6 toolchain for debug builds',
                    
                    category='debug',
        
                    programNameSuffix='-4.6',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.linux.x64.gcc46.release',
                    name='Linux x86_64 GCC 4.6 Release',
                    description='The Linux x86_64 GCC 4.6 toolchain for release builds',
                    
                    category='release',
                    
                    programNameSuffix='-4.6',
        
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),
        
                Toolchain(
                    id='toolchain.linux.x64.gcc47.debug',
                    name='Linux x86_64 GCC 4.7 Debug',
                    description='The Linux x86_64 GCC 4.7 toolchain for debug builds',
                    
                    category='debug',
        
                    programNameSuffix='-4.7',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.linux.x64.gcc47.release',
                    name='Linux x86_64 GCC 4.7 Release',
                    description='The Linux x86_64 GCC 4.7 toolchain for release builds',
                    
                    category='release',
                    
                    programNameSuffix='-4.7',
        
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),
            ],
        ),
              
              
        Toolchain(
                   
            id='toolchain.linux.x32.gcc.base',
            name='Linux i386 GCC Base',
            description='The Linux i386 GCC toolchain base',
            
            category='base',

            programNameSuffix='',
            
            compilerCpu='-arch i386',
            
            children=[
                      
                Toolchain(
                    id='toolchain.linux.x32.gcc46.debug',
                    name='Linux i386 GCC 4.6 Debug',
                    description='The Linux i386 GCC 4.6 toolchain for debug builds',
                    
                    category='debug',
        
                    programNameSuffix='-4.6',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.linux.x32.gcc46.release',
                    name='Linux i386 GCC 4.6 Release',
                    description='The Linux i386 GCC 4.6 toolchain for release builds',
                    
                    category='release',
                    
                    programNameSuffix='-4.6',
        
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),
        
                Toolchain(
                    id='toolchain.linux.x32.gcc47.debug',
                    name='Linux i386 GCC 4.7 Debug',
                    description='The Linux i386 GCC 4.7 toolchain for debug builds',
                    
                    category='debug',
        
                    programNameSuffix='-4.7',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                ),
        
                Toolchain(
                    id='toolchain.linux.x32.gcc47.release',
                    name='Linux i386 GCC 4.7 Release',
                    description='The Linux i386 GCC 4.7 toolchain for release builds',
                    
                    category='release',
                    
                    programNameSuffix='-4.7',
        
                    # use an aggressive optimisation level
                    compilerOptimisationOptions='-O3',
                ),
            ],
        ),
    ],
)
