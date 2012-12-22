# -*- coding: utf-8 -*-

Component(
    id='os.component.platforms.olimex.stm32-h103',
    name='Olimex STM32-H103 board',
    description='Support for the Olimex STM32-H103 development board, based on STM32F103.',
    
    platform='board',
    
    requires=[
        'os.component.hal.arch.cortexm.stm32f',
    ],
)
