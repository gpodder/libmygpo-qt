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

#include <qurl.h>
#include <qstring.h>

namespace mygpo {
  /**
  * Helper class to generate request URL's.
  * Helps to generate URL's for the gpodder requests.
  * This class uses the singleton pattern, to retrieve a
  * reference to the singleton object use the function instance().
  */
  
class UrlBuilder
{
  
  public: 
    
    enum Format {
      JSON,
      OPML
    };
    
    static UrlBuilder& instance();
    /**
    * @param i Any value between 1..100. If it's out of range it wil be set to 1 or 100.
    * @return Request URL to retrieve a list of the top 'i' podcasts.
    */
    QUrl getToplistUrl(int i, Format f = JSON );
    /**
     * @param i Any value between 1..100. If it's out of range it wil be set to 1 or 100.
     * @return Rquest URL to retrieve 'i' podcast suggestions.
     */
    QUrl getSuggestionsUrl( int i, Format f = JSON );
    /**
     * @param query The query to search in the podcasts name/descrption.
     * @return Request URL to retrieve podcasts related to the query.
     */
    QUrl getPodcastSearchUrl( const QString& query, Format f = JSON );
    
    
  private:
    UrlBuilder();
    UrlBuilder( const UrlBuilder& ) {};
    static UrlBuilder _instance;
    const QString _server;
    QString getFormatExtension( Format f) ;
    
};
}

#endif // URLBUILDER_H
