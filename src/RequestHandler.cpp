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

#include <QAuthenticator>
#include <QCoreApplication>

#include "RequestHandler.h"

using namespace mygpo;

RequestHandler::RequestHandler(const QString& username, const QString& password, QNetworkAccessManager* nam) : m_username(username), m_password(password), m_loginFailed(false), m_nam(nam)
{
    QObject::connect(m_nam, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), this,
                     SLOT(authenticate( QNetworkReply*, QAuthenticator*)));
}

RequestHandler::RequestHandler(QNetworkAccessManager* nam) : m_password(), m_loginFailed(false), m_nam(nam)
{
}

RequestHandler::~RequestHandler()
{
    //m_nam->deleteLater();
}

QNetworkReply* RequestHandler::getRequest(const QUrl& url)
{
    m_loginFailed = false;
    QNetworkRequest request(url);
    QNetworkReply* reply = m_nam->get(request);
    return reply;
}

QNetworkReply* RequestHandler::postRequest(const QByteArray data, const QUrl& url )
{
    m_loginFailed = false;
    QNetworkRequest request( url );
    QNetworkReply* reply = m_nam->post( request, data );
    return reply;
}

void RequestHandler::authenticate( QNetworkReply* reply, QAuthenticator* authenticator )
{
    if (m_loginFailed) {
        reply->abort();
    } else {
        m_loginFailed = true;
        authenticator->setUser(m_username);
        authenticator->setPassword(m_password);
    }
}
