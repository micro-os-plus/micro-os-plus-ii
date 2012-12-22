# -*- coding: utf-8 -*-

Component(
    id='os.component.root',
    name='The µOS++ SE repository',
    description='All µOS++ Second Edition components are below this node.',
        
    # The below files are relative to the root of the packages repository.

    # Since the config scripts are located in the 'meta' subfolder, we need to 
    # define how to compute the package root folder, starting from the current 
    # subfolder (one step up in the hierarchy).
    # This value is inherited by all children.
    basePath='..',
    
    # The list of possible relative paths where the sources can be located, 
    # starting from package root folder.
    # This value is inherited by all children.
    sourcesPaths=['src', '.'],
    
    headerPath='include/xcdl/OS_Defines.h',
    
    # Build the list of all available packages, relative to the root of the 
    # packages repository
    
    # WARNING: be sure the list is top down, since forward parent references
    # are not yet implemented!
    
    scripts=[
        'portable/kernel/meta/kernel.py',
        'portable/devices/meta/devices.py',
        'hal/arch/meta/arch.py',
        'hal/platforms/meta/platforms.py',
    ],
    
    
)
