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

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "Podcast.h"
#include "Episode.h"
#include "Tag.h"

#include <QList>

namespace mygpo {

class JsonParser
{

public:
    JsonParser();
    virtual ~JsonParser();
    QList<Podcast> toPodcastList(const QByteArray& jsonData);
    Podcast toPodcast(const QByteArray& jsonData);
    QList<Episode> toEpisodeList(const QByteArray& jsonData);
    Episode toEpisode(const QByteArray& jsonData);
    QList<Tag> toTagList(const QByteArray& jsonData);
private:
    Podcast qvariantToPodcast(QVariant& variantData);
    Episode qvariantToEpisode(QVariant& variantData);
    Tag qvariantToTag(QVariant& variantData);
};

}

#endif // JSONPARSER_H
