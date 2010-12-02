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



namespace mygpo {
  
class EpisodePrivate : QObject
{
  Q_OBJECT
  
public:
  EpisodePrivate(Episode* qq, QObject* parent = 0);
  EpisodePrivate(Episode* qq, QNetworkReply* reply, QObject* parent = 0);
  EpisodePrivate(Episode* qq, const QVariant& variant, QObject* parent = 0);
  EpisodePrivate(Episode* qq, const QUrl& url, const QString& title, const QUrl& podcastUrl, const QString& podcastTitle, const QString& description, const QUrl& website, const QUrl& mygpoUrl, QObject* parent = 0);
  QUrl url() const;
  QString title() const;
  QUrl podcastUrl() const;
  QString podcastTitle() const;
  QString description() const;
  QUrl website() const;
  QUrl mygpoUrl() const;
private:
  Episode* const q;
  QUrl m_url;
  QString m_title;
  QUrl m_podcastUrl;
  QString m_podcastTitle;
  QString m_description;
  QUrl m_website;
  QUrl m_mygpoUrl;
  QNetworkReply* m_reply;
  QNetworkReply::NetworkError m_error;
  bool parse(const QVariant& data);
  bool parse(const QByteArray& data);
  
private slots:
  void parseData();
  void error(QNetworkReply::NetworkError error);

};

};


using namespace mygpo;

EpisodePrivate::EpisodePrivate(Episode* qq, QObject* parent): QObject(parent), q(qq)
{

}

EpisodePrivate::EpisodePrivate(Episode* qq, QNetworkReply* reply, QObject* parent): QObject(parent), q(qq), m_reply(reply),m_error(QNetworkReply::NoError)
{
  QObject::connect(m_reply,SIGNAL(finished()), this, SLOT(parseData()));
  QObject::connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),
		      this,SLOT(error(QNetworkReply::NetworkError)));
}

EpisodePrivate::EpisodePrivate(Episode* qq, const QVariant& variant, QObject* parent): QObject(parent), q(qq)
{
    qDebug() << "constructing an episode via a variant";
    parse(variant);
}

EpisodePrivate::EpisodePrivate(Episode* qq, const QUrl& url, const QString& title, const QUrl& podcastUrl, 
			       const QString& podcastTitle, const QString& description, const QUrl& website, 
			       const QUrl& mygpoUrl, QObject* parent): 
			       QObject(parent), q(qq), m_url(url), m_title(title), m_podcastUrl(podcastUrl),
			       m_podcastTitle(podcastTitle), m_description(description), m_website(website), 
			       m_mygpoUrl(mygpoUrl), m_error(QNetworkReply::NoError)
{

}


bool EpisodePrivate::parse(const QVariant& data) 
{
    if (!data.canConvert(QVariant::Map) )      
      return false;
    QVariantMap episodeMap = data.toMap();
    QVariant s = episodeMap.value(QLatin1String("url"));
    if (!s.canConvert(QVariant::Url)) 
      return false;
    m_url = episodeMap.value(QLatin1String("url")).toUrl();
    s = episodeMap.value(QLatin1String("title"));
    if (!s.canConvert(QVariant::String)) 
      return false;
    m_title = episodeMap.value(QLatin1String("title")).toString();
    s = episodeMap.value(QLatin1String("podcast_url"));
    if (!s.canConvert(QVariant::Url))
      return false;
    m_podcastUrl = episodeMap.value(QLatin1String("podcast_url")).toUrl();
    s = episodeMap.value(QLatin1String("podcast_title"));
    if (!s.canConvert(QVariant::String))
      return false;
    m_podcastTitle = episodeMap.value(QLatin1String("podcast_title")).toString();
    s = episodeMap.value(QLatin1String("description"));
    if (!s.canConvert(QVariant::String))
      return false;
    m_description = episodeMap.value(QLatin1String("description")).toString();
    s = episodeMap.value(QLatin1String("website"));
    if(!s.canConvert(QVariant::Url))
      return false;
    m_website = episodeMap.value(QLatin1String("website")).toUrl();
    s = episodeMap.value(QLatin1String("mygpo_link"));
    if(!s.canConvert(QVariant::Url))
      return false;
    m_mygpoUrl = episodeMap.value(QLatin1String("mygpo_link")).toUrl();
    return true;
}

bool EpisodePrivate::parse(const QByteArray& data)
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

void EpisodePrivate::parseData() {
    //parsen und signal senden
    QJson::Parser parser;
    if (parse( m_reply->readAll() ) ) { 
      emit q->finished();
    } else {
      emit q->parseError();
    }
}

void EpisodePrivate::error(QNetworkReply::NetworkError error)
{
  this->m_error = error;
  emit q->requestError(error);
}

QString EpisodePrivate::description() const
{
  return m_description;
}

QUrl EpisodePrivate::mygpoUrl() const
{
  return m_mygpoUrl;
}

QString EpisodePrivate::podcastTitle() const
{
  return m_podcastTitle;
}

QUrl EpisodePrivate::podcastUrl() const
{
  return m_podcastUrl;
}

QString EpisodePrivate::title() const
{
  return m_title;
}

QUrl EpisodePrivate::url() const
{
  return m_url;
}

QUrl EpisodePrivate::website() const
{
  return m_website;
}


Episode::Episode(const QUrl& url, const QString& title, const QUrl& podcastUrl, const QString& podcastTitle, 
		 const QString& description, const QUrl& website, const QUrl& mygpoUrl, QObject* parent):
		 QObject(parent), d(new EpisodePrivate(this,url,title,podcastUrl,podcastTitle,description,website,mygpoUrl)), m_copy(false)
		  {
  
}

Episode::Episode(QNetworkReply* reply,QObject* parent) : QObject(parent), d(new EpisodePrivate(this, reply)), m_copy(false)
{
  
}

Episode::Episode(const QVariant& variant, QObject* parent): QObject(parent), d(new EpisodePrivate(this,variant)), m_copy(false)
{

}


Episode::Episode() : d(new EpisodePrivate(this)), m_copy(false)
{
  
}

Episode::~Episode()
{
  if( !m_copy ) delete d;
}

Episode::Episode(const mygpo::Episode& other): QObject(other.parent()), d(other.d), m_copy(true)
{
  QObject::connect(&other, SIGNAL(finished()), this, SLOT(sendFinished()));
  QObject::connect(&other, SIGNAL(parseError()), this, SLOT(sendParsError()));
  QObject::connect(&other, SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(sendRequestError(QNetworkReply::NetworkError)));
}

Episode Episode::operator=(const mygpo::Episode& other)
{
    return Episode(other);
}


QUrl Episode::url() const
{
    return d->url();
}

QString Episode::title() const
{
    return d->title();
}

QUrl Episode::podcastUrl() const
{
    return d->podcastUrl();
}

QString Episode::podcastTitle() const
{
    return d->podcastTitle();
}

QString Episode::description() const
{
  return d->description();
}

QUrl Episode::website() const
{
    return d->website();
}

QUrl Episode::mygpoUrl() const
{
    return d->mygpoUrl();
}


void Episode::sendFinished()
{
  emit finished();
}

void Episode::sendParsError()
{
  emit parseError();
}

void Episode::sendRequestError(QNetworkReply::NetworkError error)
{
  emit sendRequestError(error);
}

#include "../build/src/Episode.moc"
