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

using namespace mygpo;

Episode::Episode(QUrl url, QString title, QUrl podcastUrl, QString podcastTitle, QString description, QUrl website, QUrl mygpoUrl, QObject* parent): QObject(parent), m_url(url), m_title(title), m_podcastUrl(podcastUrl), m_podcastTitle(podcastTitle), m_description(description), m_website(website), m_mygpoUrl(mygpoUrl)
{

}

Episode::~Episode()
{

}

const QUrl mygpo::Episode::url() const
{
    return m_url;
}

const QString mygpo::Episode::title() const
{
    return m_title;
}

const QUrl mygpo::Episode::podcastUrl() const
{
    return m_podcastUrl;
}

const QString mygpo::Episode::podcastTitle() const
{
    return m_podcastTitle;
}

const QString mygpo::Episode::description() const
{
    return m_description;
}

const QUrl mygpo::Episode::website() const
{
    return m_website;
}

const QUrl mygpo::Episode::mygpoUrl() const
{
    return m_mygpoUrl;
}
