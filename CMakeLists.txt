cmake_minimum_required( VERSION 2.8.9 FATAL_ERROR )

project( libmygpo-qt )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

option(BUILD_WITH_QT4 "Build libmygpo-qt with Qt4" OFF)

if( NOT BUILD_WITH_QT4 )
    if( MYGPO_BUILD_TESTS )
        find_package(Qt5 REQUIRED COMPONENTS Core Network Test CONFIG)
    else()
        find_package(Qt5 REQUIRED COMPONENTS Core Network CONFIG)
    endif()
    set(MYGPO_QT_VERSION_SUFFIX 5)

    macro(qt_wrap_cpp)
        qt5_wrap_cpp(${ARGN})
    endmacro()

    # pkg-config names of QtCore and QtNetwork are Qt5Core and Qt5Network for
    # Qt5
    set(MYGPO_QT_MAJOR_VERSION "5")
    set(MYGPO_QT4_QJSON_DEP "")
else()
    message(STATUS "Could not find Qt5, searching for Qt4 instead...")
    message(STATUS "Qt4 Support is deprecated, building with Qt4 is no longer officially supported")
    if( MYGPO_BUILD_TESTS )
        find_package( Qt4 COMPONENTS QtCore QtNetwork QtTest REQUIRED )
    else( MYGPO_BUILD_TESTS )
        find_package( Qt4 COMPONENTS QtCore QtNetwork REQUIRED )
    endif()
    set( QT_DONT_USE_QTGUI TRUE )
    include( ${QT_USE_FILE} )

    macro(qt_wrap_cpp)
        qt4_wrap_cpp(${ARGN})
    endmacro()

    set(MYGPO_QT_MAJOR_VERSION "")
    set(MYGPO_QT4_QJSON_DEP "Requires.private: QJson")

    # QJson is only required for Qt4
    find_package(QJSON REQUIRED)
endif()

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

include(CheckCXXCompilerFlag)

if (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS( -Wcast-align -Wchar-subscripts -Wpointer-arith
       -Wwrite-strings -Wpacked -Wformat-security -Wmissing-format-attribute
       -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor  -Wall -Wextra
       -Wformat=2 -Wundef -Wstack-protector -Wmissing-include-dirs
       -Winit-self -Wunsafe-loop-optimizations  -ggdb3 -fno-inline -DQT_STRICT_ITERATORS )
    if ( NOT WIN32 )
        add_definitions( -fvisibility=hidden )
    endif()

    check_cxx_compiler_flag( -Wlogical-op GNUCXX_HAS_WLOGICAL_OP )
    if ( GNUCXX_HAS_WLOGICAL_OP )
        add_definitions( -Wlogical-op )
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
                            ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt${MYGPO_QT_VERSION_SUFFIX}.pc
                            @ONLY)
         INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt${MYGPO_QT_VERSION_SUFFIX}.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
    ENDIF (PKG_CONFIG_FOUND)
ENDIF (NOT WIN32)

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
