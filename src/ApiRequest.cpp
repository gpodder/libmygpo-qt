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
#include <QLatin1String>

using namespace mygpo;

ApiRequest::ApiRequest(const QString& username, const QString &password, QNetworkAccessManager* nam) : m_requestHandler(username, password, nam)
{
}

ApiRequest::ApiRequest(QNetworkAccessManager* nam) : m_requestHandler(nam)
{
}

QByteArray ApiRequest::toplistOpml(uint count)
{
	QUrl requestUrl = UrlBuilder::getToplistUrl(count, UrlBuilder::OPML);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    return response;
	return NULL;
}

QByteArray ApiRequest::searchOpml(const QString& query)
{
//    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl(query, UrlBuilder::OPML);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    return response;
	return NULL;
}

PodcastList ApiRequest::toplist(uint count)
{
    QUrl requestUrl = UrlBuilder::getToplistUrl(count);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    QList<Podcast> podcastList = JsonParser::toPodcastList(response);
//    //return podcastList;
	QNetworkReply *reply;
	reply = m_requestHandler.getRequest(requestUrl);
	PodcastList podcastList(reply);
    return podcastList;
}

PodcastList ApiRequest::search(const QString& query)
{
    QUrl requestUrl = UrlBuilder::getPodcastSearchUrl(query);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    QList<Podcast> podcastList = JsonParser::toPodcastList(response);
//    // return podcastList;
	QNetworkReply *reply;
	reply = m_requestHandler.getRequest(requestUrl);

	PodcastList podcastList(reply);
    return podcastList;
}

Episode ApiRequest::episodeData(const QUrl& podcasturl, const QUrl& episodeurl)
{
    QUrl requestUrl = UrlBuilder::getEpisodeDataUrl(podcasturl.toString(),episodeurl.toString());
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    Episode episode = JsonParser::toEpisode(response);
//    return episode;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

	Episode episode(reply);
    return episode;
}

EpisodeList ApiRequest::favoriteEpisode(const QString& username)
{
    QUrl requestUrl = UrlBuilder::getFavEpisodesUrl(username);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    QList<Episode> episodeList = JsonParser::toEpisodeList(response);
//    // return episodeList;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

	EpisodeList episodeList(reply);
    return episodeList;
}

Podcast ApiRequest::podcastData(const QUrl& podcasturl)
{
    QUrl requestUrl = UrlBuilder::getPodcastDataUrl(podcasturl.toString());
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    Podcast podcast = JsonParser::toPodcast(response);
//    return podcast;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

	Podcast podcast(reply);
	return podcast;
}

PodcastList ApiRequest::podcastsOfTag(uint count, const QString& tag)
{
    QUrl requestUrl = UrlBuilder::getPodcastsOfTagUrl(tag,count);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    QList<Podcast> podcastList = JsonParser::toPodcastList(response);
//    //return podcastList;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

	PodcastList podcastList(reply);
    return podcastList;
}

TagList ApiRequest::topTags(uint count)
{
    QUrl requestUrl = UrlBuilder::getTopTagsUrl(count);
//    QByteArray response;
//    //int errorFlag = m_requestHandler.getRequest(response, requestUrl);
//    checkErrorFlag(errorFlag);
//
//    QList<Tag> tagList = JsonParser::toTagList(response);
//    //return tagList;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

    TagList tagList(reply);
    return tagList;
}

PodcastList ApiRequest::suggestions(uint count)
{
    QUrl requestUrl = UrlBuilder::getSuggestionsUrl(count);
    /* QByteArray response;
    int errorFlag = m_requestHandler.getRequest(response, requestUrl);
    checkErrorFlag(errorFlag);

    QList<Podcast> podcastList = JsonParser::toPodcastList(response);*/
    //return podcastList;
    QNetworkReply *reply;
    reply = m_requestHandler.getRequest(requestUrl);

	PodcastList podcastList(reply);
    return podcastList;
}

AddRemoveResult ApiRequest::addRemoveSubscriptions(const QString& username, const QString& device,const QList< QUrl >& add, const QList< QUrl >& remove)
{
    QUrl requesturl = UrlBuilder::getAddRemoveSubUrl(username,device);
//
    QByteArray data = JsonParser::addRemoveSubsToJSON(add,remove);
//    QByteArray response;
//    int errorFlag = m_requestHandler.postRequest(response,data,requesturl);
//    checkErrorFlag(errorFlag);
//
//    AddRemoveResult result = JsonParser::toAddRemoveResult(response);
//    return result;
    QNetworkReply *reply;
    reply = m_requestHandler.postRequest(data, requesturl);
	AddRemoveResult addRemoveResult(reply);
	return addRemoveResult;
}

void ApiRequest::checkErrorFlag(QNetworkReply::NetworkError errorFlag)
{
	if (errorFlag != QNetworkReply::NoError) {
		switch (errorFlag) {
		case 3: throw ServerNotFoundException(); break;
		case 201: throw InvalidUserException(); break;
		case 203: throw InvalidDeviceIdException(); break;
		case 204: throw InvalidAuthException(); break;
		default: throw RequestException(QLatin1String("An unknown error occurred while sending the request to the server"), errorFlag); break;
		}
	}
}
