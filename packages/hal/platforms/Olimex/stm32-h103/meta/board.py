# -*- coding: utf-8 -*-

Package(
    id = 'os.package.platforms.olimex.stm32-h103',
    name = 'Olimex STM32-H103 board',
    description = 'Support for the Olimex STM32-H103 development board, based on STM32F103.',
    
    platform = 'board',
    
    requires = [
        'os.package.hal.arch.cortexm.stm32f',
    ],
)