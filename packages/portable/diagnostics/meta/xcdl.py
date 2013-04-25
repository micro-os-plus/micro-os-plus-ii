# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
    id='package.os.portable.diagnostics',
    name='Diagnostics support',
    description='Support for all diagnostics functionality.',
              
    children=[
              
        Component(
            id='component.os.portable.diagnostics.trace',
            name='Diagnostics trace support',
            description='Support for trace output.',
            
            # enabled by DEBUG requirements      
            isEnabled=False,

            requirements=[
                # for the greeting strings
                'enable("package.os.portable.core.greeting")',
                
                # at least one implementation of the above interface
                'implementationsOf("interface.os.portable.diagnostics.trace") == 1',
            ],
                
            sourceFiles=[
                'Trace.cpp',
            ],

            headerDefinition='OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE',
              
            children=[
                Interface(
                    id='interface.os.portable.diagnostics.trace',
                    name='Diagnostics trace output interface',
                    description='Platform implementation for the diagnostics trace output.',
                ),
                      
                Option(
                    id='option.os.portable.diagnostics.trace.ostream',
                    name='Diagnostics trace ostream support',
                    description='Add ostream support to the Trace class.',
                       
                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_OSTREAM_BASE',
                    
                    requirements=[
                        'enable("component.os.portable.language.cpp.streams")',
                    ],
                ),

                Component(
                    id='component.os.portable.diagnostics.trace.i2c',
                    name='Diagnostics trace i2c support',
                    description='Redirect the Trace output via bit-banged I2C.',
                    
                    # enable it to redirect the output via I2C   
                    isEnabled=False,
                    
                    headerDefinition='OS_INCLUDE_PORTABLE_DIAGNOSTICS_TRACE_I2C',
                    
                    children=[
                        
                        Option(
                            id='component.os.portable.diagnostics.trace.i2c.address',
                            name='Diagnostics trace i2c destination address',
                            description='The I2C address of the special converter device (7 bit).',
                            
                            headerFile='include/hal/platform/include/XCDL_TraceI2CDefines.h',
                            headerDefinition='OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_DESTINATION_ADDRESS',
                            valueType='int',
                            valueFormat='(0x{0:02X})',
                            defaultValue=0x28,
                        ),
                              
                        Option(
                            id='component.os.portable.diagnostics.trace.i2c.scl.port',
                            name='Diagnostics trace i2c SCL port number',
                            description='The port number of the SCL pin.',
                            
                            isEnabled=False,
                            headerFile='include/hal/platform/include/XCDL_TraceI2CDefines.h',
                            headerDefinition='OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_PORT',
                            valueType='int',
                        ),

                        Option(
                            id='component.os.portable.diagnostics.trace.i2c.scl.bit',
                            name='Diagnostics trace i2c SCL bit number',
                            description='The port number of the SCL pin.',
                            
                            isEnabled=False,
                            headerFile='include/hal/platform/include/XCDL_TraceI2CDefines.h',
                            headerDefinition='OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SCL_BIT',
                            valueType='int',
                        ),

                        Option(
                            id='component.os.portable.diagnostics.trace.i2c.sda.port',
                            name='Diagnostics trace i2c SDA port number',
                            description='The port number of the SDA pin.',
                            
                            isEnabled=False,
                            headerFile='include/hal/platform/include/XCDL_TraceI2CDefines.h',
                            headerDefinition='OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_PORT',
                            valueType='int',
                        ),

                        Option(
                            id='component.os.portable.diagnostics.trace.i2c.sda.bit',
                            name='Diagnostics trace i2c SDA bit number',
                            description='The port number of the SDA pin.',
                            
                            isEnabled=False,
                            headerFile='include/hal/platform/include/XCDL_TraceI2CDefines.h',
                            headerDefinition='OS_INTEGER_PORTABLE_DIAGNOSTICS_TRACE_I2C_SDA_BIT',
                            valueType='int',
                        ),
                        
                    ],
                ),
            
            ],
        ),
    ],
)
