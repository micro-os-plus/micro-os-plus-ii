# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.hal.platform.olimex.stm32-h103',
    name='Olimex STM32-H103 board',
    description='Support for the Olimex STM32-H103 development board, based on STM32F103.',
    
    category='board',
    
    # platform packages shall load corresponding hal packages
    loadPackages=[
        'package.os.hal.architecture.cortexm.stm32f',
    ],
)
