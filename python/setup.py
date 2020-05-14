#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

from setuptools import setup, Extension
from setuptools import find_packages


setup(
    name='msikeyboard',
    version='0.3.3',
    packages=find_packages(),
    ext_modules=[
        Extension(
            'msikeyboard',
            ['msikeyboardmodule.c'],
            include_dirs=['..'],
            libraries=['msikeyboard', 'boost_program_options'],
            library_dirs=['..', '/usr/local/lib', '/usr/lib', '/usr/local/lib64', '/usr/lib64']
        ),
    ],
    author="Alexei Panov",
    author_email="me@elemc.name",
    url="https://github.com/elemc/libmsikeyboard",
    license="GPLv3",
    description="library for set mode, colors and intensity LED MSI keyboards"
)