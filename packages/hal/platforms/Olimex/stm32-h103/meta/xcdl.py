# -*- coding: utf-8 -*-

Component(
    id='component.os.platforms.olimex.stm32-h103',
    name='Olimex STM32-H103 board',
    description='Support for the Olimex STM32-H103 development board, based on STM32F103.',
    
    kind='board',
    
    enable=[
        'component.os.hal.arch.cortexm.stm32f',
    ],
)
