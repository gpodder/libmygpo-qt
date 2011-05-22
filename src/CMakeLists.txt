
include_directories( ${QT_INCLUDES} ${QJSON_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

set ( LIBMYGPO_QT_SRC
        Settings.cpp
        AddRemoveResult.cpp
        Tag.cpp 
        JsonCreator.cpp 
        Podcast.cpp
        Episode.cpp 
        EpisodeAction.cpp
        EpisodeActionList.cpp
        ApiRequest.cpp
        RequestHandler.cpp
        UrlBuilder.cpp
        TagList.cpp
        EpisodeList.cpp
        PodcastList.cpp
        DeviceUpdates.cpp
        DeviceList.cpp
        Device.cpp
)

set ( LIBMYGPO_QT_MOC_H
        Podcast.h
        Podcast_p.h
        PodcastList.h
        PodcastList_p.h
        Episode.h
        Episode_p.h
        EpisodeList.h
        Tag.h
        Tag_p.h
        TagList.h
        Device.h
        Device_p.h
        DeviceList.h
        DeviceList_p.h
        DeviceUpdates.h
        DeviceUpdates_p.h
        EpisodeAction.h
        EpisodeActionList.h
        EpisodeActionList_p.h
        Settings.h
        Settings_p.h
        AddRemoveResult.h
        AddRemoveResult_p.h
)

set ( LIBMYGPO_QT_INSTALL_H
        ApiRequest.h
        mygpo_export.h
        Podcast.h
        PodcastList.h
        Episode.h
        EpisodeList.h
        Tag.h
        TagList.h
        Device.h
        DeviceList.h
        DeviceUpdates.h
        EpisodeAction.h
        EpisodeActionList.h
        Settings.h
        AddRemoveResult.h
)

QT4_WRAP_CPP(LIBMYGPO_QT_MOC_SRC ${LIBMYGPO_QT_MOC_H} )

add_library( mygpo-qt SHARED ${LIBMYGPO_QT_SRC} ${LIBMYGPO_QT_MOC_SRC} )

target_link_libraries( mygpo-qt ${QJSON_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
set_target_properties( mygpo-qt PROPERTIES VERSION ${MYGPO_LIB_VERSION} SOVERSION ${MYGPO_LIB_VERSION_SONAME} DEFINE_SYMBOL MYGPO_MAKEDLL)
install( TARGETS mygpo-qt DESTINATION lib${LIB_SUFFIX} )

install( FILES ${LIBMYGPO_QT_INSTALL_H} DESTINATION  include/mygpo-qt COMPONENT Devel )
