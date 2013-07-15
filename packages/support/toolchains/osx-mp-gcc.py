# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Toolchain(
          
    id='toolchain.osx.mp.gcc.base',
    name='OS X MacPorts GCC Base',
    description='The OS X MacPorts GCC toolchain base',
    
    category='base',
    
    platformSystem='Darwin',

    compilerObjectsExtension='o',
    makeObjectsVariable='OBJS',
    
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$<"',
    
    compilerWarningOptions='-Wall -Wextra -Werror',
    compilerMiscOptions='-fsigned-char -fsigned-bitfields -fmessage-length=0 -c -ffunction-sections -fdata-sections',
    compilerPreprocessorOptions='-D__MICRO_OS_PLUS_PLUS__=1',

    # These are just explicit defaults, will be usually overwritten
    compilerDebugOptions='-g',
    compilerOptimisationOptions='-O',
    
    linkerMiscOptions= '',
    
    cc=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='OS X MacPorts GNU GCC',
        standard='-std=gnu99',
        options='',
    ),
          
    cpp=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='OS X MacPorts GNU G++',
        standard='-std=c++11',
        options='-fno-rtti -fno-exceptions -Wabi',
    ),
          
    asm=Tool(
        programName='$(PREFIX)gcc$(SUFFIX)',
        description='OS X MacPorts GNU GCC',
        options='',
    ),

    ld=Tool(
        programName='$(PREFIX)g++$(SUFFIX)',
        description='OS X MacPorts GNU G++ Linker',
    ),
    
    children=[

        Toolchain(
                  
            id='toolchain.osx.debug.mp.gcc.base',
            name='OS X MacPorts Debug GCC Base',
            description='The OS X MacPorts GCC toolchain base for debug builds.',
            
            category='base',
            
            compilerOptimisationOptions='-O0',
            
            children=[

                Toolchain(
                          
                    id='toolchain.osx.debug.mp.gcc46',
                    name='OS X MacPorts Debug GCC 4.6',
                    description='The OS X MacPorts GCC 4.6 toolchain for debug builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.6',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                    
                    cpp=Tool(
                        # 4.6 is too old for -std=c++11
                        standard='-std=c++0x',
                    ),
                    
                    children=[
                        Toolchain(
                            id='toolchain.osx.debug.mp.gcc46.x64',
                            name='OS X MacPorts Debug GCC 4.6 x86_64',
                            description='The OS X MacPorts GCC 4.6 x86_64 toolchain for debug builds',
                            
                            category='debug',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                            id='toolchain.osx.debug.mp.gcc46.x32',
                            name='OS X MacPorts Debug GCC 4.6 i386',
                            description='The OS X MacPorts GCC 4.6 i386 toolchain for debug builds',

                            category='debug',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ),

                Toolchain(
                          
                    id='toolchain.osx.debug.mp.gcc47',
                    name='OS X MacPorts Debug GCC 4.7',
                    description='The OS X MacPorts GCC 4.7 toolchain for debug builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.7',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                    
                    children=[
                              
                        Toolchain(
                                  
                            id='toolchain.osx.debug.mp.gcc47.x64',
                            name='OS X MacPorts Debug GCC 4.7 x86_64',
                            description='The OS X MacPorts GCC 4.7 x86_64 toolchain for debug builds',
                            
                            category='debug',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                                  
                            id='toolchain.osx.debug.mp.gcc47.x32',
                            name='OS X MacPorts Debug GCC 4.7 i386',
                            description='The OS X MacPorts GCC 4.7 i386 toolchain for debug builds',

                            category='debug',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ), 
                                           
                Toolchain(
                          
                    id='toolchain.osx.debug.mp.gcc48',
                    name='OS X MacPorts Debug GCC 4.8',
                    description='The OS X MacPorts GCC 4.8 toolchain for debug builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.8',
                    
                    # to keep gdb happy, disable optimisations
                    compilerOptimisationOptions='-O0',
                    
                    children=[
                              
                        Toolchain(
                                  
                            id='toolchain.osx.debug.mp.gcc48.x64',
                            name='OS X MacPorts Debug GCC 4.8 x86_64',
                            description='The OS X MacPorts GCC 4.8 x86_64 toolchain for debug builds',
                            
                            category='debug',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                                  
                            id='toolchain.osx.debug.mp.gcc48.x32',
                            name='OS X MacPorts Debug GCC 4.8 i386',
                            description='The OS X MacPorts GCC 4.8 i386 toolchain for debug builds',

                            category='debug',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ), 
                      
            ],
        ),

        Toolchain(
                  
            id='toolchain.osx.release.mp.gcc',
            name='OS X MacPorts Release GCC Base',
            description='The OS X MacPorts GCC toolchain base for release builds.',
            
            category='base',
            compilerOptimisationOptions='-Os',
            
            children=[

                Toolchain(
                          
                    id='toolchain.osx.release.mp.gcc46',
                    name='OS X MacPorts Release GCC 4.6',
                    description='The OS X MacPorts GCC 4.6 toolchain for debug builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.6',
                    
                    # optimise for space, same as for embedded
                    compilerOptimisationOptions='-Os',
                    
                    cpp=Tool(
                        # 4.6 is too old for -std=c++11
                        standard='-std=c++0x',
                    ),
                    
                    children=[
                        Toolchain(
                            id='toolchain.osx.release.mp.gcc46.x64',
                            name='OS X MacPorts Release GCC 4.6 x86_64',
                            description='The OS X MacPorts GCC 4.6 x86_64 toolchain for release builds',
                            
                            category='release',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                            id='toolchain.osx.release.mp.gcc46.x32',
                            name='OS X MacPorts Release GCC 4.6 i386',
                            description='The OS X MacPorts GCC 4.6 i386 toolchain for release builds',

                            category='release',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ),

                Toolchain(
                          
                    id='toolchain.osx.release.mp.gcc47',
                    name='OS X MacPorts Release GCC 4.7',
                    description='The OS X MacPorts GCC 4.7 toolchain for release builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.7',
                    
                    # optimise for space, same as for embedded
                    compilerOptimisationOptions='-Os',
                    #compilerOptimisationOptions='-O1',
                    
                    children=[
                              
                        Toolchain(
                                  
                            id='toolchain.osx.release.mp.gcc47.x64',
                            name='OS X MacPorts Release GCC 4.7 x86_64',
                            description='The OS X MacPorts GCC 4.7 x86_64 toolchain for release builds',
                            
                            category='release',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                                  
                            id='toolchain.osx.release.mp.gcc47.x32',
                            name='OS X MacPorts Release GCC 4.7 i386',
                            description='The OS X MacPorts GCC 4.7 i386 toolchain for release builds',

                            category='release',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ),                      

                Toolchain(
                          
                    id='toolchain.osx.release.mp.gcc48',
                    name='OS X MacPorts Release GCC 4.8',
                    description='The OS X MacPorts GCC 4.8 toolchain for release builds',
                    
                    category='base',

                    programNameSuffix='-mp-4.8',
                    
                    # optimise for space, same as for embedded
                    compilerOptimisationOptions='-Os',
                    #compilerOptimisationOptions='-O1',
                    
                    children=[
                              
                        Toolchain(
                                  
                            id='toolchain.osx.release.mp.gcc48.x64',
                            name='OS X MacPorts Release GCC 4.8 x86_64',
                            description='The OS X MacPorts GCC 4.8 x86_64 toolchain for release builds',
                            
                            category='release',
                            
                            compilerCpu='-m64',
                        ),
        
                        Toolchain(
                                  
                            id='toolchain.osx.release.mp.gcc48.x32',
                            name='OS X MacPorts Release GCC 4.8 i386',
                            description='The OS X MacPorts GCC 4.8 i386 toolchain for release builds',

                            category='release',
                            
                            compilerCpu='-m32',
                        ),
                    ],
                ),                      

            ],
        ),
    ],
)
