#[=======================================================================[.rst:
Findlibmsikeyboard
-------

Finds the libmsikeyboard library.

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets, if found:

``libmsikeyboard::libmsikeyboard``
  The libmsikeyboard library

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``libmsikeyboard_FOUND``
  True if the system has the libmsikeyboard library.
``libmsikeyboard_VERSION``
  The version of the libmsikeyboard library which was found.
``libmsikeyboard_INCLUDE_DIRS``
  Include directories needed to use libmsikeyboard.
``libmsikeyboard_LIBRARIES``
  Libraries needed to link to libmsikeyboard.

Cache Variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``libmsikeyboard_INCLUDE_DIR``
  The directory containing ``libmsikeyboard.h``.
``libmsikeyboard_LIBRARY``
  The path to the libmsikeyboard library.

#]=======================================================================]

find_package(PkgConfig)
pkg_check_modules(PC_libmsikeyboard QUIET libmsikeyboard)

find_path(libmsikeyboard_INCLUDE_DIR
        NAMES msikeyboard.h
        PATHS ${PC_libmsikeyboard_INCLUDE_DIRS}
        PATH_SUFFIXES msikeyboard
)
find_library(libmsikeyboard_LIBRARY
        NAMES libmsikeyboard.so libmsikeyboard.dylib
        PATHS ${PC_libmsikeyboard_LIBRARY_DIRS}
)
set(libmsikeyboard_VERSION ${PC_libmsikeyboard_VERSION})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libmsikeyboard
        FOUND_VAR libmsikeyboard_FOUND
        REQUIRED_VARS
        libmsikeyboard_LIBRARY
        libmsikeyboard_INCLUDE_DIR
        VERSION_VAR libmsikeyboard_VERSION
)
if(libmsikeyboard_FOUND)
    set(libmsikeyboard_LIBRARIES ${libmsikeyboard_LIBRARY})
    set(libmsikeyboard_INCLUDE_DIRS ${libmsikeyboard_INCLUDE_DIR})
    set(libmsikeyboard_DEFINITIONS ${PC_libmsikeyboard_CFLAGS_OTHER})
endif()
mark_as_advanced(
        libmsikeyboard_INCLUDE_DIR
        libmsikeyboard_LIBRARY
)
# compatibility variables
set(libmsikeyboard_VERSION_STRING ${libmsikeyboard_VERSION})