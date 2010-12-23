/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 Stefan Derkits <stefan@derkits.at>                    *
* Copyright (c) 2010 Christian Wagner <christian.wagner86@gmx.at>          *
* Copyright (c) 2010 Felix Winter <ixos01@gmail.com>                       *
*                                                                          *
* This library is free software; you can redistribute it and/or            *
* modify it under the terms of the GNU Lesser General Public               *
* License as published by the Free Software Foundation; either             *
* version 2.1 of the License, or (at your option) any later version.       *
*                                                                          *
* This library is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        *
* Lesser General Public License for more details.                          *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with this library; if not, write to the Free Software      *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 *
* USA                                                                      *
***************************************************************************/


#include "ApiRequest.h"
#include "UrlBuilder.h"
#include "JsonParser.h"
//#include "RequestExceptions.h"
#include "RequestHandler.h"


#include <QDebug>

#include <QLatin1String>

namespace mygpo
{

class ApiRequestPrivate
{
public:
    //Constructors
    ApiRequestPrivate( const QString& username, const QString& password, QNetworkAccessManager* nam );
    ApiRequestPrivate( QNetworkAccessManager* nam);
    //Member Functions
    QNetworkReply* toplistOpml ( uint count );
    QNetworkReply* searchOpml ( const QString& query );
    QNetworkReply* suggestionsOpml ( uint count );
    PodcastListPtr toplist ( uint count );
    PodcastListPtr search ( const QString& query );
    PodcastListPtr suggestions ( uint count );
    PodcastListPtr podcastsOfTag ( uint count, const QString& tag );
    PodcastPtr podcastData ( const QUrl& podcasturl );
    EpisodePtr episodeData ( const QUrl& podcasturl, const QUrl& episodeurl );
    EpisodeListPtr favoriteEpisodes ( const QString& username );
    TagListPtr topTags ( uint count );
    AddRemoveResultPtr addRemoveSubscriptions ( const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove );
    SettingsPtr accountSettings( const QString& username );
    SettingsPtr deviceSettings ( const QString& username, const QString& device );
    SettingsPtr podcastSettings ( const QString& username, const QString& podcastUrl );
    SettingsPtr episodeSettings ( const QString& username, const QString& podcastUrl, const QString& episodeUrl );
    SettingsPtr setAccountSettings ( const QString& username, QMap<QString, QVariant >& set, const QList<QString>& remove);
    SettingsPtr setDeviceSettings ( const QString& username, const QString& device, QMap<QString, QVariant >& set, const QList<QString>& remove);
    SettingsPtr setPodcastSettings ( const QString& username, const QString& podcastUrl, QMap<QString, QVariant >& set, const QList<QString>& remove);
    SettingsPtr setEpisodeSettings ( const QString& username, const QString& podcastUrl, const QString& episodeUrl, QMap<QString, QVariant >& set, const QList<QString>& remove);
    DeviceUpdatesPtr deviceUpdates( const QString& username, const QString& deviceId, qlonglong timestamp );
    QNetworkReply* renameDevice( const QString& username, const QString& deviceId, const QString& caption, ApiRequest::Type type);
    /*DeviceListPtr listDevices( const QString& username );*/
    EpisodeActionListPtr episodeActions(const QString& username);
    EpisodeActionListPtr episodeActionsByPodcast(const QString& username, const QString& podcastUrl);
    EpisodeActionListPtr episodeActionsByDevice(const QString& username, const QString& deviceId);
    EpisodeActionListPtr episodeActionsByTimestamp(const QString& username, const qulonglong since);
    EpisodeActionListPtr episodeActionsByPodcastAndTimestamp(const QString& username, const QString& podcastUrl, const qulonglong since);
    EpisodeActionListPtr episodeActionsByDeviceAndTimestamp(const QString& username, const QString& deviceId, const qulonglong since);
    EpisodeActionListPtr episodeActionsByPodcastAndAggregate(const QString& username, const QString& podcastUrl, const bool aggregated);
    AddRemoveResultPtr uploadEpisodeActions(const QString& username, const QList<EpisodeActionPtr>& episodeActions);
    QNetworkReply* renameDevice( const QString& username, const QString& deviceId, const QString& caption, const QString& type);
private:
    RequestHandler m_requestHandler;
};

}

using namespace mygpo;

ApiRequestPrivate::ApiRequestPrivate(const QString& username, const QString& password, QNetworkAccessManager* nam) : m_requestHandler(username,password,nam)
{

}

ApiRequestPrivate::ApiRequestPrivate(QNetworkAccessManager* nam) : m_requestHandler(nam)
{

}

QNetworkReply* ApiRequestPrivate::toplistOpml ( uint count )
{
    QUrl requestUrl = UrlBuilder::getToplistUrl ( count, UrlBuilder::OPML );
    return m_requestHandler.getRequest ( requestUrl );
}

