# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.toolchains.base',
    name='Toolchains base',
    description='The package where all toolchain definition are linked.',

    category='root',
    
    children=[
              
        Toolchain(
          
            id='toolchain.osx.base',
            name='OS X Apple Toolchain Base',
            description='The base for all Apple OS X toolchains.',
    
            category='base',
     
            platformSystem='Darwin',
            
            includeFiles=[
                'osx-llvm.py',
                'osx-mp-gcc.py',
            ],
        ),
              
        Toolchain(
          
            id='toolchain.linux.base',
            name='GNU/Linux Toolchain Base',
            description='The base for all GNU/Linux toolchains.',
    
            category='base',
     
            platformSystem='Linux',
            
            includeFiles=[
                'linux-gcc.py',
            ],
        ),

    ],
)
