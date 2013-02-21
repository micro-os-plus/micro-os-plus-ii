# -*- coding: utf-8 -*-

Configuration(
              
    id='config.os.hal.platforms.synthetic.osx.cl-sjlj.tests.test1',
    name='OS X sjlj test',
    description='Common definitions for debug/release of test1',
    
    requirements=[
        'package.os.platforms.synthetic.osx.cl-sjlj',
    ],
    
    # parent = '',
    
    options={
        'id.1': True,
        'id.2': 7,
        'id.3': 'xyz',
    },
              
    children=[
                
        Configuration(
            id='config.os.hal.platforms.synthetic.osx.cl-sjlj.tests.test1.release',
            name='Release OS X sjlj test1',
            description='Release build configuration for test1',
            buildFolder='osx/cl-sjlj/test1/Release',
        ),

        Configuration(
            id='config.os.hal.platforms.synthetic.osx.cl-sjlj.tests.test1.debug',
            name='Debug OS X sjlj test1',
            description='Debug build configuration for test1',
            buildFolder='osx/cl-sjlj/test1/Debug',
            
            requirements=[
                'PACK',
            ],
                      
            options={
                'id.4': True,
            },
        ),
    ],
)
