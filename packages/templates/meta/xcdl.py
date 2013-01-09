# -*- coding: utf-8 -*-

Package(
              
    id='package.os.templates.minimal',
    name='Minimal set of packages',
    description='The smallest set of packages needed to build a configuration.',
    
    category='template',
    
    loadPackages=[
        'package.os.portable.kernel',
        'package.os.portable.devices.debug',
    ],
)

