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

using namespace mygpo;

Podcast::Podcast(QNetworkReply* reply, QObject* parent) : m_error(QNetworkReply::NoError)
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

void Podcast::parseData() {
    //parsen und signal senden
    
    emit finished();
}

void Podcast::error(QNetworkReply::NetworkError error) {
    this->m_error = error;
}