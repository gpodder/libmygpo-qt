########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)
remove_definitions(-fvisibility=hidden)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_TO_ASCII)

set ( TESTOBJECTS_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../src )

# UrlBuilder library
add_library( UrlBuilder ${TESTOBJECTS_SRCDIR}/UrlBuilder.cpp ${TESTOBJECTS_SRCDIR}/Config.cpp )
target_include_directories( UrlBuilder PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../src ${TESTOBJECTS_SRCDIR} )
target_link_libraries( UrlBuilder PRIVATE Qt${MYGPO_QT_VERSION_SUFFIX}::Core )

# JSONCreator library
qt_wrap_cpp(LIBMYGPO_QT_MOC_SRC ${TESTOBJECTS_SRCDIR}/EpisodeAction.h ${TESTOBJECTS_SRCDIR}/EpisodeAction_p.h )
add_library( JsonCreator ${TESTOBJECTS_SRCDIR}/JsonCreator.cpp ${TESTOBJECTS_SRCDIR}/EpisodeAction.cpp ${TESTOBJECTS_SRCDIR}/qjsonwrapper/Json.cpp ${LIBMYGPO_QT_MOC_SRC})
target_include_directories( JsonCreator PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../src ${TESTOBJECTS_SRCDIR} )
target_link_libraries( JsonCreator PRIVATE Qt${MYGPO_QT_VERSION_SUFFIX}::Core Qt${MYGPO_QT_VERSION_SUFFIX}::Network )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_libmygpo_test _source)
    get_filename_component(_name ${_source} NAME_WE)
    qt_wrap_cpp(${_name}_MOC_SRC ${_name}.h)
    add_executable(${_name} ${_source} ${${_name}_MOC_SRC})
    target_include_directories( ${_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/../src ${TESTOBJECTS_SRCDIR} )
    target_link_libraries(${_name} PRIVATE ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QT_QTNETWORK_LIBRARY})
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
    target_link_libraries(${_name} PRIVATE Qt${MYGPO_QT_VERSION_SUFFIX}::Network Qt${MYGPO_QT_VERSION_SUFFIX}::Test)
endmacro(add_libmygpo_test)

add_libmygpo_test( UrlBuilderTest.cpp )
target_link_libraries( UrlBuilderTest PRIVATE UrlBuilder)

add_libmygpo_test( JsonCreatorTest.cpp )
target_link_libraries( JsonCreatorTest PRIVATE JsonCreator )
