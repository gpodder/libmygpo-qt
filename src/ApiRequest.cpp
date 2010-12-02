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
#include "RequestExceptions.h"
#include "RequestHandler.h"
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
    PodcastList toplist ( uint count );
    PodcastList search ( const QString& query );
    PodcastList suggestions ( uint count );
    PodcastList podcastsOfTag ( uint count, const QString& tag );
    Podcast podcastData ( const QUrl& podcasturl );
    Episode episodeData ( const QUrl& podcasturl, const QUrl& episodeurl );
    EpisodeList favoriteEpisodes ( const QString& username );
    TagList topTags ( uint count );
    AddRemoveResult addRemoveSubscriptions ( const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove );
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

PodcastList ApiRequestPrivate::toplist ( uint count )
{
    QUrl requestUrl = UrlBuilder::getToplistUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );
    PodcastList podcastList ( reply );
    return podcastList;
}

PodcastList ApiRequestPrivate::search ( const QString& query )
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl ( query );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastList podcastList ( reply );
    return podcastList;
}

Episode ApiRequestPrivate::episodeData ( const QUrl& podcasturl, const QUrl& episodeurl )
{
    QUrl requestUrl = UrlBuilder::getEpisodeDataUrl ( podcasturl.toString(),episodeurl.toString() );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    Episode episode ( reply );
    return episode;
}

EpisodeList ApiRequestPrivate::favoriteEpisodes ( const QString& username )
{
    QUrl requestUrl = UrlBuilder::getFavEpisodesUrl ( username );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );
    EpisodeList episodeList ( reply );
    return episodeList;
}

Podcast ApiRequestPrivate::podcastData ( const QUrl& podcasturl )
{
    QUrl requestUrl = UrlBuilder::getPodcastDataUrl ( podcasturl.toString() );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    Podcast podcast ( reply );
    return podcast;
}

PodcastList ApiRequestPrivate::podcastsOfTag ( uint count, const QString& tag )
{
    QUrl requestUrl = UrlBuilder::getPodcastsOfTagUrl ( tag,count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastList podcastList ( reply );
    return podcastList;
}

TagList ApiRequestPrivate::topTags ( uint count )
{
    QUrl requestUrl = UrlBuilder::getTopTagsUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    TagList tagList ( reply );
    return tagList;
}

PodcastList ApiRequestPrivate::suggestions ( uint count )
{
    QUrl requestUrl = UrlBuilder::getSuggestionsUrl ( count );
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest ( requestUrl );

    PodcastList podcastList ( reply );
    return podcastList;
}

AddRemoveResult ApiRequestPrivate::addRemoveSubscriptions ( const QString& username, const QString& device,const QList< QUrl >& add, const QList< QUrl >& remove )
{
    foreach (QUrl url,add)
    {
        remove.removeAll(url);
            
    }
    QUrl requesturl = UrlBuilder::getAddRemoveSubUrl ( username,device );
    QByteArray data = JsonParser::addRemoveSubsToJSON ( add,remove );
    //TODO: Check if no URL is contained in both Lists
    QNetworkReply *reply;
    reply = m_requestHandler.postRequest ( data, requesturl );
    AddRemoveResult addRemoveResult ( reply );
    return addRemoveResult;
}


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

PodcastList ApiRequest::toplist(uint count)
{
    return d->toplist(count);
}

PodcastList ApiRequest::search(const QString& query)
{
    return d->search(query);
}

PodcastList ApiRequest::suggestions(uint count)
{
    return d->suggestions(count);
}

PodcastList ApiRequest::podcastsOfTag(uint count, const QString& tag)
{
    return d->podcastsOfTag(count,tag);
}

Podcast ApiRequest::podcastData(const QUrl& podcasturl)
{
    return d->podcastData(podcasturl);
}

Episode ApiRequest::episodeData(const QUrl& podcasturl, const QUrl& episodeurl)
{
    return d->episodeData(podcasturl,episodeurl);
}

EpisodeList ApiRequest::favoriteEpisodes(const QString& username)
{
    return d->favoriteEpisodes(username);
}

TagList ApiRequest::topTags(uint count)
{
    return d->topTags(count);
}

AddRemoveResult ApiRequest::addRemoveSubscriptions(const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove)
{
    return d->addRemoveSubscriptions(username,device,add,remove);
}
