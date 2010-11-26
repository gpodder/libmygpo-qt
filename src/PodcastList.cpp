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

namespace mygpo {

PodcastList::PodcastList() : m_reply(0), m_podcasts(QVariant())
{

}

    
PodcastList::PodcastList(QNetworkReply* reply, QObject* parent) : QObject(parent), m_reply(reply)
{
    QObject::connect(reply,SIGNAL(finished()), this, SLOT(parseData()));
    QObject::connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
              this,SLOT(error(QNetworkReply::NetworkError)));
}

PodcastList::PodcastList(const PodcastList& other): QObject(other.parent()), m_reply(other.m_reply), m_podcasts(other.m_podcasts)
{
}

PodcastList::~PodcastList() {
}

QList<Podcast> PodcastList::list() const
{
	QList<Podcast> list;
    QVariantList varList = m_podcasts.toList();
    foreach(QVariant var,varList)
    {
        list.append(var.value<mygpo::Podcast>());
    }
    return list;        
}

bool PodcastList::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::List))
        return false;
    QVariantList varList = data.toList();
    QVariantList podcastList;
    foreach (QVariant var,varList)
    {
        QVariant v;
        v.setValue<mygpo::Podcast>(Podcast(var));
        podcastList.append(v);
    }
    m_podcasts = QVariant(podcastList);
    return true;
}

bool PodcastList::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      ok = (parse( variant ));
    }
    return ok;
}


void PodcastList::parseData()
{
    QJson::Parser parser;
    if (parse( m_reply->readAll() ) ) { 
      emit finished();
    } else {
      emit parseError();
    }
}

void PodcastList::error(QNetworkReply::NetworkError error)
{
    this->m_error = error;
    emit requestError(error);
}


QVariant PodcastList::podcasts() const
{
	return m_podcasts;
}

}
