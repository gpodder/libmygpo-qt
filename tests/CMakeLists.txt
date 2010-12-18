########### next target ###############
# QTEST_MAIN is using QApplication when QT_GUI_LIB is defined
remove_definitions(-DQT_GUI_LIB)
remove_definitions(-fvisibility=hidden)

set ( TESTOBJECTS_SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/../src )

include_directories(  ${QJSON_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${TESTOBJECTS_SRCDIR}  )

add_definitions( -Werror )


set ( APIREQUEST_SRC
  ${TESTOBJECTS_SRCDIR}/AddRemoveResult.cpp
  ${TESTOBJECTS_SRCDIR}/Tag.cpp 
  ${TESTOBJECTS_SRCDIR}/JsonParser.cpp 
  ${TESTOBJECTS_SRCDIR}/Podcast.cpp
  ${TESTOBJECTS_SRCDIR}/Episode.cpp 
  ${TESTOBJECTS_SRCDIR}/ApiRequest.cpp
  ${TESTOBJECTS_SRCDIR}/RequestHandler.cpp
  ${TESTOBJECTS_SRCDIR}/UrlBuilder.cpp
  ${TESTOBJECTS_SRCDIR}/TagList.cpp
  ${TESTOBJECTS_SRCDIR}/EpisodeList.cpp
  ${TESTOBJECTS_SRCDIR}/PodcastList.cpp
  ${TESTOBJECTS_SRCDIR}/RequestExceptions.cpp
)


set ( APIREQUEST_H
  ${TESTOBJECTS_SRCDIR}/AddRemoveResult.h
  ${TESTOBJECTS_SRCDIR}/JsonParser.h
  ${TESTOBJECTS_SRCDIR}/mygpo.h
  ${TESTOBJECTS_SRCDIR}/mygpo_export.h
  ${TESTOBJECTS_SRCDIR}/Podcast.h
  ${TESTOBJECTS_SRCDIR}/Episode.h
  ${TESTOBJECTS_SRCDIR}/Tag.h
  ${TESTOBJECTS_SRCDIR}/ApiRequest.h
  ${TESTOBJECTS_SRCDIR}/RequestHandler.h
  ${TESTOBJECTS_SRCDIR}/UrlBuilder.h
  ${TESTOBJECTS_SRCDIR}/RequestExceptions.h
  ${TESTOBJECTS_SRCDIR}/TagList.h
  ${TESTOBJECTS_SRCDIR}/EpisodeList.h
  ${TESTOBJECTS_SRCDIR}/PodcastList.h
)

QT4_WRAP_CPP(APIREQUEST_MOC_SRC ${APIREQUEST_H} )
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/PodcastList.cpp PodcastList.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/EpisodeList.cpp EpisodeList.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/Episode.cpp Episode.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/Podcast.cpp Podcast.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/AddRemoveResult.cpp AddRemoveResult.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/TagList.cpp TagList.moc)
QT4_GENERATE_MOC(${TESTOBJECTS_SRCDIR}/Tag.cpp Tag.moc)

# ApiRequest library
add_library(ApiRequest ${APIREQUEST_SRC} ${APIREQUEST_MOC_SRC} PodcastList.moc EpisodeList.moc Episode.moc Podcast.moc AddRemoveResult.moc TagList.moc Tag.moc)

# RequestHandler library
QT4_WRAP_CPP(REQUESTHANDLER_MOC_SRC ${TESTOBJECTS_SRCDIR}/RequestHandler.h)
add_library(RequestHandler ${TESTOBJECTS_SRCDIR}/RequestHandler.cpp ${REQUESTHANDLER_MOC_SRC})

# UrlBuilder library
QT4_WRAP_CPP(URLBUILDER_MOC_SRC ${TESTOBJECTS_SRCDIR}/UrlBuilder.h)
add_library(UrlBuilder ${TESTOBJECTS_SRCDIR}/UrlBuilder.cpp ${URLBUILDER_MOC_SRC})

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro(add_libmygpo_test _source)
    get_filename_component(_name ${_source} NAME_WE)
    QT4_WRAP_CPP(${_name}_MOC_SRC ${_name}.h)
    add_executable(${_name} ${_source} ${${_name}_MOC_SRC})
    target_link_libraries(${_name} ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} ${QTCORE_QTNETWORK_LIBRARY})
    add_test(${_name}-test ${EXECUTABLE_OUTPUT_PATH}/${_name})
endmacro(add_libmygpo_test)

add_libmygpo_test( UrlBuilderTest.cpp )
target_link_libraries( UrlBuilderTest UrlBuilder)

add_libmygpo_test( RequestHandlerTest.cpp )
target_link_libraries(RequestHandlerTest RequestHandler)

add_libmygpo_test( ApiRequestTest.cpp )
target_link_libraries(ApiRequestTest ${QJSON_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ApiRequest)
