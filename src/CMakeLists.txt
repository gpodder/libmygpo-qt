
include_directories( ${QJSON_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

set ( LIBMYGPO_QT_SRC
        Settings.cpp
        AddRemoveResult.cpp
        Tag.cpp 
        JsonParser.cpp 
        Podcast.cpp
        Episode.cpp 
        EpisodeAction.cpp
        EpisodeActionList.cpp
        ApiRequest.cpp
        RequestHandler.cpp
        UrlBuilder.cpp
        RequestExceptions.cpp
        TagList.cpp
        EpisodeList.cpp
        PodcastList.cpp
        DeviceUpdates.cpp
#        DeviceList.cpp
)

set ( LIBMYGPO_QT_H
        Settings.h
        AddRemoveResult.h
        JsonParser.h
        mygpo.h
        mygpo_export.h
        Podcast.h
        Episode.h
        EpisodeAction.h
        EpisodeActionList.h
        Tag.h
        ApiRequest.h
        RequestHandler.h
        UrlBuilder.h
        RequestExceptions.h
        TagList.h
        EpisodeList.h
        PodcastList.h
        DeviceUpdates.h
#        DeviceList.h
)

QT4_WRAP_CPP(LIBMYGPO_QT_MOC_SRC ${LIBMYGPO_QT_H} )

QT4_GENERATE_MOC(PodcastList.cpp PodcastList.moc)
QT4_GENERATE_MOC(EpisodeList.cpp EpisodeList.moc)
QT4_GENERATE_MOC(Episode.cpp Episode.moc)
QT4_GENERATE_MOC(EpisodeAction.cpp EpisodeAction.moc)
QT4_GENERATE_MOC(EpisodeActionList.cpp EpisodeActionList.moc)
QT4_GENERATE_MOC(Podcast.cpp Podcast.moc)
QT4_GENERATE_MOC(AddRemoveResult.cpp AddRemoveResult.moc)
QT4_GENERATE_MOC(TagList.cpp TagList.moc)
QT4_GENERATE_MOC(Tag.cpp Tag.moc)
QT4_GENERATE_MOC(Settings.cpp Settings.moc)
QT4_GENERATE_MOC(DeviceUpdates.cpp DeviceUpdates.moc)
#QT4_GENERATE_MOC(DeviceList.cpp DeviceList.moc)

add_definitions( -Werror )

add_library( mygpo-qt SHARED ${LIBMYGPO_QT_SRC} ${LIBMYGPO_QT_MOC_SRC} PodcastList.moc EpisodeList.moc Episode.moc EpisodeAction.moc EpisodeActionList.moc Podcast.moc AddRemoveResult.moc TagList.moc Tag.moc Settings.moc DeviceUpdates.moc)
#DeviceList.moc)

target_link_libraries( mygpo-qt ${QJSON_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )
set_target_properties( mygpo-qt PROPERTIES VERSION ${MYGPO_LIB_VERSION} SOVERSION ${MYGPO_LIB_VERSION_SONAME} DEFINE_SYMBOL MYGPO_MAKEDLL)
install( TARGETS mygpo-qt DESTINATION lib${LIB_SUFFIX} )

install( FILES ${LIBMYGPO_QT_H} DESTINATION  include/mygpo-qt COMPONENT Devel )
