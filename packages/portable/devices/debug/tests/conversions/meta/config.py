# -*- coding: utf-8 -*-

Configuration(
              
    id = 'os.config.portable.devices.debug.tests.conversions',
    name = 'Test Debug conversions',
    description = 'Test all conversions provided by the Debug device.',
    
    requires = [
        'os.component.portable.devices.debug.tests.conversions',
    ],
                  
    children = [
 
        Configuration(
              
            id = 'os.config.portable.devices.debug.tests.conversions.osx.cl-sjlj',
            name = 'Test Debug conversions on OS X sjlj',
            description = 'Common definitions for Debug/Release build configurations running on OS X',
            
            requires=[
                # mandatory platform requirement
                'os.component.platforms.synthetic.osx.cl-sjlj',
            ],
            buildFolder = 'osx/cl-sjlj/debug/conversions',
            
            children = [
                            
                Configuration(
                    id = 'os.config.portable.devices.debug.tests.conversions.osx.cl-sjlj.release',
                    name = 'Release OS X sjlj conversion test',
                    description = 'Release build configuration for conversions',
                    buildFolder = '$(PARENT)/Release',
                ),

                Configuration(
                    id = 'os.config.hal.platforms.synthetic.osx.cl-sjlj.tests.test1.debug',
                    name = 'Debug OS X sjlj conversion test',
                    description = 'Debug build configuration for conversions',
                    buildFolder = '$(PARENT)/Debug',
                    
                    preprocessorSymbols = [
                        'DEBUG=1',
                    ],
                ), 
            ],
        ),             
    ],
)