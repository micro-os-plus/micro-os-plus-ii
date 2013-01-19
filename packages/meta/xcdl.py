# -*- coding: utf-8 -*-

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
        
        
    
)
