cmake_minimum_required( VERSION 3.0 FATAL_ERROR )

project( libmygpo-qt )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(CheckCXXCompilerFlag)

list(APPEND COMPILE_OPTIONS
  -Wall
  -Wextra
  -Wpedantic
  -Wunused
  -Wshadow
  -Wundef
  -Wpacked
  -Wuninitialized
  -Wredundant-decls
  -Wunused-parameter
  -Wcast-align
  -Wchar-subscripts
  -Wpointer-arith
  -Wwrite-strings
  -Wformat-security
  -Wold-style-cast
  -Woverloaded-virtual
  -Wnon-virtual-dtor
  -Wstack-protector
  -Winit-self
  -Wmissing-format-attribute
  -Wmissing-include-dirs
  -Wmissing-declarations
  -Wstrict-overflow=2
  -Wformat=2
  -Wdisabled-optimization
  -fno-inline
)
if ( NOT WIN32 )
  list(APPEND COMPILE_OPTIONS -fvisibility=hidden )
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
  list(APPEND COMPILE_OPTIONS
    -ggdb3
    -Wunsafe-loop-optimizations
  )
  check_cxx_compiler_flag( -Wlogical-op GNUCXX_HAS_WLOGICAL_OP )
  if ( GNUCXX_HAS_WLOGICAL_OP )
    list(APPEND COMPILE_OPTIONS -Wlogical-op )
  endif()
endif (CMAKE_COMPILER_IS_GNUCXX)

add_compile_options(${COMPILE_OPTIONS})

add_definitions(-DQT_STRICT_ITERATOR -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII)

option( MYGPO_QT_MAJOR_VERSION "Qt version to use (5 or 6)" )
option( BUILD_WITH_QT5 "Build libmygpo-qt with Qt 5" OFF )
option( BUILD_WITH_QT6 "Build libmygpo-qt with Qt 6" OFF )
option( MYGPO_BUILD_TESTS "Build all unit tests" ON )

set(QT_COMPONENTS Core Network)
if(MYGPO_BUILD_TESTS)
    list(APPEND QT_COMPONENTS Test)
endif()

if( BUILD_WITH_QT6 OR MYGPO_QT_MAJOR_VERSION EQUAL 6 )
    set( MYGPO_QT_MAJOR_VERSION 6 CACHE STRING "" FORCE )
    set( BUILD_WITH_QT6 ON CACHE BOOL "" FORCE )
elseif( BUILD_WITH_QT5 OR MYGPO_QT_MAJOR_VERSION EQUAL 5 )
    set( MYGPO_QT_MAJOR_VERSION 5 CACHE STRING "" FORCE )
    set( BUILD_WITH_QT5 ON CACHE BOOL "" FORCE )
    set( QT_MIN_VERSION 5.2 )
 else()
    # Automatically detect Qt version.
    find_package( QT NAMES Qt6 Qt5 COMPONENTS ${QT_COMPONENTS} REQUIRED )
    if( QT_FOUND AND QT_VERSION_MAJOR EQUAL 6 )
        set( BUILD_WITH_QT6 ON CACHE BOOL "" FORCE )
        set( MYGPO_QT_MAJOR_VERSION 6 CACHE STRING "" FORCE )
    elseif (QT_FOUND AND QT_VERSION_MAJOR EQUAL 5 )
        set( BUILD_WITH_QT5 ON CACHE BOOL "" FORCE )
        set( MYGPO_QT_MAJOR_VERSION 5 CACHE STRING "" FORCE )
        set( QT_MIN_VERSION 5.2 )
    else()
        message( FATAL_ERROR "Could not find a suitable Qt version." )
    endif()
endif()

if( BUILD_WITH_QT5 AND Qt5Core_VERSION VERSION_LESS 5.15.0 )
   macro(qt_wrap_cpp)
       qt5_wrap_cpp(${ARGN})
   endmacro()
endif()

