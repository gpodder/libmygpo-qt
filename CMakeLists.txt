project( libmygpo-qt )

cmake_minimum_required( VERSION 2.6 )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII" )

find_package( Qt4 COMPONENTS QtCore QtNetwork QtTest REQUIRED )
set( QT_DONT_USE_QTGUI TRUE )

find_package(QJSON REQUIRED)

include( ${QT_USE_FILE} )

set( MYGPO_LIB_MAJOR_VERSION "0" )
set( MYGPO_LIB_MINOR_VERSION "2" )
set( MYGPO_LIB_PATCH_VERSION "5" )
set( MYGPO_LIB_VERSION "${MYGPO_LIB_MAJOR_VERSION}.${MYGPO_LIB_MINOR_VERSION}.${MYGPO_LIB_PATCH_VERSION}" )

set( MYGPO_LIB_VERSION_SONAME "${MYGPO_LIB_MAJOR_VERSION}.${MYGPO_LIB_MINOR_VERSION}")

if (CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS( -Wall -Wundef -Wcast-align -Wchar-subscripts -Wpointer-arith
       -Wwrite-strings -Wpacked -Wformat-security -Wmissing-format-attribute
       -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor -Werror )
    if ( NOT WIN32 )
        add_definitions( -fvisibility=hidden )
    endif()

endif(CMAKE_COMPILER_IS_GNUCXX)

option(MYGPO_BUILD_TESTS "Build all unit tests" ON)

if(MYGPO_BUILD_TESTS)
  enable_testing()
endif(MYGPO_BUILD_TESTS)

set( CPACK_GENERATOR "TBZ2" "DEB" )
set( CPACK_PACKAGE_VERSION_MAJOR "${MYGPO_LIB_MAJOR_VERSION}" )
set( CPACK_PACKAGE_VERSION_MINOR "${MYGPO_LIB_MINOR_VERSION}" )
set( CPACK_PACKAGE_VERSION_PATCH "${MYGPO_LIB_PATCH_VERSION}" )
set( CPACK_PACKAGE_VERSION "${MYGPO_LIB_VERSION}" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "gpodder-devel@lists.berlios.de" )
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "A c++/qt library to access the APIs provided by GPodder.net." )

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

#add extra search paths for libraries and includes
SET (LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
SET (LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Directory where lib will install")
SET (INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/mygpo-qt" CACHE PATH "The directory the headers are installed in")
# SET (CMAKE_MODULES_INSTALL_DIR "${CMAKE_ROOT}/Modules" CACHE PATH "The directory to install FindLibmygpo-qt.cmake to")

# pkg-config
find_package(PkgConfig)
IF (NOT WIN32)
    IF (PKG_CONFIG_FOUND)
        CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/libmygpo-qt.pc.in
                            ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt.pc
                            @ONLY)
         INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/libmygpo-qt.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
        ENDIF (PKG_CONFIG_DIR)
    ENDIF (PKG_CONFIG_FOUND)
ENDIF (NOT WIN32)

add_subdirectory( src )
#add_subdirectory( extra )
add_subdirectory( tests )
