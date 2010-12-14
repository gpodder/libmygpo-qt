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
#include <QDebug>
#include <QSharedPointer>

namespace mygpo {
  
class PodcastPrivate : QObject
{
  Q_OBJECT
public:
  PodcastPrivate(Podcast* qq, QNetworkReply* reply,QObject* parent = 0);
  PodcastPrivate(Podcast* qq, const QUrl& url, const QString& title, const QString& description, int subscribers, const QUrl& logoUrl, const QUrl& website, const QUrl& mygpolink, QObject* parent = NULL);
  PodcastPrivate(Podcast* qq, const QVariant& variant, QObject* parent = 0);
  PodcastPrivate(Podcast* qq, const PodcastPrivate* pp, QObject* partent = 0);
  PodcastPrivate(Podcast* qq , QObject* parent = 0);
  //Getters
  QUrl url() const;
  QString title() const;
  QString description() const;
  uint subscribers() const;
  //const uint subscriberstLastWeek();
  QUrl logoUrl() const;
  QUrl website() const;
  QUrl mygpoUrl() const;
  
private:
  QSharedPointer<QNetworkReply> m_reply;
  Podcast* const q;
  QUrl m_url;
  QString m_title;
  QString m_description;
  uint m_subscribers;
  //uint m_SubscribersLastWeek;
  QUrl m_logoUrl;
  QUrl m_website;
  QUrl m_mygpoUrl;
  QNetworkReply::NetworkError m_error;

  
  bool parse(const QVariant& data);
  bool parse(const QByteArray& data);
private slots:
  void parseData();
  void error(QNetworkReply::NetworkError error);

  
};
  
};


using namespace mygpo;

PodcastPrivate::PodcastPrivate(Podcast* qq, QNetworkReply* reply, QObject* parent): QObject( parent), m_reply(reply), q(qq), m_error(QNetworkReply::NoError)
{
    QObject::connect(&(*m_reply),SIGNAL(finished()), this, SLOT(parseData()));
    QObject::connect(&(*m_reply),SIGNAL(error(QNetworkReply::NetworkError)),
		      this,SLOT(error(QNetworkReply::NetworkError)));
}

PodcastPrivate::PodcastPrivate(Podcast* qq, const QUrl& url, const QString& title, const QString& description, 
			       int subscribers, const QUrl& logoUrl, const QUrl& website, const QUrl& mygpolink,
			       QObject* parent): 
			       QObject(parent), q(qq), m_url(url), m_title(title), m_description(description), 
			       m_subscribers(subscribers), m_logoUrl(logoUrl), m_website(website), m_mygpoUrl(mygpolink)
{

}


PodcastPrivate::PodcastPrivate(Podcast* qq, const QVariant& variant, QObject* parent): QObject(parent),  m_reply(0), q(qq), m_error(QNetworkReply::NoError)
{
    parse(variant);
}

PodcastPrivate::PodcastPrivate(Podcast* qq, const mygpo::PodcastPrivate* pp, 
			       QObject* partent): QObject(partent), m_reply(pp->m_reply), q(qq),
			       m_url(pp->m_url), m_title(pp->m_title), m_description(pp->m_description),
			       m_subscribers(pp->m_subscribers), m_logoUrl(pp->m_logoUrl), m_website(pp->m_website),
			       m_mygpoUrl(pp->m_mygpoUrl), m_error(pp->m_error)
{
	if (m_reply != 0) {
		QObject::connect(&(*m_reply),SIGNAL(finished()), this, SLOT(parseData()));
		QObject::connect(&(*m_reply),SIGNAL(error(QNetworkReply::NetworkError)),
				this,SLOT(error(QNetworkReply::NetworkError)));
	}
}

PodcastPrivate::PodcastPrivate(Podcast* qq, QObject* parent): QObject(parent), q(qq)
{

}


QUrl PodcastPrivate::url() const
{
    return m_url;
}

QString PodcastPrivate::title() const
{
    return m_title;
}

QString PodcastPrivate::description() const
{
    return m_description;
}

uint PodcastPrivate::subscribers() const
{
    return m_subscribers;
}

QUrl PodcastPrivate::logoUrl() const
{
    return m_logoUrl;
}

QUrl PodcastPrivate::website() const
{
    return m_website;
}

QUrl PodcastPrivate::mygpoUrl() const
{
    return m_mygpoUrl;
}




Podcast::Podcast(const QUrl& url, const QString& title, const QString& description, int subscribers,
		 const QUrl& logoUrl, const QUrl& website, const QUrl& mygpolink, QObject* parent) : 
		 QObject(parent), d(new PodcastPrivate(this, url, title, description, subscribers,
		 logoUrl, website, mygpolink))
		 
{

}

Podcast::Podcast() : d(new PodcastPrivate(this))
{

}


Podcast::Podcast(QNetworkReply* reply, QObject* parent) : QObject(parent), d(new PodcastPrivate(this,reply))
{
   
}

Podcast::Podcast(const QVariant& variant, QObject* parent): QObject(parent), d(new PodcastPrivate(this,variant))
{

}


Podcast::Podcast(const Podcast& other): QObject(other.parent()), d(new PodcastPrivate (this, other.d))
{
  
}

Podcast::~Podcast()
{
  delete d;
}

Podcast Podcast::Podcast::operator=(const mygpo::Podcast& other)
{
    return Podcast(other);
}


QUrl Podcast::url() const
{
    return d->url();
}

QString Podcast::title() const
{
    return d->title();
}

QString Podcast::description() const
{
    return d->description();
}

uint Podcast::subscribers() const
{
    return d->subscribers();
}

QUrl Podcast::logoUrl() const
{
    return d->logoUrl();
}

QUrl Podcast::website() const
{
    return d->website();
}

QUrl Podcast::mygpoUrl() const
{
    return d->mygpoUrl();
}

bool PodcastPrivate::parse(const QVariant& data) 
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

bool PodcastPrivate::parse(const QByteArray& data)
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

void PodcastPrivate::parseData() {
    //parsen und signal senden
    QJson::Parser parser;
    if (parse( m_reply->peek( m_reply->bytesAvailable() ) ) ) {
      emit q->finished();
    } else {
      emit q->parseError();
    }
}

void PodcastPrivate::error(QNetworkReply::NetworkError error) {
    this->m_error = error;
    emit q->requestError(error);
}


#include "../build/src/Podcast.moc"
