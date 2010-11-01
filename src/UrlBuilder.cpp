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


using namespace mygpo;

UrlBuilder UrlBuilder::_instance;

UrlBuilder::UrlBuilder(): _server( "http://gpodder.net" ) 
{
}

UrlBuilder& UrlBuilder::instance()
{
  return _instance;
}

QUrl UrlBuilder::getToplistUrl( unsigned short i, Format f )
{
  QString tmp;
  if( i == 0 ) i = 1;
  tmp.setNum( i );
  return QUrl( _server+"/toplist/"+tmp+getFormatExtension( f ), QUrl::TolerantMode );
}


QUrl UrlBuilder::getSuggestionsUrl( unsigned short i, Format f ) 
{
  QString tmp;
  if( i == 0 ) i = 1;
  tmp.setNum( i );
  return QUrl( _server+"/suggestion/"+tmp+getFormatExtension( f ), QUrl::TolerantMode );
}

QUrl UrlBuilder::getPodcastSearchUrl( const QString& query, Format f ) 
{
  return QUrl( _server+"/search"+getFormatExtension( f )+"?q="+query, QUrl::TolerantMode );
}

QString UrlBuilder::getFormatExtension(Format f)
{
  switch( f ) {
    case JSON:
      return QString( ".json" );
      break;
    case OPML:
      return QString( ".opml" );
      break;      
  }
}


