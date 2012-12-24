# -*- coding: utf-8 -*-

Component(
    id='component.os.portable.devices.debug.tests.conversions',
    name = 'Test Debug conversions',
    description = 'Test all conversions provided by the Debug device.',
    
    kind='test',
    
    enable = [
        'component.os.portable.kernel',
        'component.os.portable.devices.debug',
    ],

    compile=[
        'main.cpp',
    ],
)