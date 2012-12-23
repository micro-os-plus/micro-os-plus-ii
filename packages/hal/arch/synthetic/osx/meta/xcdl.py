# -*- coding: utf-8 -*-

Component(
    id='os.component.hal.arch.synthetic.osx',
    name='Synthetic OS X architecture',
    description='Support for the family of OS X synthetic targets.',
    
    kind='family',
    
    scripts=[
        'devices/debug/meta/xcdl.py',
    ],
)
