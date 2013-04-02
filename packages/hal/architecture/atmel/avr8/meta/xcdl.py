# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.hal.architecture.atmel.avr8',
    name='Atmel AVR8 Architecture',
    description='Support for Atmel AVR8 processors.',
    
    category='architecture',
    
    headerDefinition='OS_INCLUDE_HAL_ARCHITECTURE_ATMEL_AVR8',
      
    isEnabled=False,

    sourceFiles=[
        #'ArchitectureImplementation.cpp',
    ],
    
    implements=[
        # mark this is an architecture
        'interface.os.architecture',
    ],
    
)
