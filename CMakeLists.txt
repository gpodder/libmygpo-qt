cmake_minimum_required( VERSION 2.6 FATAL_ERROR )

project( libmygpo-qt )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

# Don't use absolute path in Mygpo-qtTargets-$buildType.cmake
set(QT_USE_IMPORTED_TARGETS TRUE)

find_package( Qt4 COMPONENTS QtCore QtNetwork QtTest REQUIRED )
set( QT_DONT_USE_QTGUI TRUE )

find_package(QJSON REQUIRED)

include( ${QT_USE_FILE} )

set( MYGPO_QT_VERSION_MAJOR "1" )
set( MYGPO_QT_VERSION_MINOR "0" )
set( MYGPO_QT_VERSION_PATCH "5" )
set( MYGPO_QT_VERSION "${MYGPO_QT_VERSION_MAJOR}.${MYGPO_QT_VERSION_MINOR}.${MYGPO_QT_VERSION_PATCH}" )

set( MYGPO_QT_SONAME "${MYGPO_QT_VERSION_MAJOR}")

if (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS( -Wcast-align -Wchar-subscripts -Wpointer-arith
       -Wwrite-strings -Wpacked -Wformat-security -Wmissing-format-attribute
       -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor  -Wall -Wextra
       -Wformat=2 -Wundef -Wlogical-op -Wstack-protector -Wmissing-include-dirs
       -Winit-self -Wunsafe-loop-optimizations  -ggdb3 -fno-inline -DQT_STRICT_ITERATORS )
    if ( NOT WIN32 )
        add_definitions( -fvisibility=hidden )
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

option(MYGPO_BUILD_TESTS "Build all unit tests" ON)

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

set(LIB_INSTALL_DIR_SUFFIX "" CACHE STRING "The directories where to install libraries to")
set(LIB_INSTALL_DIR lib${LIB_INSTALL_DIR_SUFFIX} )
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/mygpo-qt" CACHE PATH "The directory the headers are installed in")
set(CMAKECONFIG_INSTALL_DIR ${LIB_INSTALL_DIR}/cmake/mygpo-qt ) 

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
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

# pkg-config
IF (NOT WIN32)
    FIND_PACKAGE(PkgConfig)
    IF (PKG_CONFIG_FOUND)
        CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/libmygpo-qt.pc.in
                            ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt.pc
                            @ONLY)
         INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
    ENDIF (PKG_CONFIG_FOUND)
ENDIF (NOT WIN32)

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
install(EXPORT mygpo-qtExport DESTINATION ${CMAKECONFIG_INSTALL_DIR} FILE Mygpo-qtTargets.cmake )

# figure out the relative path from the installed Config.cmake file to the install prefix (which may be at
# runtime different from the chosen CMAKE_INSTALL_PREFIX if under Windows the package was installed anywhere)
# This relative path will be configured into the BarConfig.cmake
file(RELATIVE_PATH relInstallDir ${CMAKE_INSTALL_PREFIX}/${CMAKECONFIG_INSTALL_DIR} ${CMAKE_INSTALL_PREFIX} )

# Create a BarConfig.cmake file. <name>Config.cmake files are searched by find_package()
# automatically. We configure that file so that we can put any information we want in it,
# e.g. version numbers, include directories, etc.
configure_file(Mygpo-qtConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qtConfig.cmake @ONLY )

# Additionally, when cmake has found a BarConfig.cmake, it can check for a BarConfigVersion.cmake
# in the same directory when figuring out the version of the package when a version
# has been specified in the find_package() call, e.g. find_package(Bar 1.0)
configure_file(Mygpo-qtConfigVersion.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qtConfigVersion.cmake @ONLY )

# Install these two files into the same directory as the generated exports-file.
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qtConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/Mygpo-qtConfigVersion.cmake DESTINATION ${CMAKECONFIG_INSTALL_DIR} )
