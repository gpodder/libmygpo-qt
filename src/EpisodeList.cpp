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

using namespace mygpo;

EpisodeList::EpisodeList ( QNetworkReply* reply, QObject* parent ) : QObject ( parent ), m_reply ( reply )
{

    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

EpisodeList::EpisodeList ( const EpisodeList& other ) : QObject ( other.parent() ), m_reply ( other.m_reply ), m_episodes ( other.m_episodes )
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

EpisodeList::~EpisodeList()
{
}

QList<Episode> EpisodeList::list() const
{
    QList<Episode> list;
    QVariantList varList = m_episodes.toList();
    foreach ( QVariant var,varList )
    {
        list.append ( var.value<mygpo::Episode>() );
    }
    return list;
}

QVariant EpisodeList::episodes() const
{
    return m_episodes;
}

bool EpisodeList::parse ( const QVariant& data )
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


bool EpisodeList::parse ( const QByteArray& data )
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

void EpisodeList::parseData()
{
    qDebug() << "parsing episode list data";
    QJson::Parser parser;
    if ( parse ( m_reply->readAll() ) )
    {
        emit finished();
    }
    else
    {
        emit parseError();
    }
}

void EpisodeList::error ( QNetworkReply::NetworkError error )
{
    this->m_error = error;
    emit requestError ( error );
}
