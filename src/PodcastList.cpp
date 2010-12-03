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

#include "PodcastList.h"

#include <parser.h>
#include <QDebug>

namespace mygpo
{

class PodcastListPrivate : QObject
{
  Q_OBJECT
public:
  PodcastListPrivate(PodcastList* qq, QNetworkReply* reply, QObject* parent = 0);
  PodcastListPrivate(PodcastList* qq, QObject* parent = 0);
  PodcastListPrivate(PodcastList* qq, PodcastListPrivate* pp ,QObject* parent = 0);
  QList<Podcast> list() const;
  QVariant podcasts() const;
  QNetworkReply* m_reply;
    
private:
  PodcastList* const q;
  QVariant m_podcasts;
  QNetworkReply::NetworkError m_error;

  bool parse ( const QVariant& data );
  bool parse ( const QByteArray& data );
private slots:
  void parseData();
  void error(QNetworkReply::NetworkError error);
};

};



using namespace mygpo;


PodcastListPrivate::PodcastListPrivate(PodcastList* qq, QNetworkReply* reply, QObject* parent) : QObject ( parent ), m_reply ( reply ), q(qq)
{
  QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
  QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

PodcastListPrivate::PodcastListPrivate(PodcastList* qq, QObject* parent) : QObject(parent), m_reply ( 0 ), q(qq), m_podcasts ( QVariant() )
{
}

PodcastListPrivate::PodcastListPrivate(PodcastList* qq, 
				       PodcastListPrivate* pp, QObject* parent):
				       QObject(parent), m_reply(pp->m_reply), q(qq), m_podcasts(pp->m_podcasts)
{
  QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
  QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}



QList< Podcast > PodcastListPrivate::list() const
{
  QList<Podcast> list;
  QVariantList varList = m_podcasts.toList();
  foreach ( QVariant var,varList )
  {
    list.append ( var.value<mygpo::Podcast>() );
  }
  return list;
}

QVariant PodcastListPrivate::podcasts() const
{    
  return m_podcasts;
}

bool PodcastListPrivate::parse ( const QVariant& data )
{
    if ( !data.canConvert ( QVariant::List ) )
        return false;
    QVariantList varList = data.toList();
    QVariantList podcastList;
    foreach ( QVariant var,varList )
    {
        QVariant v;
        v.setValue<mygpo::Podcast> ( Podcast ( var ) );
        podcastList.append ( v );
    }
    m_podcasts = QVariant ( podcastList );
    return true;
}

bool PodcastListPrivate::parse ( const QByteArray& data )
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse ( data, &ok );
    if ( ok )
    {
        ok = ( parse ( variant ) );
    }
    return ok;
}


void PodcastListPrivate::parseData()
{
    QJson::Parser parser;
    //if ( parse ( m_reply->readAll() ) )
    if ( parse ( m_reply->peek( m_reply->bytesAvailable() ) ) )
    {
        emit q->finished();
    }
    else
    {
        emit q->parseError();
    }
}

void PodcastListPrivate::error ( QNetworkReply::NetworkError error )
{
    this->m_error = error;
    emit q->requestError ( error );
}





PodcastList::PodcastList() : d(new PodcastListPrivate(this))
{

}

PodcastList::PodcastList ( QNetworkReply* reply, QObject* parent ) : QObject(parent), d(new PodcastListPrivate(this,reply))
{
    
}

PodcastList::PodcastList ( const PodcastList& other ) : QObject ( other.parent() ) , d(new PodcastListPrivate(this,other.d))
{
  
}

PodcastList::~PodcastList()
{
  delete d;
}

QList<Podcast> PodcastList::list() const
{
   return d->list();
}

QVariant PodcastList::podcasts() const
{
  return d->podcasts();
}

#include "../build/src/PodcastList.moc"