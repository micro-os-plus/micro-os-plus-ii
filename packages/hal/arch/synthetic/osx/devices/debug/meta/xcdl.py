
Package(
    id='package.os.hal.arch.synthetic.osx.debug',
    name='Synthetic OS X architecture debug implementation',
    description='Implementation for the debug device.',
    
    headerDefinition='OS_INCLUDE_HAL_ARCH_SYNTHETIC_OSX_DEVICES_DEBUGIMPLEMENTATION',

    implements=[
        'interface.os.portable.devices.debug',
    ],
          
    sourceFiles=[
        'DebugImplementation.cpp',
    ],
)
