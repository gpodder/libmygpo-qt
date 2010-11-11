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

#include "RequestHandler.h"

#include <QEventLoop>

using namespace mygpo;

RequestHandler RequestHandler::_instance;

RequestHandler& RequestHandler::instance()
{
    return _instance;
}

int RequestHandler::getRequest(QByteArray& response, const QUrl& url)
{
	errorFlag = QNetworkReply::NoError;

	QNetworkRequest request(url);
	QNetworkReply *reply = manager.get(request);
	QEventLoop loop;
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this,
			         SLOT(handleError(QNetworkReply::NetworkError)));
	QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop,
			         SLOT(quit()));

	// Execute the event loop here, now we will wait here until readyRead() signal is emitted
	// which in turn will trigger event loop quit.
	loop.exec();

	if (errorFlag == QNetworkReply::NoError) {
		response = reply->readAll();
	}
	return errorFlag;
}



int RequestHandler::postRequest( QByteArray& response, const QByteArray& data, const QUrl& url )
{
  /*NOTE: using the same variable for error handling as getRequest.
   * (If we want to implement asynchronous calls for get/post-Request, use 
   * a new variable and error handling function (slot) for each request-function.)
   * Also use a copy of data for asynchronous calls!
   */
  
  errorFlag = QNetworkReply::NoError;
  QNetworkRequest request( url );
  QNetworkReply *reply = manager.post( request, data );
  QEventLoop loop;
  QObject::connect( reply, SIGNAL( finished() ), &loop, SLOT( quit() ) );
  QObject::connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ), this,
		    SLOT( handleError( QNetworkReply::NetworkError ) ) );
  QObject::connect( reply, SIGNAL( error( QNetworkReply::NetworkError ) ), &loop,
		    SLOT( quit() ) );

  loop.exec();
  
  if( errorFlag == QNetworkReply::NoError ) {
    response = reply->readAll();
  }
  return errorFlag;
}


void RequestHandler::handleError(QNetworkReply::NetworkError code)
{
	errorFlag = code;
}








