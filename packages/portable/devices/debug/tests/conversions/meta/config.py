# -*- coding: utf-8 -*-

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
        'setValue("package.os.portable.kernel.greeting.app.name", "Test Debug conversions")',
        'setValue("package.os.portable.kernel.greeting.app.version.revision", 2)',
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
                    
                    buildFolder='$(PARENT)/Release',
                ),

                Configuration(
                    id='config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.debug',
                    name='Debug OS X sjlj conversion test configuration',
                    description='Debug build configuration for conversions',
                    
                    buildFolder='$(PARENT)/Debug',
                    
                    preprocessorSymbols=[
                        'DEBUG=1',
                    ],
                ),
            ],
        ),
    ],
)
