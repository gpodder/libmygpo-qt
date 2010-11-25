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

#ifndef REQUESTHANDLER_H_
#define REQUESTHANDLER_H_

#include "mygpo_export.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

namespace mygpo {

/**
 * Class for sending HTTP requests and handle the servers response.
 */
class MYGPO_EXPORT RequestHandler : public QObject {

    Q_OBJECT

public:

    /**
     * @param username The username that should be used for authentication if required.
     * @param password The password that should be used for authentication if required
     */
    RequestHandler(const QString& username, const QString& password, const QNetworkAccessManager& manager = QNetworkAccessManager());
    RequestHandler();

    /**
     * Sends a GET request with the given url and receives the servers response.
     * @param response The servers response will be written into this QByteArray
     * @param url The request url
     * @return 0 if the request was successful, corresponding ErrorCode if unsuccessful
     */
    QNetworkReply* getRequest(const QUrl& url );

    /**
     * Sends a POST request with the given url and data.
     * @param data The data to send to the url
     * @param url The request url
     * @return 0 if the request was successful, corresponding ErrorCode if unsuccessful
     */
    QNetworkReply* postRequest(const QByteArray& data, const QUrl& url );

private:
    QNetworkAccessManager m_nam;
    QString m_username;
    QString m_password;
    bool m_loginFailed;

private slots:
    void authenticate( QNetworkReply* reply, QAuthenticator* authentiactor );
};

}

#endif /* REQUESTHANDLER_H_ */
