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

#include <parser.h>

#include "AddRemoveResult.h"

#include <QDebug>

using namespace mygpo;


AddRemoveResult::AddRemoveResult ( qulonglong timestamp, const QVariant& updateUrls, QObject* parent ) : QObject ( parent ), m_timestamp ( timestamp ), m_updateUrls ( updateUrls )
{

}

AddRemoveResult::AddRemoveResult ( QNetworkReply* reply, QObject* parent ) : QObject ( parent ), m_reply ( reply )
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ), this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

AddRemoveResult::AddRemoveResult ( const AddRemoveResult& other ) : QObject ( other.parent() ), m_timestamp ( other.timestamp() ), m_updateUrls ( other.updateUrls() ), m_reply ( other.m_reply )
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ), this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

AddRemoveResult::AddRemoveResult()
{

}

AddRemoveResult AddRemoveResult::operator= ( const AddRemoveResult& other )
{
    return AddRemoveResult ( other );
}

qulonglong AddRemoveResult::timestamp() const
{
    return m_timestamp;
}

QVariant AddRemoveResult::updateUrls() const
{
    return m_updateUrls;
}

QList< QPair< QUrl, QUrl > > AddRemoveResult::updateUrlsList() const
{
    QVariantList updateVarList = updateUrls().toList();
    QList<QPair<QUrl, QUrl > > updateUrls;
    foreach ( const QVariant& url, updateVarList )
    {
        QVariantList urlList = url.toList();
        QUrl first = QUrl ( urlList.at ( 0 ).toString() );
        QUrl second = QUrl ( urlList.at ( 1 ).toString() );
        updateUrls.append ( qMakePair ( first,second ) );
    }
    return updateUrls;
}

bool AddRemoveResult::parse ( const QVariant& data )
{
    QJson::Parser parser;
    if (!data.canConvert(QVariant::Map))
        return false;
    QVariantMap resultMap = data.toMap();
    QVariant v = resultMap.value ( QLatin1String ( "timestamp" ) );
    if (!v.canConvert(QVariant::ULongLong))
        return false;
    m_timestamp = v.toULongLong();
    m_updateUrls = resultMap.value ( QLatin1String ( "update_urls" ) );
    return true;
}

bool AddRemoveResult::parse ( const QByteArray& data )
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse ( data, &ok );
    if ( ok )
    {
        ok = ( parse ( variant ) );
    }
    return ok;
}


void AddRemoveResult::parseData()
{
    QJson::Parser parser;
    if ( parse ( m_reply->readAll() ) )
    {
        emit finished();
    }
    else
    {
        emit parseError();
    }
}

void AddRemoveResult::error ( QNetworkReply::NetworkError error )
{
    this->m_error = error;
    emit requestError ( error );
}
