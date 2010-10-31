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

#ifndef URLBUILDER_H
#define URLBUILDER_H
#include <qt4/QtCore/qurl.h>
#include <qstring.h>

namespace mygpo {
class UrlBuilder
{
  
  public:
    static UrlBuilder& instance();
    QUrl getToplistUrl( short i );
    QUrl getSuggestionsUrl( short i );
    QUrl getPodcastSearchUrl( const QString& query );
    
    
  private:
    UrlBuilder() {};
    UrlBuilder( const UrlBuilder& ) {};
    static UrlBuilder _instance;
    
};
}

#endif // URLBUILDER_H
