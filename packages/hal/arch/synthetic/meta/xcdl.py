# -*- coding: utf-8 -*-

Component(
    id='os.component.hal.arch.synthetic',
    name='Synthetic architectures',
    description='Support for all synthetic architectures. These are \
architectures synthesised on other existing architectures, like OS X, \
Linux, Windows.',

    kind='architecture',
        
    scripts=[
        'osx/meta/xcdl.py',
    ],
)
