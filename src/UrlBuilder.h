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
    * @param i Any value between 1..100. If i <= 0 it will be set to 1.
    * @return Request URL to retrieve a list of the top 'i' podcasts.
    */
    QUrl getToplistUrl( unsigned int i, Format f = JSON );
    
    /**
     * @param i Any value between 1..100. If i <= 0 it will be set to 1.
     * @return Rquest URL to retrieve 'i' podcast suggestions.
     */
    QUrl getSuggestionsUrl( unsigned int i, Format f = JSON );
    
    /**
     * @param query The query to search in the podcasts name/descrption.
     * @return Request URL to retrieve podcasts related to the query.
     */
    QUrl getPodcastSearchUrl( const QString& query, Format f = JSON );
    
    /**
     * @param i Amount of tags. If i == 0 it will be set to 1.
     * @return Request URL to retrieve the 'i' most used tags.
     */
    QUrl getTopTagsUrl( unsigned int i, Format f = JSON );
    
    /**
     * @param i Amount of podcasts. If i == 0 it will be set to 1.
     * @return Request URL to retrieve the 'i' most-subscribed podcats that are tagged with tag.
     */
    QUrl getPodcastsOfTagUrl( const QString& tag, unsigned int i, Format f = JSON );
    
    /**
     * @param url The URL of the podcast
     * @return Request URL to retrieve information about the podcast with the given url.
     */
    QUrl getPodcastDataUrl( const QString& url, Format f = JSON );
    
    /**
     * @param podcastUrl URL of the podcast
     * @param episodeUrl URL of the episode that belongs to the podcast-url
     * @return Request URL to retrieve information about the episode with the given episode-url.
     */
    QUrl getEpisodeDataUrl( const QString& podcastUrl, const QString& episodeUrl, Format f = JSON );
    
    /**
     * @param username User name (gpodder.net). You need to be logged in with username.
     * @return Request URL to retrieve a list of all favorite episodes.
     */
    QUrl getFavEpisodesUrl( const QString& username, Format f = JSON );
    
    /**
     * @param username User name (gpodder.net). You need to be logged in with username.
     * @param deviceId The id of the device.
     * @return Request URL to to update the subscription list for a given device.
     */
    QUrl getAddRemoveSubUrl( const QString& username, const QString& deviceId, Format f = JSON );
    
  private:
    UrlBuilder();
    UrlBuilder( const UrlBuilder& ) {};
    static UrlBuilder _instance;
    const QString _server;
    const QString _api2;
    const QString _api1;
    QString getFormatExtension( Format f ) ;
    
};
}

#endif // URLBUILDER_H
