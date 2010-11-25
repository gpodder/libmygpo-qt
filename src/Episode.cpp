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

#include "Episode.h"
#include "JsonParser.h"
#include <parser.h>

using namespace mygpo;

Episode::Episode(const QUrl& url, const QString& title, const QUrl& podcastUrl, const QString& podcastTitle, const QString& description, const QUrl& website, const QUrl& mygpoUrl, QObject* parent): QObject(parent), m_url(url), m_title(title), m_podcastUrl(podcastUrl), m_podcastTitle(podcastTitle), m_description(description), m_website(website), m_mygpoUrl(mygpoUrl), m_error(QNetworkReply::NoError) {
  
}

Episode::Episode(QNetworkReply* reply,QObject* parent) : m_reply(reply), m_error(QNetworkReply::NoError)
{
  QObject::connect(m_reply,SIGNAL(finished()), this, SLOT(parseData()));
    QObject::connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),
		      this,SLOT(error(QNetworkReply::NetworkError)));

}

Episode::~Episode()
{

}

Episode::Episode(const mygpo::Episode& other): QObject(other.parent()), m_url(other.url()), m_title(other.title()), m_podcastUrl(other.podcastUrl()), m_podcastTitle(other.podcastTitle()), m_description(other.description()), m_website(other.website()), m_mygpoUrl(other.mygpoUrl())
{

}

Episode Episode::operator=(const mygpo::Episode& other)
{
    return Episode(other);
}


QUrl Episode::url() const
{
    return m_url;
}

QString Episode::title() const
{
    return m_title;
}

QUrl Episode::podcastUrl() const
{
    return m_podcastUrl;
}

QString Episode::podcastTitle() const
{
    return m_podcastTitle;
}

QString Episode::description() const
{
    return m_description;
}

QUrl Episode::website() const
{
    return m_website;
}

QUrl Episode::mygpoUrl() const
{
    return m_mygpoUrl;
}


void Episode::parse(const QVariant& data) 
{
    QVariantMap episodeMap = data.toMap();
    m_url = episodeMap.value(QLatin1String("url")).toUrl();
    m_title = episodeMap.value(QLatin1String("title")).toString();
    m_podcastUrl = episodeMap.value(QLatin1String("podcast_url")).toUrl();
    m_podcastTitle = episodeMap.value(QLatin1String("podcast_title")).toString();
    m_description = episodeMap.value(QLatin1String("description")).toString();
    m_website = episodeMap.value(QLatin1String("website")).toUrl();
    m_mygpoUrl = episodeMap.value(QLatin1String("mygpo_link")).toUrl();
}

bool Episode::parse(const QByteArray& data)
{	
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      parse( variant );
      return true;
    } else {
      return false;
    }
}

void Episode::parseData() {
    //parsen und signal senden
    QJson::Parser parser;
    if (parse( m_reply->readAll() ) ) { 
      emit finished();
    } else {
      emit parseError();
    }
}

void Episode::error(QNetworkReply::NetworkError error) {
    this->m_error = error;
    emit requestError(error);
}