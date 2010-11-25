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

#ifndef REQUESTEXCEPTIONS_H_
#define REQUESTEXCEPTIONS_H_

#include <stdexcept>
#include <QString>
#include <QNetworkReply>

namespace mygpo {

/**
 * The RequestException class is an exception which is thrown
 * whenever a request sent by the ApiRequest fails.
 * It may also be caught as a std::runtime_error.
 */

class RequestException : public std::runtime_error {
public:
	RequestException(const QString &s, QNetworkReply::NetworkError errorFlag);
	/**
	 * errorFlag contains information about possible server errors.
	 * It can be interpreted like values from QNetworkReply::NetworkError
	 */
	const QNetworkReply::NetworkError errorFlag;

	virtual ~RequestException() throw() { }
};

class InvalidDeviceIdException : RequestException {
public:
	InvalidDeviceIdException();
	virtual ~InvalidDeviceIdException() throw() { }
};

class InvalidUserException : public RequestException {
public:
	InvalidUserException();
	virtual ~InvalidUserException() throw() { }
};

class InvalidAuthException : public RequestException {
public:
	InvalidAuthException();
	virtual ~InvalidAuthException() throw() { }
};

class ServerNotFoundException : public RequestException {
public:
	ServerNotFoundException();
	virtual ~ServerNotFoundException() throw() { }
};

}

#endif /* REQUESTEXCEPTIONS_H_ */