QNetworkReply* ApiRequestPrivate::searchOpml ( const QString& query )
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl ( query, UrlBuilder::OPML );
    return m_requestHandler.getRequest ( requestUrl );
}


QNetworkReply* ApiRequestPrivate::suggestionsOpml ( uint count )
{
    QUrl requestUrl = UrlBuilder::getSuggestionsUrl ( count , UrlBuilder::OPML );
    return m_requestHandler.getRequest ( requestUrl );
}

PodcastListPtr ApiRequestPrivate::toplist ( uint count )
{
    QUrl requestUrl = UrlBuilder::getToplistUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );
    PodcastListPtr podcastList ( new PodcastList( reply ) );
    return podcastList;
}

PodcastListPtr ApiRequestPrivate::search ( const QString& query )
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl ( query );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastListPtr podcastList (new PodcastList( reply ) );
    return podcastList;
}

EpisodePtr ApiRequestPrivate::episodeData ( const QUrl& podcasturl, const QUrl& episodeurl )
{
    QUrl requestUrl = UrlBuilder::getEpisodeDataUrl ( podcasturl.toString(),episodeurl.toString() );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    EpisodePtr episode ( new Episode( reply ) );
    return episode;
}

EpisodeListPtr ApiRequestPrivate::favoriteEpisodes ( const QString& username )
{
    QUrl requestUrl = UrlBuilder::getFavEpisodesUrl ( username );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );
    EpisodeListPtr episodeList ( new EpisodeList (reply) );
    return episodeList;
}

PodcastPtr ApiRequestPrivate::podcastData ( const QUrl& podcasturl )
{
    QUrl requestUrl = UrlBuilder::getPodcastDataUrl ( podcasturl.toString() );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastPtr podcast ( new Podcast( reply ) );
    return podcast;
}

PodcastListPtr ApiRequestPrivate::podcastsOfTag ( uint count, const QString& tag )
{
    QUrl requestUrl = UrlBuilder::getPodcastsOfTagUrl ( tag,count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastListPtr podcastList ( new PodcastList( reply ) );
    return podcastList;
}

TagListPtr ApiRequestPrivate::topTags ( uint count )
{
    QUrl requestUrl = UrlBuilder::getTopTagsUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    TagListPtr tagList ( new TagList( reply ) );
    return tagList;
}

PodcastListPtr ApiRequestPrivate::suggestions ( uint count )
{
    QUrl requestUrl = UrlBuilder::getSuggestionsUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);
    PodcastListPtr podcastList ( new PodcastList( reply ) );
    return podcastList;
}

AddRemoveResultPtr ApiRequestPrivate::addRemoveSubscriptions ( const QString& username, const QString& device,const QList< QUrl >& add, const QList< QUrl >& remove )
{
    QUrl requesturl = UrlBuilder::getAddRemoveSubUrl ( username,device );
    QByteArray data = JsonParser::addRemoveSubsToJSON ( add,remove );
    //TODO: Check if no URL is contained in both Lists
    QNetworkReply *reply;
    reply = m_requestHandler.postRequest ( data, requesturl );
    AddRemoveResultPtr addRemoveResult(new AddRemoveResult ( reply ));
    return addRemoveResult;
}

