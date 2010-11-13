########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)

#add_definitions( -DDATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/test_data\" )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../src)

macro(add_libmygpo_test _source)
    get_filename_component(_name ${_source} NAME_WE)
    qt4_automoc(${_name} ${_source})
    add_executable(${_name} ${_source})
    target_link_libraries(${_name} mygpo-qt ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QTCORE_QTNETWORK_LIBRARY})
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
endmacro(add_libmygpo_test)

add_libmygpo_test( UrlBuilderTest.cpp )
