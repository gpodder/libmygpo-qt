/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 - 2011 Stefan Derkits <stefan@derkits.at>             *
* Copyright (c) 2010 - 2011 Christian Wagner <christian.wagner86@gmx.at>   *
* Copyright (c) 2010 - 2011 Felix Winter <ixos01@gmail.com>                *
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

#include <QAuthenticator>
#include <QCoreApplication>

#include <QDebug>

#include "RequestHandler.h"

using namespace mygpo;

RequestHandler::RequestHandler( const QString& username, const QString& password, QNetworkAccessManager* nam, bool ssl ) : m_username( username ), m_password( password ), m_nam( nam ), m_ssl( ssl )
{
}

RequestHandler::RequestHandler( QNetworkAccessManager* nam, bool ssl ) : m_username(), m_password(), m_nam( nam ), m_ssl( ssl )
{
}

RequestHandler::~RequestHandler()
{
}

QNetworkReply* RequestHandler::getRequest( const QString& url )
{
    QUrl reqUrl( url );
    if (m_ssl)
        reqUrl.setScheme(QLatin1String("https"));
    qDebug() << reqUrl;
    QNetworkRequest request( reqUrl );
    QNetworkReply* reply = m_nam->get( request );
    return reply;
}

QNetworkReply* RequestHandler::authGetRequest( const QString& url )
{
    QUrl authUrl = addAuthData( url );
    if (m_ssl)
        authUrl.setScheme(QLatin1String("https"));
    QNetworkRequest request( authUrl );
    QNetworkReply* reply = m_nam->get( request );
    return reply;
}


QNetworkReply* RequestHandler::postRequest( const QByteArray data, const QString& url )
{
    QUrl authUrl = addAuthData( url );
    if (m_ssl)
        authUrl.setScheme(QLatin1String("https"));
    QNetworkRequest request( authUrl );
    QNetworkReply* reply = m_nam->post( request, data );
    return reply;
}

QUrl RequestHandler::addAuthData( const QString& url )
{
    QUrl authUrl( url );
    authUrl.setUserName( m_username );
    authUrl.setPassword( m_password );
    return authUrl;
}
