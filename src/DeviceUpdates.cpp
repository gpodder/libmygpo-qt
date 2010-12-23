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

#include <QObject>
#include <parser.h>
#include "DeviceUpdates.h"

namespace mygpo
{

class DeviceUpdatesPrivate : public QObject
{
    Q_OBJECT
public:
    DeviceUpdatesPrivate(DeviceUpdates* qq, QNetworkReply* reply);
    ~DeviceUpdatesPrivate();
    QList<PodcastPtr> addList() const;
    QList<EpisodePtr> updateList() const;
    QList<QUrl> removeList() const;
    QVariant add() const;
    QVariant update() const;
    QVariant remove() const;
    qulonglong timestamp() const;
    
private:
    DeviceUpdates* q;
    QVariant m_add;
    QVariant m_update;
    QVariant m_remove;
    qlonglong m_timestamp;
    
    QNetworkReply* m_reply;
    QNetworkReply::NetworkError m_error;
    
    
    bool parse ( const QVariant& data );
    bool parse ( const QByteArray& data );

private slots:
    void parseData();
    void error ( QNetworkReply::NetworkError error );
    
};
}

using namespace mygpo;


DeviceUpdatesPrivate::DeviceUpdatesPrivate(DeviceUpdates* qq, QNetworkReply* reply): q(qq), m_timestamp(0), m_reply(reply)
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}


DeviceUpdatesPrivate::~DeviceUpdatesPrivate()
{
    if (m_reply)
        delete m_reply;
}


QVariant DeviceUpdatesPrivate::add() const
{
    return m_add;
}

QList< PodcastPtr > DeviceUpdatesPrivate::addList() const
{
    QVariantList updateVarList = m_add.toList();
    QList<PodcastPtr> ret;
    foreach( const QVariant& var, updateVarList) 
    {
        ret.append(PodcastPtr(new Podcast(var)));
    }
    return ret;
}

QVariant DeviceUpdatesPrivate::remove() const
{
    return m_remove;
}

QList< QUrl > DeviceUpdatesPrivate::removeList() const
{
    QVariantList updateVarList = m_remove.toList();
    QList<QUrl> ret;
    foreach( const QVariant& var, updateVarList) 
    {
        if(var.canConvert(QVariant::Url)) 
            ret.append(var.toUrl());
    }
    return ret;
}

QVariant DeviceUpdatesPrivate::update() const
{
    return m_update;
}

QList< EpisodePtr > DeviceUpdatesPrivate::updateList() const
{
    QVariantList updateVarList = m_update.toList();
    QList<EpisodePtr> ret;
    foreach( const QVariant& var, updateVarList) 
    {
        ret.append(EpisodePtr(new Episode(var)));
    }
    return ret;
}

bool DeviceUpdatesPrivate::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::Map))
        return false;
    QVariantMap varMap = data.toMap();
    m_add = varMap.value(QLatin1String("add"));
    m_remove = varMap.value(QLatin1String("remove"));
    m_update = varMap.value(QLatin1String("updates"));
    if(varMap.value(QLatin1String("timestamp")).canConvert(QVariant::LongLong))
        m_timestamp = varMap.value(QLatin1String("timestamp")).toLongLong();
    return true;
}

bool DeviceUpdatesPrivate::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      ok = (parse( variant ));
    }
    return ok;
}

void DeviceUpdatesPrivate::parseData()
{
    if (m_reply->error() == QNetworkReply::NoError) {
        if ( parse( m_reply->readAll() ) ) {
            emit q->finished();
        } else {
            emit q->parseError();
        }
    }
}

void DeviceUpdatesPrivate::error(QNetworkReply::NetworkError error)
{
    m_error = error;
    emit q->requestError(error);
}

qulonglong DeviceUpdatesPrivate::timestamp() const
{
    return m_timestamp;
}


DeviceUpdates::DeviceUpdates(QNetworkReply* reply, QObject* parent): QObject(parent), d(new DeviceUpdatesPrivate(this,reply))
{

}

DeviceUpdates::~DeviceUpdates()
{
    delete d;
}


QVariant DeviceUpdates::add() const
{
    return d->add();
}

QList< PodcastPtr > DeviceUpdates::addList() const
{
    return d->addList();
}

QVariant mygpo::DeviceUpdates::remove() const
{
    return d->remove();
}

QList< QUrl > mygpo::DeviceUpdates::removeList() const
{
    return d->removeList();
}

QVariant mygpo::DeviceUpdates::update() const
{
    return d->update();
}

QList< mygpo::EpisodePtr > mygpo::DeviceUpdates::updateList() const
{
    return d->updateList();
}

qulonglong DeviceUpdates::timestamp() const
{
    return d->timestamp();
}


#include "DeviceUpdates.moc"