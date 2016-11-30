# -*- CMake -*-
# ------------------------------------ #
# CMake library                        #
# Project libmsikeyboard               #
# Author: Alexei Panov <me@elemc.name> #
# ------------------------------------ #

cmake_minimum_required (VERSION 2.8.0)

enable_testing()

if ( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug )
endif ( NOT CMAKE_BUILD_TYPE )
if (NOT DEBUG)
    if ( CMAKE_BUILD_TYPE STREQUAL Debug )
        set (DEBUG 1)
    else ( CMAKE_BUILD_TYPE STREQUAL Debug )
        set (DEBUG 0)
    endif ( CMAKE_BUILD_TYPE STREQUAL Debug )
endif (NOT DEBUG)

if ( NOT APPLE )
    set( LIB_INSTALL_DIR lib${LIB_SUFFIX} )
    set( INCLUDE_INSTALL_DIR include )
    set( CMAKE_SKIP_BUILD_RPATH ON )
else ( NOT APPLE )
    if ( NOT CMAKE_MACOSX_RPATH )
        set( CMAKE_MACOSX_RPATH 0 )
    endif ( NOT CMAKE_MACOSX_RPATH )
endif ( NOT APPLE )

set(BUILD_SHARED_LIBS ON)

set (PROJECT_NAME msikeyboard)

set(MSIKEYBOARD_VERSION_MAJOR 0)
set(MSIKEYBOARD_VERSION_MINOR 1)
set(MSIKEYBOARD_VERSION_PATCH 0)
set(MSIKEYBOARD_VERSION_STRING ${MSIKEYBOARD_VERSION_MAJOR}.${MSIKEYBOARD_VERSION_MINOR}.${MSIKEYBOARD_VERSION_PATCH})

set (HEADERS
    msikeyboard.h
)
set (SOURCES
    msikeyboard.c
)

set (HIDAPI_hidraw_DIR ${CMAKE_SOURCE_DIR}/cmake-modules)
set (HIDAPI_libusb_DIR ${CMAKE_SOURCE_DIR}/cmake-modules)
message( ${HIDAPI_libusb_DIR} )

project (${PROJECT_NAME})

set (DEP_LIB_INCLUDES           "")
set (BUILD_PROJECT_LIBRARIES    "")

IF ( WITH_HIDRAW )
    find_package (HIDAPI_hidraw REQUIRED)
ELSE ( WITH_HIDRAW )
    find_package (HIDAPI_libusb REQUIRED)
ENDIF ( WITH_HIDRAW )
set (BUILD_PROJECT_LIBRARIES ${BUILD_PROJECT_LIBRARIES} ${HIDAPI_LIBRARIES})
set (DEP_LIB_INCLUDES ${DEP_LIB_INCLUDES} ${HIDAPI_INCLUDE_DIR})

include_directories (${CMAKE_CURRENT_BINARY_DIR} ${DEP_LIB_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

# Library
add_library( ${PROJECT_NAME} ${SOURCES} ${HEADERS} )
target_link_libraries (${PROJECT_NAME} ${BUILD_PROJECT_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${MSIKEYBOARD_VERSION_STRING} SOVERSION ${MSIKEYBOARD_VERSION_MAJOR})
if ( APPLE )
    get_target_property(GENERIC_COMPILE_FLAGS ${PROJECT_NAME} COMPILE_FLAGS)
    if( GENERIC_COMPILE_FLAGS STREQUAL "GENERIC_COMPILE_FLAGS-NOTFOUND" )
        set( GENERIC_COMPILE_FLAGS "" )
    endif( GENERIC_COMPILE_FLAGS STREQUAL "GENERIC_COMPILE_FLAGS-NOTFOUND" )
    set( NEW_COMPILE_FLAGS "${GENERIC_COMPILE_FLAGS} -Wno-deprecated-declarations" )
    set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS ${NEW_COMPILE_FLAGS})
endif ( APPLE )

# Install section
if ( NOT APPLE )
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
            LIBRARY DESTINATION ${LIB_INSTALL_DIR}
            ARCHIVE DESTINATION ${LIB_INSTALL_DIR}/static)
    install(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME})
endif ( NOT APPLE )
