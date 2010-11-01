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

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

/**
 * Class for sending HTTP requests and handle the servers response.
 */
class RequestHandler {
public:
	/**
	 * Gets an instance of the RequestHandler
	 * @return The instance of the RequestHandler object.
	 */
	static RequestHandler& instance();
	/**
	 * Sends a GET request with the given url and receives the servers response.
	 * @param response The servers response will be written into this QByteArray
	 * @param url The request url
	 * @return 0 if the request was successful, 1 if an error occurred.
	 */
	int getRequest(QByteArray& response, const QUrl& url);

private:
	QNetworkAccessManager manager;
	static RequestHandler _instance;
	QNetworkReply::NetworkError errorFlag;

	RequestHandler() {};
	RequestHandler(const RequestHandler&) {};

	void handleError(QNetworkReply::NetworkError code);
};

#endif /* REQUESTHANDLER_H_ */
