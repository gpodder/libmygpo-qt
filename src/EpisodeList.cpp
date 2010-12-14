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
#include <parser.h>

#include <QDebug>
#include <QSharedPointer>

namespace mygpo {
  
class EpisodeListPrivate : QObject 
{
  Q_OBJECT
  
public:
  EpisodeListPrivate(EpisodeList* qq, QNetworkReply* reply, QObject* parent = 0);
  EpisodeListPrivate(EpisodeList* qq, EpisodeListPrivate* pp, QObject* parent = 0);
  QList<Episode> list() const;
  QVariant episodes() const;
  
private:
  QSharedPointer<QNetworkReply> m_reply;
  EpisodeList* const q;
  QVariant m_episodes;
  QNetworkReply::NetworkError m_error;
  bool parse(const QVariant& data);
  bool parse(const QByteArray& data);

private slots:
  void parseData();
  void error(QNetworkReply::NetworkError error);

};
  
};

using namespace mygpo;


EpisodeListPrivate::EpisodeListPrivate(EpisodeList* qq, QNetworkReply* reply, QObject* parent): QObject( parent ), m_reply( reply ), q(qq)
{
  QObject::connect ( &(*m_reply),SIGNAL ( finished() ), this, SLOT ( parseData() ) );
  QObject::connect ( &(*m_reply),SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

EpisodeListPrivate::EpisodeListPrivate(EpisodeList* qq, EpisodeListPrivate* pp, 
				       QObject* parent): QObject(parent), m_reply( pp->m_reply ), 
				       q(qq), m_episodes(pp->m_episodes)
{
  QObject::connect ( &(*m_reply),SIGNAL ( finished() ), this, SLOT ( parseData() ) );
  QObject::connect ( &(*m_reply),SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

QList<Episode> EpisodeListPrivate::list() const
{
    QList<Episode> list;
    QVariantList varList = m_episodes.toList();
    foreach ( QVariant var,varList )
    {
        list.append ( var.value<mygpo::Episode>() );
    }
    return list;
}

QVariant EpisodeListPrivate::episodes() const
{
    return m_episodes;
}

bool EpisodeListPrivate::parse ( const QVariant& data )
{
    if ( !data.canConvert ( QVariant::List ) )
        return false;
    QVariantList varList = data.toList();
    QVariantList episodeList;
    foreach ( QVariant var,varList )
    {
        QVariant v;
        v.setValue<mygpo::Episode> ( Episode ( var ) );
        episodeList.append ( v );
    }
    m_episodes = QVariant ( episodeList );
    return true;
}


bool EpisodeListPrivate::parse ( const QByteArray& data )
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

void EpisodeListPrivate::parseData()
{
    qDebug() << "parsing episode list data";
    QJson::Parser parser;
    //if ( parse ( m_reply->readAll() ) )
    if ( parse ( m_reply->peek(m_reply->bytesAvailable()) ) )
    {
        emit q->finished();
    }
    else
    {
        emit q->parseError();
    }
}

void EpisodeListPrivate::error ( QNetworkReply::NetworkError error )
{
    this->m_error = error;
    emit q->requestError ( error );
}




EpisodeList::EpisodeList ( QNetworkReply* reply, QObject* parent ) : QObject ( parent ), d(new EpisodeListPrivate(this, reply))
{
   
}

EpisodeList::EpisodeList ( const EpisodeList& other ) : QObject ( other.parent() ), d(new EpisodeListPrivate(this, other.d))
{

}


QVariant EpisodeList::episodes() const
{
  return d->episodes();
}


QList< Episode > EpisodeList::list() const
{
  return d->list();
}

EpisodeList::~EpisodeList()
{
  delete d;
}

#include "../build/src/EpisodeList.moc"