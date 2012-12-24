# -*- coding: utf-8 -*-

Configuration(
              
    id = 'config.os.portable.devices.debug.tests.conversions',
    name = 'Test Debug conversions',
    description = 'Test all conversions provided by the Debug device.',
    
    enable = [
        'component.os.portable.devices.debug.tests.conversions',
    ],
                  
    children = [
 
        Configuration(
              
            id = 'config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj',
            name = 'Test Debug conversions on OS X sjlj',
            description = 'Common definitions for Debug/Release build configurations running on OS X',
            
            enable=[
                # mandatory platform requirement
                'component.os.platforms.synthetic.osx.cl-sjlj',
            ],
            buildFolder = 'osx/cl-sjlj/debug/conversions',
            
            children = [
                            
                Configuration(
                    id = 'config.os.portable.devices.debug.tests.conversions.osx.cl-sjlj.release',
                    name = 'Release OS X sjlj conversion test',
                    description = 'Release build configuration for conversions',
                    buildFolder = '$(PARENT)/Release',
                ),

                Configuration(
                    id = 'config.os.hal.platforms.synthetic.osx.cl-sjlj.tests.test1.debug',
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