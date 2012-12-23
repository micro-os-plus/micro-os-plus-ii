# -*- coding: utf-8 -*-

Component(
    id='os.component.hal.arch.cortexm',
    name='ARM Cortex-M architecture',
    description='Support for all ARM Cortex-M processors.',
    
    kind='architecture',
    
    scripts=[
        'stm32f/meta/family.py',
    ],
)
