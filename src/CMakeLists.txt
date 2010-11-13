
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/extra/qjson/src )

set ( LIBMYGPO_QT_SRC
        AddRemoveResult.cpp
        Tag.cpp 
        JsonParser.cpp 
        Podcast.cpp
        Episode.cpp 
        ApiRequest.cpp
        RequestHandler.cpp
        UrlBuilder.cpp
)

set ( LIBMYGPO_QT_H
        AddRemoveResult.h
        JsonParser.h
        mygpo.h
        mygpo_export.h
        Podcast.h
        Episode.h
        Tag.h
        ApiRequest.h
        RequestHandler.h
        UrlBuilder.h
)

QT4_WRAP_CPP(LIBMYGPO_QT_MOC_SRC ${LIBMYGPO_QT_H} )

add_definitions( -Werror )

add_library( mygpo-qt SHARED ${LIBMYGPO_QT_SRC} ${LIBMYGPO_QT_MOC_SRC})
target_link_libraries( mygpo-qt qjson ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
set_target_properties( mygpo-qt PROPERTIES VERSION ${MYGPO_LIB_VERSION} SOVERSION ${MYGPO_LIB_VERSION_SONAME} DEFINE_SYMBOL MYGPO_MAKEDLL)
install( TARGETS mygpo-qt DESTINATION lib${LIB_SUFFIX} )

install( FILES ${LIBMYGPO_QT_H} DESTINATION  include/mygpo-qt COMPONENT Devel )
