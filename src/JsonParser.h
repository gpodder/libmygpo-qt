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
#include "AddRemoveResult.h"

#include <QList>

namespace mygpo {

class JsonParser
{

public:
    static QList<Podcast> toPodcastList(const QByteArray& jsonData);
    static Podcast toPodcast(const QByteArray& jsonData);
    static QList<Episode> toEpisodeList(const QByteArray& jsonData);
    static Episode toEpisode(const QByteArray& jsonData);
    static QList<Tag> toTagList(const QByteArray& jsonData);
    static AddRemoveResult toAddRemoveResult(const QByteArray& jsonData);
    static QList<QPair<QUrl,QUrl> > toUrlPairList(const QVariant& variantData);
    static QByteArray addRemoveSubsToJSON(const QList<QUrl>& add, const QList<QUrl>& remove);
private:
    static Podcast qvariantToPodcast(const QVariant& variantData);
    static Episode qvariantToEpisode(const QVariant& variantData);
    static Tag qvariantToTag(const QVariant& variantData);
    static QPair<QUrl, QUrl> toUpdatePair(const QVariant& variantData);
    static QVariantList urlListToQVariantList(const QList<QUrl>& urls);
};

}

#endif // JSONPARSER_H