SettingsPtr ApiRequestPrivate::accountSettings(const QString& username)
{
    QUrl requesturl = UrlBuilder::getAccountSettingsUrl( username );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest( requesturl );
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::deviceSettings(const QString& username, const QString& device)
{
    QUrl requesturl = UrlBuilder::getDeviceSettingsUrl( username, device );
    qDebug() << requesturl;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest( requesturl );
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::podcastSettings(const QString& username, const QString& podcastUrl)
{
    QUrl requesturl = UrlBuilder::getPodcastSettingsUrl( username, podcastUrl );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest( requesturl );
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::episodeSettings(const QString& username, const QString& podcastUrl, const QString& episodeUrl)
{
    QUrl requesturl = UrlBuilder::getEpisodeSettingsUrl( username, podcastUrl, episodeUrl );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest( requesturl );
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::setAccountSettings(const QString& username, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    QUrl requesturl = UrlBuilder::getAccountSettingsUrl( username );
    QNetworkReply *reply;
    QByteArray postData = JsonParser::saveSettingsToJSON(set,remove);
    reply = m_requestHandler.postRequest(postData,requesturl);
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::setDeviceSettings(const QString& username, const QString& device, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    QUrl requesturl = UrlBuilder::getDeviceSettingsUrl( username, device );
    QNetworkReply *reply;
    QByteArray postData = JsonParser::saveSettingsToJSON(set,remove);
    reply = m_requestHandler.postRequest(postData,requesturl);
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::setPodcastSettings(const QString& username, const QString& podcastUrl, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    QUrl requesturl = UrlBuilder::getPodcastSettingsUrl( username, podcastUrl );
    QNetworkReply *reply;
    QByteArray postData = JsonParser::saveSettingsToJSON(set,remove);
    reply = m_requestHandler.postRequest(postData,requesturl);
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

SettingsPtr ApiRequestPrivate::setEpisodeSettings(const QString& username, const QString& podcastUrl, const QString& episodeUrl, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    QUrl requesturl = UrlBuilder::getEpisodeSettingsUrl( username, podcastUrl, episodeUrl );
    QNetworkReply *reply;
    QByteArray postData = JsonParser::saveSettingsToJSON(set,remove);
    reply = m_requestHandler.postRequest(postData,requesturl);
    SettingsPtr settings(new Settings ( reply ));
    return settings;
}

DeviceUpdatesPtr ApiRequestPrivate::deviceUpdates(const QString& username, const QString& deviceId, qlonglong timestamp)
{
    QUrl requesturl = UrlBuilder::getDeviceUpdatesUrl(username, deviceId, timestamp);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    DeviceUpdatesPtr updates(new DeviceUpdates(reply));
    return updates;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActions(const QString& username)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrl(username);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByPodcast(const QString& username, const QString& podcastUrl)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByPodcast(username, podcastUrl);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByDevice(const QString& username, const QString& deviceId)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByDevice(username, deviceId);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByTimestamp(const QString& username, const qulonglong since)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByTimestamp(username, since);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByPodcastAndTimestamp(const QString& username, const QString& podcastUrl, const qulonglong since)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByPodcastAndTimestamp(username, podcastUrl, since);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByDeviceAndTimestamp(const QString& username, const QString& deviceId, const qulonglong since)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByDeviceAndTimestamp(username, deviceId, since);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

EpisodeActionListPtr ApiRequestPrivate::episodeActionsByPodcastAndAggregate(const QString& username, const QString& podcastUrl, const bool aggregated)
{
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrlByPodcastAndAggregate(username, podcastUrl, aggregated);
    QNetworkReply* reply;
    reply = m_requestHandler.getRequest( requesturl );
    EpisodeActionListPtr episodeActions(new EpisodeActionList(reply));
    return episodeActions;
}

AddRemoveResultPtr ApiRequestPrivate::uploadEpisodeActions(const QString& username, const QList<EpisodeActionPtr>& episodeActions) {
    QUrl requesturl = UrlBuilder::getEpisodeActionsUrl(username);
    QNetworkReply *reply;
    QByteArray postData = JsonParser::episodeActionListToJSON(episodeActions);
    reply = m_requestHandler.postRequest(postData,requesturl);
    AddRemoveResultPtr addRemoveResult(new AddRemoveResult ( reply ));
    return addRemoveResult;
}

QNetworkReply* ApiRequestPrivate::renameDevice(const QString& username , const QString& deviceId ,const QString& caption, ApiRequest::Type type)
{
   QUrl requestUrl = UrlBuilder::getRenameDeviceUrl(username, deviceId);
   QNetworkReply* reply;
   QByteArray data;
   switch (type) {
       case ApiRequest::DESKTOP:
           data = JsonParser::renameDeviceStringToJSON(caption,QLatin1String("desktop"));
           break;
       case ApiRequest::LAPTOP:
           data = JsonParser::renameDeviceStringToJSON(caption,QLatin1String("laptop"));
           break;
       case ApiRequest::MOBILE:
           data = JsonParser::renameDeviceStringToJSON(caption,QLatin1String("mobile"));
           break;
       case ApiRequest::SERVER:
           data = JsonParser::renameDeviceStringToJSON(caption,QLatin1String("server"));
           break;
       case ApiRequest::OTHER:
           data = JsonParser::renameDeviceStringToJSON(caption,QLatin1String("other"));
           break;
   }
   reply = m_requestHandler.postRequest(data, requestUrl);
   return reply;
}

/*DeviceListPtr ApiRequestPrivate::listDevices(const QString& username)
{
    QUrl requestUrl = UrlBuilder::getDeviceListUrl(username);
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest( requestUrl );
    DeviceListPtr list(new DeviceList(reply));
    return list;
}*/


ApiRequest::ApiRequest ( const QString& username, const QString& password, QNetworkAccessManager* nam ) : d(new ApiRequestPrivate( username, password, nam ))
{
}

ApiRequest::ApiRequest ( QNetworkAccessManager* nam ) : d(new ApiRequestPrivate(nam))
{
}

ApiRequest::~ApiRequest()
{
    delete d;
}

QNetworkReply* ApiRequest::toplistOpml(uint count)
{
    return d->toplistOpml(count);
}

QNetworkReply* ApiRequest::searchOpml(const QString& query)
{
    return d->searchOpml(query);
}

QNetworkReply* ApiRequest::suggestionsOpml(uint count)
{
    return d->suggestionsOpml(count);
}

PodcastListPtr ApiRequest::toplist(uint count)
{
    return d->toplist(count);
}

PodcastListPtr ApiRequest::search(const QString& query)
{
    return d->search(query);
}

PodcastListPtr ApiRequest::suggestions(uint count)
{
    return d->suggestions(count);
}

PodcastListPtr ApiRequest::podcastsOfTag(uint count, const QString& tag)
{
    return d->podcastsOfTag(count,tag);
}

PodcastPtr ApiRequest::podcastData(const QUrl& podcasturl)
{
    return d->podcastData(podcasturl);
}

EpisodePtr ApiRequest::episodeData(const QUrl& podcasturl, const QUrl& episodeurl)
{
    return d->episodeData(podcasturl,episodeurl);
}

EpisodeListPtr ApiRequest::favoriteEpisodes(const QString& username)
{
    return d->favoriteEpisodes(username);
}

TagListPtr ApiRequest::topTags(uint count)
{
    return d->topTags(count);
}

AddRemoveResultPtr ApiRequest::addRemoveSubscriptions(const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove)
{
    return d->addRemoveSubscriptions(username,device,add,remove);
}

SettingsPtr ApiRequest::accountSettings(const QString& username)
{
    return d->accountSettings( username );
}

SettingsPtr ApiRequest::deviceSettings(const QString& username, const QString& device)
{
    return d->deviceSettings( username, device );
}

SettingsPtr ApiRequest::podcastSettings(const QString& username, const QString& podcastUrl)
{
    return d->podcastSettings( username, podcastUrl );
}

SettingsPtr ApiRequest::episodeSettings(const QString& username, const QString& podcastUrl, const QString& episodeUrl)
{
    return d->episodeSettings( username, podcastUrl, episodeUrl );
}

SettingsPtr ApiRequest::setAccountSettings(const QString& username, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    return d->setAccountSettings(username,set,remove);
}

SettingsPtr ApiRequest::setDeviceSettings(const QString& username, const QString& device, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    return d->setDeviceSettings(username,device,set,remove);
}

SettingsPtr ApiRequest::setPodcastSettings(const QString& username, const QString& podcastUrl, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    return d->setPodcastSettings(username,podcastUrl,set,remove);
}

SettingsPtr ApiRequest::setEpisodeSettings(const QString& username, const QString& podcastUrl, const QString& episodeUrl, QMap<QString, QVariant >& set, const QList< QString >& remove)
{
    return d->setEpisodeSettings(username,podcastUrl,episodeUrl,set,remove);
}

DeviceUpdatesPtr ApiRequest::deviceUpdates(const QString& username, const QString& deviceId, qlonglong timestamp)
{
    return d->deviceUpdates(username, deviceId, timestamp);
}

EpisodeActionListPtr ApiRequest::episodeActions(const QString& username)
{
	return d->episodeActions(username);
}

EpisodeActionListPtr ApiRequest::episodeActionsByPodcast(const QString& username, const QString& podcastUrl)
{
	return d->episodeActionsByDevice(username, podcastUrl);
}

EpisodeActionListPtr ApiRequest::episodeActionsByDevice(const QString& username, const QString& deviceId)
{
	return d->episodeActionsByDevice(username, deviceId);
}

EpisodeActionListPtr ApiRequest::episodeActionsByTimestamp(const QString& username, const qulonglong since)
{
	return d->episodeActionsByTimestamp(username, since);
}

EpisodeActionListPtr ApiRequest::episodeActionsByPodcastAndTimestamp(const QString& username, const QString& podcastUrl, const qulonglong since)
{
	return d->episodeActionsByPodcastAndTimestamp(username, podcastUrl, since);
}

EpisodeActionListPtr ApiRequest::episodeActionsByDeviceAndTimestamp(const QString& username, const QString& deviceId, const qulonglong since)
{
	return d->episodeActionsByDeviceAndTimestamp(username, deviceId, since);
}

EpisodeActionListPtr ApiRequest::episodeActionsByPodcastAndAggregate(const QString& username, const QString& podcastUrl, const bool aggregated)
{
	return d->episodeActionsByPodcastAndAggregate(username, podcastUrl, aggregated);
}

AddRemoveResultPtr ApiRequest::uploadEpisodeActions(const QString& username, const QList<EpisodeActionPtr>& episodeActions) {
	return d->uploadEpisodeActions(username, episodeActions);
}

QNetworkReply* ApiRequest::renameDevice(const QString& username , const QString& deviceId, const QString& caption, ApiRequest::Type type)
{
   return d->renameDevice(username, deviceId, caption, type);
}

/*DeviceListPtr ApiRequest::listDevices(const QString& username)
{
    return d->listDevices(username);
}*/
