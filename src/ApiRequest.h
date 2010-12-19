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

#ifndef APIREQUEST_H
#define APIREQUEST_H

#define MYGPO_MAJOR_VERSION 0
#define MYGPO_MINOR_VERSION 2
#define MYGPO_PATCH_VERSION 5

//#include "RequestHandler.h"
#include "mygpo_export.h"
#include "Podcast.h"
#include "Episode.h"
#include "Tag.h"
#include "AddRemoveResult.h"
#include "EpisodeList.h"
#include "PodcastList.h"
#include "TagList.h"
#include "Settings.h"

#include <QByteArray>
#include <QString>

namespace mygpo
{

class ApiRequestPrivate;

/**
 * This Class is the Frontend of libmygpo-qt.
 * Methods from this Class map the Web API of gpodder.net
 * and return the Results of the Requests.
 * Web API Documentation can be found here: http://wiki.gpodder.org/wiki/Web_Services/API_2
 */

class MYGPO_EXPORT ApiRequest
{
public:


    ApiRequest ( const QString& username, const QString& password, QNetworkAccessManager* nam = 0 );
    ApiRequest ( QNetworkAccessManager* nam = 0 );
    ~ApiRequest ( );
    /**
     * Returns the OPML Result for the Simple API Call "Downloading Podcast Toplists"
     * @param count The number of Podcasts that should be returned - will be set to to 100 if > 100 or < 1
     * @return
     *
     */
    QNetworkReply* toplistOpml ( uint count );

    /**
     * Returns the OPML Result for the Simple API Call "Searching for Podcasts"
     * @param query The String you want to search for
     * @return
     *
     */
    QNetworkReply* searchOpml ( const QString& query );

    /**
     * Returns the Result for the Simple API Call "Downloading podcast suggestions"
     * Requires Authentication
     * @param count The maximum number of Podcasts that should be returned - will be set to to 100 if > 100 or < 1
     * @return
     *
     */
    QNetworkReply* suggestionsOpml ( uint count );

    /**
     * Returns the Result for the Simple API Call "Downloading Podcast Toplists"
     * @param count The number of Podcasts that should be returned - will be set to to 100 if > 100 or < 1
     * @return List of Podcast Objects containing the Data from gPodder
     *
     */
    PodcastListPtr toplist ( uint count );

    /**
     * Returns the Result for the Simple API Call "Searching for Podcasts"
     * @param query The String you want to search for
     * @return List of Podcast Objects containing the Data from gPodder
     *
     */
    PodcastListPtr search ( const QString& query );

    /**
     * Returns the Result for the Simple API Call "Downloading podcast suggestions"
     * Requires Authentication
     * @param count The maximum number of Podcasts that should be returned - will be set to to 100 if > 100 or < 1
     * @return List of Podcast Objects containing the Data from gPodder
     *
     */
    PodcastListPtr suggestions ( uint count );

    /**
     * Returns the Result for the Advanced API Call "Retrieving Podcasts of a Tag"
     * @param query The number of Podcasts that should be returned - will be set to to 100 if > 100 or < 1
     * @param tag The Tag for which Podcasts should be retrieved
     * @return List of Podcast Objects containing the Data from gPodder
     *
     */
    PodcastListPtr podcastsOfTag ( uint count, const QString& tag );

    /**
     * Returns the Result for the Advanced API Call "Retrieving Podcast Data"
     * @param podcasturl Url of the Podcast for which Data should be retrieved
     * @return Podcast Object containing the Data from gPodder
     *
     */
    PodcastPtr podcastData ( const QUrl& podcasturl );

    /**
     * Returns the Result for the Advanced API Call "Retrieving Episode Data"
     * @param podcasturl Url of the Podcast that contains the Episode
     * @param episodeurl Url of the Episode Data for which Data should be retrieved
     * @return Episode Object containing the Data from gPodder
     *
     */
    EpisodePtr episodeData ( const QUrl& podcasturl, const QUrl& episodeurl );

    /**
     * Returns the Result for the Advanced API Call "Listing Favorite Episodes"
     * @param username The User whose Favorite Episodes should be retrieved
     * @return List of Episode Objects containing the Data from gPodder
     *
     */
    EpisodeListPtr favoriteEpisodes ( const QString& username );

    /**
     * Returns the Result for the Advanced API Call "Retrieving Top Tags"
     * @param count The number of Tags that should be returned - will be set to to 100 if > 100 or < 1
     * @return List of Tag Objects containing the Data from gPodder
     *
     */
    TagListPtr topTags ( uint count );

    /**
     * Uploads Data & returns the Result for the Advanced API Call "Add/remove subscriptions"
     * Requires Authentication
     * @param username User for which this API Call should be executed
     * @param device gPodder Device for which this API Call should be executed
     * @param add URLs of Podcasts that should be added to the Subscriptions of the User
     * @param remove URLs of Podcasts that should be removed from the Subscriptions of the User
     *
     */
    AddRemoveResultPtr addRemoveSubscriptions ( const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove );
    
    SettingsPtr accountSettings( const QString& username );
    
    SettingsPtr deviceSettings ( const QString& username, const QString& device );
    
    SettingsPtr podcastSettings ( const QString& username, const QString& podcastUrl );
    
    SettingsPtr episodeSettings ( const QString& username, const QString& podcastUrl, const QString& episodeUrl );

private:
    ApiRequestPrivate* const d;

};

}

#endif
