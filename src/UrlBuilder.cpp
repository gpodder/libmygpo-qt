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

UrlBuilder& UrlBuilder::instance()
{
  return _instance;
}

QUrl UrlBuilder::getToplistUrl( short i )
{
  QString tmp;
  if( i < 1 ) {
    i = 1;
  } else if ( i > 100 ) {
    i = 100;
  }
  tmp.setNum( i );
  return QUrl( "http://gpodder.net/toplist/"+tmp+".json" );
}


QUrl UrlBuilder::getSuggestionsUrl( short i ) {
  QString tmp;
  QUrl u;
  if( i < 1 ) {
    i = 1;
  } else if ( i > 100 ) {
    i = 100;
  }
  tmp.setNum( i );
  return QUrl( "http://gpodder.net/suggesstion/"+tmp+".json" );
}

QUrl UrlBuilder::getPodcastSearchUrl( const QString& query ) {
  return QUrl( "http://gpodder.net/search.json?q="+query+".json" );
}


