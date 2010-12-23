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

#include <QNetworkReply>
#include <parser.h>

#include <QDebug>

#include "Settings.h"

namespace mygpo {

class SettingsPrivate : public QObject
{
    Q_OBJECT

public:
    SettingsPrivate(Settings* qq,QNetworkReply* reply);
    virtual ~SettingsPrivate();
    QVariant settings() const;

private:
    Settings* const q;
    QVariant m_settings;

    QNetworkReply* m_reply;
    QNetworkReply::NetworkError m_error;

    bool parse ( const QVariant& data );
    bool parse ( const QByteArray& data );

private slots:
    void parseData();
    void error ( QNetworkReply::NetworkError error );

};

SettingsPrivate::SettingsPrivate(Settings* qq, QNetworkReply* reply): q(qq), m_reply(reply), m_error(QNetworkReply::NoError)
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ), this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

SettingsPrivate::~SettingsPrivate()
{
    delete m_reply;
}

QVariant SettingsPrivate::settings() const
{
    return m_settings;
}

bool SettingsPrivate::parse(const QVariant& data)
{
    m_settings = data;
    return true;
}

bool SettingsPrivate::parse(const QByteArray& data)
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

void SettingsPrivate::parseData()
{
	if (m_reply->error() == QNetworkReply::NoError) {
        QJson::Parser parser;
        if ( parse ( m_reply->readAll()  ) )
        {
            emit q->finished();
        }
        else
        {
            emit q->parseError();
        }
    }
}


void SettingsPrivate::error(QNetworkReply::NetworkError error)
{
    this->m_error = error;
    emit q->requestError ( error );
}

}


using namespace mygpo;

Settings::Settings(QNetworkReply* reply, QObject* parent): QObject(parent), d(new SettingsPrivate(this,reply))
{

}

Settings::~Settings()
{
    delete d;
}

QVariant Settings::settings() const
{
    return d->settings();
}

#include "Settings.moc"

