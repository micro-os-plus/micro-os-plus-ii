# -*- coding: utf-8 -*-

Package(
    id='package.os.toolchains.base',
    name='Toolchains base',
    description='The package where all toolchain definition are linked.',

    category='root',
    
)


Toolchain(
    id='toolchain.osx.llvm.base',
    name='OS X LLVM x64 Base',
    description='The Mac OS X Apple LLVM x64 toolchain base',
    
    category='base',
    parent='package.os.toolchains.base',
    
    compilerObjectsExtension='bc',
    compilerDepsOptions='-MMD -MP',
    compilerOutputOptions='-o "$@"',
    compilerInputOptions='"$"',
    compilerWarningOptions='-Wall',
    compilerMiscOptions='-emit-llvm -c -fmessage-length=0 -fsigned-char',
    compilerDebugOptions='-g3',
    compilerOptimisationOptions='-O0',
    
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
    ld=Tool(
        programName='clang++',
        description='LLVM Clang++',    
    ),
    
    children=[
              
        Toolchain(
            id='toolchain.osx.llvm.debug',
            name='OS X LLVM x64 Debug',
            description='The Mac OS X Apple LLVM x64 toolchain debug',
            
            category='debug',
            
            compilerOptimisationOptions='-O0',

        ),

        Toolchain(
            id='toolchain.osx.llvm.release',
            name='OS X LLVM x64 Release',
            description='The Mac OS X Apple LLVM x64 toolchain release',
            
            category='release',
            
            compilerOptimisationOptions='-O3',

        ),
              
    ],
)
