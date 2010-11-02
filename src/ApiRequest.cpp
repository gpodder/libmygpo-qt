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


#include "ApiRequest.h"
#include "UrlBuilder.h"
#include "RequestHandler.h"

using namespace mygpo;


QByteArray mygpo::ApiRequest::toplistOpml(int count)
{
  QUrl requestUrl = UrlBuilder::instance().getToplistUrl(count, UrlBuilder::OPML);
  QByteArray response;
  RequestHandler::instance().getRequest(response, requestUrl);
  return response;
}

QByteArray mygpo::ApiRequest::searchOpml(const QString& query)
{
  QUrl requestUrl = UrlBuilder::instance().getPodcastSearchUrl(query, UrlBuilder::OPML);
  QByteArray response;
  RequestHandler::instance().getRequest(response, requestUrl);
  return response;
}
