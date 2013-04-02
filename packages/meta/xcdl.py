# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Repository(
    id='package.os.root',
    name='The µOS++ SE repository',
    description='All µOS++ Second Edition components are below this node.',

    # Mark this as the root of the component repository (informative).
    category='root',
    
    # The list of possible relative paths where the sources can be located, 
    # starting from package root folder.
    # This value is inherited by all children.
    sourcesPaths=['src', '.'],
    
    # Each component tree will generate a subfolder below the build folder.
    buildSubFolder='micro-os-plus',
    
    # The default dynamically generated header file, where all definitions that 
    # call for inclusions must be created.
    headerFile='include/portable/core/include/XCDL_Build_Defines.h',
    
    # The folders where to search for include files during build
    buildIncludeFolders=[
        # Each repository must contribute an include path to it's root.
        '$(REPO_DIR)', 
        
        # In addition, the folder where the dynamically generated header files
        # are stored is also used as include folder.
        '$(BUILD_DIR)/include',
    ],
    
    children=[
        
        Interface(
            id='interface.os.architecture',
            name='Active architectures',
            description='Count of active architectures, used for validation.',
        ),
        
        Interface(
            id='interface.os.architecture.family',
            name='Active architecture families',
            description='Count of active architecture families, used for validation.',
        ),
        
        Interface(
            id='interface.os.platform',
            name='Active platforms',
            description='Count of active platforms, used for validation.',
        ),

        Interface(
            id='interface.os.artefact',
            name='Active artefacts',
            description='Count of active artefacts, used for validation.',
        ),

        Option(
            id='option.os.validation',
            name='Root validations',
            description='Check all above counts.',
            
            requirements=[
                          
                # one and only one architecture shall be enabled
                'implementationsOf("interface.os.architecture") == 1',

                # not more than one architecture family shall be enabled
                # (some architectures have no families)
                'implementationsOf("interface.os.architecture.family") <= 1',
                
                # one and only one platform shall be enabled
                'implementationsOf("interface.os.platform") == 1',
                
                # one and only one artefact shall be enabled
                'implementationsOf("interface.os.artefact") == 1',
                
            ],
        ),
    ],
)
