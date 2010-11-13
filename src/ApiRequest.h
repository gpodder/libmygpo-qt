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
#define MYGPO_PATCH_VERSION 0

#include "RequestHandler.h"
#include "mygpo_export.h"
#include "Podcast.h"
#include "Episode.h"
#include "Tag.h"
#include "AddRemoveResult.h"


#include <QByteArray>


namespace mygpo
{
  
    /**
     * This Class is the Frontend of libmygpo-qt.
     * Methods from this Class map the Web API of gpodder.net
     * and return the Results of the Requests.
     */

class MYGPO_EXPORT ApiRequest
{
public:
    
  
    ApiRequest(const QString& username, const QString& password);
    ApiRequest() {};
    /**
     * Returns the OPML Result for the Simple API Call "Downloading Podcast Toplists"
     * @param count The number of Podcasts that should be returned - will be set to 1 if < 1 and to 100 if > 100 
     * @return QByteArray containing the OPM Data
     */
    QByteArray toplistOpml(uint count);
    
    /**
     * Returns the OPML Result for the Simple API Call "Searching for Podcasts"
     * @param query The String you want to search for
     * @return QByteArray containing the OPM Data
     */
    QByteArray searchOpml(const QString& query);
    
    //still missing for v0.2: Add/Remove Subscriptions
    
    QList<Podcast> toplist(uint count);
    
    QList<Podcast> search(const QString& query);
    
    QList<Podcast> suggestions(uint count);
    
    QList<Podcast> podcastsOfTag(uint count, const QString& tag);
    
    Podcast podcastData(const QUrl& podcasturl);
    
    Episode episodeData(const QUrl& podcasturl, const QUrl& episodeurl);
    
    QList<Episode> favoriteEpisode(const QString& username);
    
    QList<Tag> topTags(uint count);
    
    AddRemoveResult addRemoveSubscriptions(const QString& username, const QString& device, const QList< QUrl >& add, const QList< QUrl >& remove);
    
private:
    
    RequestHandler requestHandler;
    
};

}

#endif
