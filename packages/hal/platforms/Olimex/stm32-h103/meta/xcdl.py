# -*- coding: utf-8 -*-

Package(
    id='package.os.hal.platforms.olimex.stm32-h103',
    name='Olimex STM32-H103 board',
    description='Support for the Olimex STM32-H103 development board, based on STM32F103.',
    
    category='board',
    
    # platform packages shall load corresponding hal packages
    loadPackages=[
        'package.os.hal.arch.cortexm.stm32f',
    ],
)
