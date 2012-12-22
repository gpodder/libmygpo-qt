########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)
remove_definitions(-fvisibility=hidden)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

set ( TESTOBJECTS_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../src )

include_directories( ${QT_INCLUDES} ${QJSON_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../src ${TESTOBJECTS_SRCDIR} )

# UrlBuilder library
add_library( UrlBuilder ${TESTOBJECTS_SRCDIR}/UrlBuilder.cpp ${TESTOBJECTS_SRCDIR}/Config.cpp )
# JSONCreator library
QT4_WRAP_CPP(LIBMYGPO_QT_MOC_SRC ${TESTOBJECTS_SRCDIR}/EpisodeAction.h ${TESTOBJECTS_SRCDIR}/EpisodeAction_p.h )
add_library( JsonCreator ${TESTOBJECTS_SRCDIR}/JsonCreator.cpp ${TESTOBJECTS_SRCDIR}/EpisodeAction.cpp ${LIBMYGPO_QT_MOC_SRC})

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_libmygpo_test _source)
    get_filename_component(_name ${_source} NAME_WE)
    QT4_WRAP_CPP(${_name}_MOC_SRC ${_name}.h)
    add_executable(${_name} ${_source} ${${_name}_MOC_SRC})
    target_link_libraries(${_name} ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QT_QTNETWORK_LIBRARY})
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
endmacro(add_libmygpo_test)

add_libmygpo_test( UrlBuilderTest.cpp )
target_link_libraries( UrlBuilderTest UrlBuilder)

add_libmygpo_test( JsonCreatorTest.cpp )
target_link_libraries( JsonCreatorTest JsonCreator ${QJSON_LIBRARIES} )