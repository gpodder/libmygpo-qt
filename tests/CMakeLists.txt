########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)
remove_definitions(-fvisibility=hidden)

set ( TESTOBJECTS_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../src )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${TESTOBJECTS_SRCDIR})

add_definitions( -Werror )

# RequestHandler library
QT4_WRAP_CPP(REQUESTHANDLER_MOC_SRC ${TESTOBJECTS_SRCDIR}/RequestHandler.h)
add_library(RequestHandler ${TESTOBJECTS_SRCDIR}/RequestHandler.cpp ${REQUESTHANDLER_MOC_SRC})

# UrlBuilder library
QT4_WRAP_CPP(URLBUILDER_MOC_SRC ${TESTOBJECTS_SRCDIR}/UrlBuilder.h)
add_library(UrlBuilder ${TESTOBJECTS_SRCDIR}/UrlBuilder.cpp ${URLBUILDER_MOC_SRC})


set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_libmygpo_test _source)
    get_filename_component(_name ${_source} NAME_WE)
    QT4_WRAP_CPP(${_name}_MOC_SRC ${_name}.h )
    add_executable(${_name} ${_source} ${${_name}_MOC_SRC})
    target_link_libraries(${_name} ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QTCORE_QTNETWORK_LIBRARY})
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
endmacro(add_libmygpo_test)

add_libmygpo_test( UrlBuilderTest.cpp )
target_link_libraries( UrlBuilderTest UrlBuilder)

add_libmygpo_test( RequestHandlerTest.cpp )
target_link_libraries(RequestHandlerTest RequestHandler)