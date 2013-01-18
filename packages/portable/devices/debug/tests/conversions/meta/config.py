# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

RepositoryFolder('../../../../../..')

Configuration(
              
    id='config.os.portable.devices.debug.tests.conversions',
    name='Test Debug conversions configuration',
    description='Test all conversions provided by the Debug device.',
    
    loadPackages=[
        # mandatory test code requirement
        'package.os.portable.devices.debug.tests.conversions',
        
        # the minimal template
        'package.os.templates.minimal',
    ],
    
    requires=[
        #'setValue("package.os.portable.kernel.greeting.app.name", "Test Debug conversions")',
        'setValue("APP_STRING_APPLICATION_NAME", "Test Debug conversions")',
        
        #'setValue("package.os.portable.kernel.greeting.app.version.revision", 2)',
        'setValue("APP_INTEGER_VERSION_REVISION", 3)',
    ],
                  
    children=[
 
        Configuration(
              
            id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj',
            name='Test Debug conversions on OS X sjlj configuration',
            description='Common definitions for Debug/Release build configurations running on OS X',
            
            loadPackages=[
                # mandatory platform requirement
                'package.os.hal.platforms.synthetic.osx.cl-sjlj',
            ],
            buildFolder='osx/cl-sjlj/debug/conversions',
            
            artifactFileName='conversions.elf',
            
            children=[
                            
                Configuration(
                    id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.release',
                    name='Release OS X sjlj conversion test configuration',
                    description='Release build configuration for conversions',
                    
                    buildFolder='$(PARENT)/llvm/Release',
                    
                    toolchain='toolchain.osx.llvm.release',
                ),

                Configuration(
                    id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.debug',
                    name='Debug OS X sjlj conversion test configuration',
                    description='Debug build configuration for conversions',
                    
                    buildFolder='$(PARENT)/llvm/Debug',
                    
                    requires=[
                        'enable("DEBUG")',
                    ],
                      
                    # no longer needed, generated by the above option        
                    #preprocessorSymbols=[
                    #    'DEBUG=1',
                    #],
                    toolchain='toolchain.osx.llvm.debug',
                ),

                Configuration(
                    id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.gcc46.debug',
                    name='Debug OS X sjlj conversion test configuration with GCC 4.6',
                    description='Debug build configuration for conversions using GNU GCC 4.6',
                    
                    buildFolder='$(PARENT)/gcc46/Debug',
                    
                    requires=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.mp.gcc46.debug',
                ),

                Configuration(
                    id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.gcc47.debug',
                    name='Debug OS X sjlj conversion test configuration with GCC 4.7',
                    description='Debug build configuration for conversions using GNU GCC 4.7',
                    
                    buildFolder='$(PARENT)/gcc47/Debug',
                    
                    requires=[
                        'enable("DEBUG")',
                    ],
                      
                    toolchain='toolchain.osx.mp.gcc47.debug',
                ),

            ],
        ),
    ],
)
