# micro-os-plus-ii - µOS++ SE

This project is the Second edition of µOS++, written in 2013.

It was modularised using a structure similar to eCos, 
support for Arm Cortex-M devices was added.

An experimental build system based on Python configurations
was implemented as XCDL.

The experience with the component based configuration and build 
system was considered a success, and it validated the concept.

The major weakness was the limitation to manual edits for the
build metadata, since the Python code is not easily editable
via a GUI based IDE, as are the C/C++ settings in Eclipse CDT.

The XCDL configuration and build system constituted the
base for the future [xPack project](https://github.com/xpack).

The project is now archived, and preserved for historical reasons.
