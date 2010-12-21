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


#include "UrlBuilder.h"
#include "QString"

#include <QLatin1String>


using namespace mygpo;

const QString UrlBuilder::s_server = QLatin1String( "http://gpodder.net" );
const QString UrlBuilder::s_api2 = QLatin1String( "/api/2" );
const QString UrlBuilder::s_api1 = QLatin1String( "/api/1" );


QUrl UrlBuilder::getToplistUrl( uint i, Format f )
{
    QString tmp = QString::number( (i==0) ? 1 : i );
    return QUrl( UrlBuilder::s_server+QLatin1String( "/toplist/" )+tmp+UrlBuilder::getFormatExtension( f ), QUrl::TolerantMode );
}


QUrl UrlBuilder::getSuggestionsUrl( uint i, Format f )
{
    QString tmp = QString::number( (i==0) ? 1 : i );
    return QUrl( s_server+QLatin1String( "/suggestions/" )+tmp+getFormatExtension( f ), QUrl::TolerantMode );
}

QUrl UrlBuilder::getPodcastSearchUrl( const QString& query, Format f )
{
    return QUrl( s_server+QLatin1String( "/search" )+getFormatExtension( f )+QLatin1String("?q=")+query, QUrl::TolerantMode );
}

QUrl UrlBuilder::getTopTagsUrl( uint i )
{
    QString tmp = QString::number( (i==0) ? 1 : i );
    return QUrl( s_server+s_api2+QLatin1String( "/tags/" )+tmp+QLatin1String( ".json" ), QUrl::TolerantMode );
}

QUrl UrlBuilder::getPodcastsOfTagUrl( const QString& tag, uint i )
{
    QString tmp = QString::number( (i==0) ? 1 : i );
    return QUrl( s_server+s_api2+QLatin1String( "/tag/" )+tag+QLatin1String( "/" )+tmp+QLatin1String( ".json" ) );
}

QUrl UrlBuilder::getPodcastDataUrl(const QString& url )
{
    return QUrl( s_server+s_api2+QLatin1String( "/data/podcast" )+QLatin1String( ".json" )+QLatin1String( "?url=" )+url );
}

QUrl UrlBuilder::getEpisodeDataUrl( const QString& podcastUrl, const QString& episodeUrl )
{
    return QUrl( s_server+s_api2+QLatin1String( "/data/episode" )+QLatin1String( ".json" )+
                 QLatin1String( "?podcast=" )+podcastUrl+QLatin1String( "&url=" )+episodeUrl);
}

QUrl UrlBuilder::getFavEpisodesUrl( const QString& username )
{
    return QUrl( s_server+s_api2+QLatin1String( "/favorites/" )+username+QLatin1String( ".json" ) );
}


QUrl UrlBuilder::getAddRemoveSubUrl( const QString& username, const QString& deviceId )
{
    return QUrl( s_server+s_api1+QLatin1String( "/subscriptions/" )+username+QLatin1String( "/" )+deviceId+QLatin1String( ".json" ) );
}

QUrl UrlBuilder::getAccountSettingsUrl( const QString& username )
{
    return QUrl(s_server+s_api2+QLatin1String( "/settings/" )+username+QLatin1String("/account")+QLatin1String( ".json" ) );
}

QUrl UrlBuilder::getDeviceSettingsUrl( const QString& username, const QString& deviceId)
{
    return QUrl(s_server+s_api2+QLatin1String( "/settings/" )+username+QLatin1String("/device")+QLatin1String( ".json" )+QLatin1String("?id=")+deviceId);
}

QUrl UrlBuilder::getPodcastSettingsUrl( const QString& username, const QString& podcastUrl)
{
    return QUrl(s_server+s_api2+QLatin1String( "/settings/" )+username+QLatin1String("/podcast")+QLatin1String( ".json" )+QLatin1String("?podcast=")+podcastUrl);
}

QUrl UrlBuilder::getEpisodeSettingsUrl( const QString& username, const QString& podcastUrl, const QString& episodeUrl)
{
    return QUrl(s_server+s_api2+QLatin1String( "/settings/" )+username+QLatin1String("/episode")+QLatin1String( ".json" )+QLatin1String("?podcast=")+podcastUrl+QLatin1String("&episode=")+episodeUrl);
}

QUrl UrlBuilder::getDeviceListUrl ( const QString& username )
{
    return QUrl(s_server+s_api2+QLatin1String( "/devices/" )+username+QLatin1String( ".json" ) );
}

QUrl UrlBuilder::getDeviceUpdatesUrl ( const QString& username, const QString& deviceId, qulonglong timestamp )
{
    QString tmp = QString::number(timestamp < 0 ? 0 : timestamp);
    return QUrl(s_server+s_api2+QLatin1String( "/updates/" )+username+QLatin1String("/")+deviceId+QLatin1String( ".json?since=" )+tmp);
}

QUrl UrlBuilder::getRenameDeviceUrl ( const QString& username, const QString& deviceId )
{
    return QUrl(s_server+s_api2+QLatin1String( "/devices/" )+username+QLatin1String("/")+deviceId+QLatin1String(".json"));
}

QUrl UrlBuilder::getEpisodeActionsUrl(const QString& username)
{
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json"));
}

QUrl UrlBuilder::getEpisodeActionsUrlByPodcast(const QString& username, const QString& podcastUrl)
{
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?podcast=")+podcastUrl);
}

QUrl UrlBuilder::getEpisodeActionsUrlByDevice(const QString& username, const QString& deviceId)
{
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?device=")+deviceId);
}

QUrl UrlBuilder::getEpisodeActionsUrlByTimestamp(const QString& username, const qulonglong since)
{
	QString tmp = QString::number(since);
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?since=")+tmp);
}

QUrl UrlBuilder::getEpisodeActionsUrlByPodcastAndTimestamp(const QString& username, const QString& podcastUrl, const qulonglong since)
{
	QString tmp = QString::number(since);
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?podcast=")+podcastUrl+QLatin1String("&since=")+tmp);
}

QUrl UrlBuilder::getEpisodeActionsUrlByDeviceAndTimestamp(const QString& username, const QString& deviceId, const qulonglong since)
{
	QString tmp = QString::number(since);
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?device=")+deviceId+QLatin1String("&since=")+tmp);
}

QUrl UrlBuilder::getEpisodeActionsUrlByPodcastAndAggregate(const QString& username, const QString& deviceId, const bool aggregated)
{
	QString agg;
	if (aggregated)
		agg = QLatin1String("true");
	else
		agg = QLatin1String("false");

	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json?podcast=")+deviceId+QLatin1String("&aggregated=")+agg);
}

QUrl UrlBuilder::getUploadEpisodeActionsUrl(const QString& username)
{
	return QUrl(s_server+s_api2+QLatin1String( "/episodes/" )+username+QLatin1String(".json"));
}

QString UrlBuilder::getFormatExtension(Format f)
{
    QString ret;
    switch ( f ) {
    case JSON:
        ret = QString( QLatin1String( ".json" ) );
        break;
    case OPML:
        ret = QString( QLatin1String( ".opml" ) );
        break;
    case TEXT:
        ret = QString( QLatin1String( ".txt" ) );
        break;
    }
    return ret;
}
