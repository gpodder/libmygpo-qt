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

#include "DeviceList.h"
#include <parser.h>
#include <QDebug>

namespace mygpo
{

class DeviceListPrivate : public QObject
{
    Q_OBJECT
public:
    DeviceListPrivate(DeviceList* qq, QNetworkReply* reply);
    virtual ~DeviceListPrivate();
    QVariant devices() const;
    QList< DevicePtr > devicesList() const;

private:
    DeviceList* q;
    QNetworkReply* m_reply;
    QVariant m_devices;
    QList<DevicePtr> m_devicesList;
    QNetworkReply::NetworkError m_error;

    bool parse ( const QVariant& data );
    bool parse ( const QByteArray& data );

private slots:
    void parseData();
    void error ( QNetworkReply::NetworkError error );
};

}


using namespace mygpo;

DeviceListPrivate::DeviceListPrivate(DeviceList* qq, QNetworkReply* reply) : q(qq), m_reply(reply), m_error(QNetworkReply::NoError)
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

DeviceListPrivate::~DeviceListPrivate()
{
    delete m_reply;
}

QVariant DeviceListPrivate::devices() const
{
    return m_devices;
}

QList< DevicePtr > DeviceListPrivate::devicesList() const
{
    QVariantList varList = m_devices.toList();
    QList< QMap< QString, QString > > ret;
    foreach( const QVariant& var, varList)
    {
        if (var.canConvert(QVariant::Map))
        {
            QMap<QString,QVariant> varMap;
            QMap<QString,QString> tmp;

            varMap = var.toMap();
            if (varMap.value(QLatin1String("id")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("id"),varMap.value(QLatin1String("id")).toString());
            if (varMap.value(QLatin1String("caption")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("caption"),varMap.value(QLatin1String("caption")).toString());
            if (varMap.value(QLatin1String("type")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("type"),varMap.value(QLatin1String("type")).toString());
            if (varMap.value(QLatin1String("subscription")).canConvert(QVariant::Int))
                tmp.insert(QLatin1String("subscription"),QString::number(varMap.value(QLatin1String("subscription")).toInt()));
            ret.append(tmp);
        }
    }
    return ret;
}

void DeviceListPrivate::error(QNetworkReply::NetworkError error)
{
    m_error = error;
    emit q->requestError(error);
}

bool DeviceListPrivate::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::List))
        return false;
    
    QVariantList varList = data.toList();
    QVariantList devList;
    foreach( const QVariant& var, varList)
    {
        m_devicesList.append(DevicePtr (new Device(var)));
        QVariant v;
        v.setValue<DevicePtr>(DevicePtr (new Device(var)));
        devList.append(v);
    }
    m_devices = devList;
    return true;
}

bool DeviceListPrivate::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if ( ok ) {
        ok = (parse( variant ));
    }
    return ok;
}


void DeviceListPrivate::parseData()
{
    if (m_reply->error()==QNetworkReply::NoError) {
        if ( parse( m_reply->readAll() ) ) {
            emit q->finished();
        } else {
            emit q->parseError();
        }
    }
}

DeviceList::DeviceList(QNetworkReply* reply, QObject* parent) : QObject(parent), d(new DeviceListPrivate(this, reply))
{

}

DeviceList::~DeviceList()
{
    delete d;
}

QVariant mygpo::DeviceList::devices() const
{
    return d->devices();
}

QList< DevicePtr > DeviceList::devicesList() const
{
    return d->devicesList();
}


#include "DeviceList.moc"