find_package( Qt${MYGPO_QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS ${QT_COMPONENTS} )

set( MYGPO_QT_VERSION_SUFFIX ${MYGPO_QT_MAJOR_VERSION} )
set( QT_DEFAULT_MAJOR_VERSION ${MYGPO_QT_MAJOR_VERSION} )

# Don't use absolute path in Mygpo-qtTargets-$buildType.cmake
# (This will have no effect with CMake < 2.8)
# set(QT_USE_IMPORTED_TARGETS TRUE)

set( MYGPO_QT_VERSION_MAJOR "1" )
set( MYGPO_QT_VERSION_MINOR "1" )
set( MYGPO_QT_VERSION_PATCH "0" )
set( MYGPO_QT_VERSION "${MYGPO_QT_VERSION_MAJOR}.${MYGPO_QT_VERSION_MINOR}.${MYGPO_QT_VERSION_PATCH}" )

set( MYGPO_QT_SONAME "${MYGPO_QT_VERSION_MAJOR}")

#Configure Version.h.in with the actual version number
configure_file( src/Version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/Version.h )

if(MYGPO_BUILD_TESTS)
    INCLUDE(CTest)
    enable_testing()
endif(MYGPO_BUILD_TESTS)

set( CPACK_GENERATOR "TBZ2" "DEB" )
set( CPACK_PACKAGE_VERSION_MAJOR "${MYGPO_QT_VERSION_MAJOR}" )
set( CPACK_PACKAGE_VERSION_MINOR "${MYGPO_QT_VERSION_MINOR}" )
set( CPACK_PACKAGE_VERSION_PATCH "${MYGPO_QT_VERSION_PATCH}" )
set( CPACK_PACKAGE_VERSION "${MYGPO_QT_VERSION}" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "gpodder@freelists.org" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "A c++/qt library to access the APIs provided by gpodder.net." )

set(LIB_SUFFIX "" CACHE STRING "The directories where to install libraries to")
set(LIB_INSTALL_DIR lib${LIB_SUFFIX} )
set(LIB_DIR_PKGCONF "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/mygpo-qt${MYGPO_QT_VERSION_SUFFIX}" CACHE PATH "The directory the headers are installed in")
set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/mygpo-qt${MYGPO_QT_VERSION_SUFFIX})

if( APPLE )
    set( CPACK_GENERATOR "DragNDrop" )
    set( CPACK_DMG_FORMAT "UDBZ" )
    set( CPACK_DMG_VOLUME_NAME "libmygpo-qt" )
    set( CPACK_SYSTEM_NAME "OSX" )
endif( APPLE )

include(CPack)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                         COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

# make uninstall support
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# pkg-config
if (NOT WIN32)
    find_package(PkgConfig)
    if (PKG_CONFIG_FOUND)
        configure_file (${CMAKE_CURRENT_SOURCE_DIR}/libmygpo-qt.pc.in
                            ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt${MYGPO_QT_VERSION_SUFFIX}.pc
                            @ONLY)
         install (FILES ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt${MYGPO_QT_VERSION_SUFFIX}.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
    endif (PKG_CONFIG_FOUND)
endif (NOT WIN32)

set(MYGPO_QT_TARGET_NAME mygpo-qt${MYGPO_QT_VERSION_SUFFIX} CACHE INTERNAL "" FORCE )

add_subdirectory( src )
if(MYGPO_BUILD_TESTS)
    add_subdirectory( tests )
endif(MYGPO_BUILD_TESTS)

# This "exports" all targets which have been put into the export set "BarExport".
# This means that cmake generates a file with the given filename, which can later on be loaded
# by projects using this package.
# This file contains add_library(bar IMPORTED) statements for each target in the export set, so
# when loaded later on cmake will create "imported" library targets from these, which can be used
# in many ways in the same way as a normal library target created via a normal add_library().
install(EXPORT ${MYGPO_QT_TARGET_NAME}Export DESTINATION ${CMAKECONFIG_INSTALL_DIR} FILE Mygpo-qt${MYGPO_QT_VERSION_SUFFIX}Targets.cmake )

# figure out the relative path from the installed Config.cmake file to the install prefix (which may be at
# runtime different from the chosen CMAKE_INSTALL_PREFIX if under Windows the package was installed anywhere)
# This relative path will be configured into the BarConfig.cmake
file(RELATIVE_PATH relInstallDir ${CMAKE_INSTALL_PREFIX}/${CMAKECONFIG_INSTALL_DIR} ${CMAKE_INSTALL_PREFIX} )

# Create a BarConfig.cmake file. <name>Config.cmake files are searched by find_package()
# automatically. We configure that file so that we can put any information we want in it,
# e.g. version numbers, include directories, etc.
configure_file(Mygpo-qtConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qt${MYGPO_QT_VERSION_SUFFIX}Config.cmake @ONLY )

# Additionally, when cmake has found a BarConfig.cmake, it can check for a BarConfigVersion.cmake
# in the same directory when figuring out the version of the package when a version
# has been specified in the find_package() call, e.g. find_package(Bar 1.0)
configure_file(Mygpo-qtConfigVersion.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qt${MYGPO_QT_VERSION_SUFFIX}ConfigVersion.cmake @ONLY )

# Install these two files into the same directory as the generated exports-file.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qt${MYGPO_QT_VERSION_SUFFIX}Config.cmake ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qt${MYGPO_QT_VERSION_SUFFIX}ConfigVersion.cmake DESTINATION ${CMAKECONFIG_INSTALL_DIR} )
