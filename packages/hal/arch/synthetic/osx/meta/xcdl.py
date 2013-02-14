# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
    id='package.os.hal.arch.synthetic.osx',
    name='Synthetic OS X architecture',
    description='Support for the family of OS X synthetic targets.',
    
    category='family',   
    
    loadPackages=[
        'package.os.hal.arch.synthetic.posix.infrastructure',
    ], 
)
