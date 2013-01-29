# -*- coding: utf-8 -*-

# Copyright (C) 2013 Liviu Ionescu.
# This file is part of the uOS++ SE distribution.

Package(
              
    id='package.os.templates.minimal',
    name='Minimal set of packages',
    description='The smallest set of packages needed to build a configuration.',
    
    category='template',
    
    loadPackages=[
        'package.os.portable.core',
        'package.os.portable.devices.debug',
        'package.os.portable.infra',
    ],
)

