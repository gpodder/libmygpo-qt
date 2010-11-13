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

#include <QLatin1String>


using namespace mygpo;

const QString UrlBuilder::_server = QLatin1String( "http://gpodder.net" );
const QString UrlBuilder::_api2 = QLatin1String( "/api/2" );
const QString UrlBuilder::_api1 = QLatin1String( "/api/1" );


QUrl UrlBuilder::getToplistUrl( unsigned int i, Format f )
{
  QString tmp = QString::number( (i==0) ? 1 : i );
  return QUrl( UrlBuilder::_server+QLatin1String( "/toplist/" )+tmp+UrlBuilder::getFormatExtension( f ), QUrl::TolerantMode );
}


QUrl UrlBuilder::getSuggestionsUrl( unsigned int i, Format f ) 
{
  QString tmp = QString::number( (i==0) ? 1 : i );
  return QUrl( _server+QLatin1String( "/suggestion/" )+tmp+getFormatExtension( f ), QUrl::TolerantMode );
}

QUrl UrlBuilder::getPodcastSearchUrl( const QString& query, Format f ) 
{
  return QUrl( _server+QLatin1String( "/search" )+getFormatExtension( f )+QLatin1String("?q=")+query, QUrl::TolerantMode );
}

QUrl UrlBuilder::getTopTagsUrl( unsigned int i, Format f )
{
  QString tmp = QString::number( (i==0) ? 1 : i );
  return QUrl( _server+_api2+QLatin1String( "/tags/" )+tmp+getFormatExtension( f ), QUrl::TolerantMode );
}

QUrl UrlBuilder::getPodcastsOfTagUrl( const QString& tag, unsigned int i, Format f ) 
{
  QString tmp = QString::number( (i==0) ? 1 : i );
  return QUrl( _server+_api2+QLatin1String( "/tag/" )+tag+QLatin1String( "/" )+tmp+getFormatExtension( f ) );
}

QUrl UrlBuilder::getPodcastDataUrl(const QString& url, Format f)
{
  return QUrl( _server+_api2+QLatin1String( "/data/podcast" )+getFormatExtension( f )+QLatin1String( "?url=" )+url );
}

QUrl UrlBuilder::getEpisodeDataUrl( const QString& podcastUrl, const QString& episodeUrl, Format f ) 
{
  return QUrl( _server+_api2+QLatin1String( "/data/episode" )+getFormatExtension( f )+
	 QLatin1String( "?podcast=" )+podcastUrl+QLatin1String( "&url=" )+episodeUrl);
}

QUrl UrlBuilder::getFavEpisodesUrl( const QString& username, Format f)
{
  return QUrl( _server+_api2+QLatin1String( "/favorites/" )+username+getFormatExtension( f ) );
}


QUrl UrlBuilder::getAddRemoveSubUrl( const QString& username, const QString& deviceId, Format f )
{
  return QUrl( _server+_api1+QLatin1String( "/subscriptions/" )+username+QLatin1String( "/" )+deviceId+getFormatExtension( f ) );
}

QString UrlBuilder::getFormatExtension(Format f)
{
  switch( f ) {
    case JSON:
      return QString( QLatin1String( ".json" ) );
      break;
    case OPML:
      return QString( QLatin1String( ".opml" ) );
      break;      
  }
}
