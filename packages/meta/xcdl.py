# -*- coding: utf-8 -*-

Package(
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
    headerFile='include/xcdl/OS_Defines.h',
    
    # Each repository must contribute an include path to it's root.
    # The second definition is related to the previous 'headerFile', and 
    # allows the compiler to locate the dynamically generated headers.
    #buildIncludeFolders=['$(REPO)', '$(BUILD)/include'],
    buildIncludeFolders=['/Users/ilg/My Files/MacBookPro Projects/uOS/micro-os-plus-se.git/packages', '/Users/ilg/tmp/build/include'],
    
)
