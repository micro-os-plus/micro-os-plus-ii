# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Package(
              
    id='package.os.template.minimal',
    name='Minimal set of packages',
    description='The smallest set of packages needed to build a configuration.',
    
    category='template',
    
    loadPackages=[
        'package.os.portable.core',
        'package.os.portable.core.peripheral',
        'package.os.portable.diagnostics',
        'package.os.portable.infrastructure',
        'package.os.portable.language.cpp',
    ],
)

