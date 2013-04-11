# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
    id='component.os.hal.architecture.arm.cortexm.stm32f.lib.cmsis.stm32f10x',
    name='ST Micro ARM Cortex-M STM32F10x family CMSIS',
    description='CMSIS Support for STM32F10X ARM Cortex-M processors.',
    
    category='cmsis',
    
    isEnabled=True,
    
    sourceFiles=[
        'system_stm32f10x.c',
    ],
       
)
