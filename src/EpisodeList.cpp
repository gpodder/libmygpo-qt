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

#include "EpisodeList.h"

using namespace mygpo;

EpisodeList::EpisodeList(QNetworkReply* reply, QObject* parent) : QObject(parent), m_reply(reply) {

}

EpisodeList::EpisodeList(const EpisodeList& other): QObject(other.parent()), m_reply(other.m_reply), m_episodes(other.m_episodes) {
	QObject::connect(m_reply,SIGNAL(finished()), this, SLOT(parseData()));
	QObject::connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),
			this,SLOT(error(QNetworkReply::NetworkError)));
}

EpisodeList::~EpisodeList() {
}

QList<Episode> EpisodeList::episodes() const {
	return QList<Episode>();
}

QVariant EpisodeList::episodesVar() const {
	return m_episodes;
}

bool EpisodeList::parse(const QVariant& data) {
//    QVariantMap episodeMap = data.toMap();
//    m_url = episodeMap.value(QLatin1String("url")).toUrl();
//    m_title = episodeMap.value(QLatin1String("title")).toString();
//    m_podcastUrl = episodeMap.value(QLatin1String("podcast_url")).toUrl();
//    m_podcastTitle = episodeMap.value(QLatin1String("podcast_title")).toString();
//    m_description = episodeMap.value(QLatin1String("description")).toString();
//    m_website = episodeMap.value(QLatin1String("website")).toUrl();
//    m_mygpoUrl = episodeMap.value(QLatin1String("mygpo_link")).toUrl();
	return false;
}


bool EpisodeList::parse(const QByteArray& data)
{
//    QJson::Parser parser;
//    bool ok;
//    QVariant variant = parser.parse( data, &ok );
//    if( ok ) {
//      parse( variant );
//      return true;
//    } else {
//      return false;
//    }
	return false;
}

void EpisodeList::parseData() {

}

void EpisodeList::error(QNetworkReply::NetworkError error) {

}
