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
#include "RequestHandler.h"
#include "JsonParser.h"

using namespace mygpo;


QByteArray ApiRequest::toplistOpml(uint count)
{
    QUrl requestUrl = UrlBuilder::getToplistUrl(count, UrlBuilder::OPML);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    return response;
}

QByteArray ApiRequest::searchOpml(const QString& query)
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl(query, UrlBuilder::OPML);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    return response;
}

QList< Podcast > ApiRequest::toplist(uint count)
{
    QUrl requestUrl = UrlBuilder::getToplistUrl(count);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    QList<Podcast> podcastList = parser.toPodcastList(response);
    return podcastList;
}

QList< Podcast > ApiRequest::search(const QString& query)
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl(query);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    QList<Podcast> podcastList = parser.toPodcastList(response);
    return podcastList;
}

Episode ApiRequest::episodeData(const QUrl& podcasturl, const QUrl& episodeurl)
{
    QUrl requestUrl = UrlBuilder::getEpisodeDataUrl(podcasturl.toString(),episodeurl.toString());
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    Episode episode = parser.toEpisode(response);
    return episode;
}

QList< Episode > ApiRequest::favoriteEpisode(const QString& username)
{
    QUrl requestUrl = UrlBuilder::getFavEpisodesUrl(username);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    QList<Episode> episodeList = parser.toEpisodeList(response);
    return episodeList;
}

Podcast ApiRequest::podcastData(const QUrl& podcasturl)
{
    QUrl requestUrl = UrlBuilder::getPodcastDataUrl(podcasturl.toString());
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    Podcast podcast = parser.toPodcast(response);
    return podcast;
}

QList< Podcast > ApiRequest::podcastsOfTag(uint count, const QString& tag)
{
    QUrl requestUrl = UrlBuilder::getPodcastsOfTagUrl(tag,count);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    QList<Podcast> podcastList = parser.toPodcastList(response);
    return podcastList;
}

QList< Tag > ApiRequest::topTags(uint count)
{
    QUrl requestUrl = UrlBuilder::getTopTagsUrl(count);
    QByteArray response;
    RequestHandler::instance().getRequest(response, requestUrl);
    JsonParser parser;
    QList<Tag> tagList = parser.toTagList(response);
    return tagList;
}
