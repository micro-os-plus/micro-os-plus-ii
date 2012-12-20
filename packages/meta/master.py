# -*- coding: utf-8 -*-

Package(
    id = 'os.package.root',
    name = 'The µOS++ SE repository',
    description = 'All µOS++ Second Edition packages are below this node.',
        
    # The below files are relative to the root of the packages repository.

    # Since the config scripts are located in the 'meta' subfolder, we need to 
    # define how to compute the package root folder, starting from the current 
    # subfolder (one step up in the hierarchy).
    # This value is inherited by all children.
    basePath = '..',
    
    # The list of possible relative paths where the sources can be located, 
    # starting from package root folder.
    # This value is inherited by all children.
    sourcesPaths = ['src', '.'],
    
    headerPath = 'include/xcdl/OS_Defines.h',
    
    # Build the list of all available packages, relative to the root of the 
    # packages repository
    
    # WARNING: be sure the list is top down, since forward parent references
    # are not yet implemented!
    
    scripts = [
        'portable/devices/debug/meta/debug.py',
        'hal/arch/cortexm/meta/arch.py',
        'hal/arch/synthetic/meta/arch.py',
        'hal/platforms/Olimex/stm32-h103/meta/board.py',
        'hal/platforms/synthetic/osx/cl-sjlj/meta/platform.py',
    ],
    
    
)