# -*- coding: utf-8 -*-

Component(
    id='os.component.hal.platforms',
    name='The µOS++ SE HAL platforms',
    description='All µOS++ Second Edition supported platforms.',
    
    scripts=[
        'Olimex/stm32-h103/meta/board.py',
        'synthetic/osx/cl-sjlj/meta/platform.py',
    ],
)
