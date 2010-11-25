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


#include "Podcast.h"
#include <parser.h>

using namespace mygpo;

Podcast::Podcast(const QUrl& url, const QString& title, const QString& description, int subscribers, const QUrl& logoUrl, const QUrl& website, const QUrl& mygpolink, QObject* parent) : m_url(url), m_title(title), m_description(description), m_subscribers(subscribers), m_logoUrl(logoUrl), m_website(website), m_mygpoUrl(mygpolink)
{

}

Podcast::Podcast()
{

}


Podcast::Podcast(QNetworkReply* reply, QObject* parent) : m_error(QNetworkReply::NoError), m_reply(reply)
{
    QObject::connect(reply,SIGNAL(finished()), this, SLOT(parseData()));
    QObject::connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
		      this,SLOT(error(QNetworkReply::NetworkError)));
}

Podcast::Podcast(const Podcast& other): QObject(other.parent()), m_url(other.url()), m_title(other.title()), m_description(other.description()), m_subscribers(other.subscribers()), m_logoUrl(other.logoUrl()), m_website(other.website()), m_mygpoUrl(other.mygpoUrl())
{

}

Podcast::~Podcast()
{

}

Podcast Podcast::Podcast::operator=(const mygpo::Podcast& other)
{
    return Podcast(other);
}


QUrl Podcast::url() const
{
    return m_url;
}

QString Podcast::title() const
{
    return m_title;
}

QString Podcast::description() const
{
    return m_description;
}

uint Podcast::subscribers() const
{
    return m_subscribers;
}

QUrl Podcast::logoUrl() const
{
    return m_logoUrl;
}

QUrl Podcast::website() const
{
    return m_website;
}

QUrl Podcast::mygpoUrl() const
{
    return m_mygpoUrl;
}

bool Podcast::parse(const QVariant& data) 
{
    if(!data.canConvert(QVariant::Map))
      return false;
    QVariantMap podcastMap = data.toMap();
    QVariant v = podcastMap.value(QLatin1String("url"));
    if(!v.canConvert(QVariant::Url))
      return false;
    m_url = podcastMap.value(QLatin1String("url")).toUrl();
    v = podcastMap.value(QLatin1String("title"));
    if(!v.canConvert(QVariant::String)) 
      return false;
    m_title = podcastMap.value(QLatin1String("title")).toString();
    v = podcastMap.value(QLatin1String("title"));
    if(!v.canConvert(QVariant::String))
      return false;
    m_description = podcastMap.value(QLatin1String("description")).toString();
    v = podcastMap.value(QLatin1String("subscribers"));
    if(!v.canConvert(QVariant::Int))
      return false;
    m_subscribers = podcastMap.value(QLatin1String("subscribers")).toUInt();
    v = podcastMap.value(QLatin1String("logo_url"));
    if(!v.canConvert(QVariant::Url))
      return false;
    m_logoUrl = podcastMap.value(QLatin1String("logo_url")).toUrl();
    v = podcastMap.value(QLatin1String("website"));
    if(!v.canConvert(QVariant::Url))
      return false;
    m_website = podcastMap.value(QLatin1String("website")).toUrl();
    v = podcastMap.value(QLatin1String("mygpo_link"));
    if(!v.canConvert(QVariant::Url))
      return false;
    m_mygpoUrl = podcastMap.value(QLatin1String("mygpo_link")).toUrl();
    return true;
}

bool Podcast::parse(const QByteArray& data)
{	
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      if (!parse( variant )) return false;
      return true;
    } else {
      return false;
    }
}

void Podcast::parseData() {
    //parsen und signal senden
    QJson::Parser parser;
    if (parse( m_reply->readAll() ) ) { 
      emit finished();
    } else {
      emit parseError();
    }
}

void Podcast::error(QNetworkReply::NetworkError error) {
    this->m_error = error;
    emit requestError(error);
}