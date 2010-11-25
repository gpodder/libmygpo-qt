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

#include "AddRemoveResult.h"

#include "JsonParser.h"

using namespace mygpo;


AddRemoveResult::AddRemoveResult(qulonglong timestamp, const QVariant& updateUrlsVar, QObject* parent): QObject(parent), m_timestamp(timestamp), m_updateUrlsVar(updateUrlsVar) {
  
}

AddRemoveResult::AddRemoveResult(QNetworkReply* reply, QObject* parent)
{
    QObject::connect(reply,SIGNAL(finished()), this, SLOT(parseData()));
    QObject::connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),
		      this,SLOT(error(QNetworkReply::NetworkError)));
}

AddRemoveResult::AddRemoveResult(const AddRemoveResult& other): QObject(other.parent()), m_timestamp(other.timestamp()), m_updateUrlsVar(other.updateUrlsVar())
{

}

AddRemoveResult AddRemoveResult::operator=(const AddRemoveResult& other)
{
    return AddRemoveResult(other);
}

qulonglong AddRemoveResult::timestamp() const
{
    return m_timestamp;
}

QVariant AddRemoveResult::updateUrlsVar() const
{
    return m_updateUrlsVar;
}


const QList< QPair< QUrl, QUrl > > AddRemoveResult::updateUrls() const
{
    return JsonParser::toUrlPairList(m_updateUrlsVar);
}


void AddRemoveResult::parseData() {
    //parsen und signal senden
    
    emit finished();
}

void AddRemoveResult::error(QNetworkReply::NetworkError error) {
    this->m_error = error;
}
