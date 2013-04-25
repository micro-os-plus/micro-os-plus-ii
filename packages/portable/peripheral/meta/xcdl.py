# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.core.peripheral',
    name='The µOS++ SE devices package',
    description='All µOS++ Second Edition portable device packages.',
    
    children=[
        Component(
            id='component.os.portable.core.peripheral.activeled',
            name='The main active led',
            description='The active led should be turned on when the processor is active and turned off when the processor is sleeping.',
            
            isEnabled=False,
            
            headerDefinition='OS_HAS_ACTIVELED',
            childrenHeaderFile='include/hal/platform/include/XCDL_LedsDefines.h',
            
            children=[
                Option(
                    id='component.os.portable.core.peripheral.activeled.port',
                    name='The active led port number',
                    description='The number of the GPIO port, starting with 0 for GPIOA.',
                    
                    isEnabled=True,
                    valueType='int',          
                    headerFile='include/hal/platform/include/XCDL_LedsDefines.h',
                    headerDefinition='OS_INTEGER_ACTIVELED_PORT',
                    
                ),

                Option(
                    id='component.os.portable.core.peripheral.activeled.bit',
                    name='The active led bit number',
                    description='The number of the bit in the GPIO port, starting with 0.',
                    
                    isEnabled=True,
                    valueType='int',            
                    headerFile='include/hal/platform/include/XCDL_LedsDefines.h',
                    headerDefinition='OS_INTEGER_ACTIVELED_BIT',
                    
                ),


                Option(
                    id='component.os.portable.core.peripheral.activeled.isactivelow',
                    name='The active led is active low',
                    description='True if the pin must be low for the led to emit light.',
                    
                    isEnabled=True,
                    valueType='bool',
                    defaultValue='True',          
                    headerFile='include/hal/platform/include/XCDL_LedsDefines.h',
                    headerDefinition='OS_BOOL_ACTIVELED_ISACTIVELOW',
                    
                ),
            ],
        ),
    ],
)
