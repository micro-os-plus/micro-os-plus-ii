# -*- coding: utf-8 -*-

Package(
    id='package.os.root',
    name='The µOS++ SE repository',
    description='All µOS++ Second Edition components are below this node.',

    category='root',
            
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
    
    # Each component tree will generate a subfolder below the build folder
    buildSubFolder='micro-os-plus',
    
    headerFile='include/xcdl/OS_Defines.h',
    
)
