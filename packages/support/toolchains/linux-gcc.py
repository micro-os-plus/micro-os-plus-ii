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
