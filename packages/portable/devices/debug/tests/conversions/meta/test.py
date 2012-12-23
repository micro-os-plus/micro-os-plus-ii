# -*- coding: utf-8 -*-

Component(
    id='os.component.portable.devices.debug.tests.conversions',
    name = 'Test Debug conversions',
    description = 'Test all conversions provided by the Debug device.',
    
    requires = [
        'os.component.portable.devices.debug',
    ],

    kind='test',
    
    compile=[
        'main.cpp',
    ],
)