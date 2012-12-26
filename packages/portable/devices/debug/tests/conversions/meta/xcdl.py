# -*- coding: utf-8 -*-

Package(
    id='package.os.portable.devices.debug.tests.conversions',
    name='Test Debug conversions',
    description='Test all conversions provided by the Debug device.',
    
    kind='test',
    
    loadPackages=[
        'package.os.portable.kernel',
        'package.os.portable.devices.debug',
    ],

    compile=[
        'main.cpp',
    ],
)
