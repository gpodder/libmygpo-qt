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

#include "EpisodeActionList.h"

#include <parser.h>

#include <QSharedPointer>
#include <QDebug>

namespace mygpo {

class EpisodeActionListPrivate : public QObject {
  Q_OBJECT

public:
  EpisodeActionListPrivate(EpisodeActionList* qq, QNetworkReply* reply);
  virtual ~EpisodeActionListPrivate();
  QList<EpisodeActionPtr> list() const;
  QVariant episodeActions() const;

  qulonglong timestamp() const;

private:
  QNetworkReply* m_reply;
  EpisodeActionList* const q;
  QVariant m_episodeActions;
  QNetworkReply::NetworkError m_error;
  qulonglong m_timestamp;

  bool parse(const QVariant& data);
  bool parse(const QByteArray& data);

private slots:
  void parseData();
  void error(QNetworkReply::NetworkError error);

};

EpisodeActionListPrivate::EpisodeActionListPrivate(EpisodeActionList* qq, QNetworkReply* reply): m_reply( reply ), q(qq)
{
  QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
  QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

EpisodeActionListPrivate::~EpisodeActionListPrivate()
{
	delete m_reply;
}

QList<EpisodeActionPtr> EpisodeActionListPrivate::list() const
{
    QList<EpisodeActionPtr> list;
    QVariantList varList = m_episodeActions.toList();
    foreach ( QVariant var,varList )
    {
        list.append ( var.value<mygpo::EpisodeActionPtr>() );
    }
    return list;
}

QVariant EpisodeActionListPrivate::episodeActions() const
{
    return m_episodeActions;
}

bool EpisodeActionListPrivate::parse ( const QVariant& data )
{
    if (!data.canConvert(QVariant::Map) )
      return false;
    QVariantMap episodeActionListMap = data.toMap();

    QVariant s = episodeActionListMap.value(QLatin1String("timestamp"));
    if (!s.canConvert(QVariant::ULongLong))
      return false;
    m_timestamp = s.toULongLong();

    s = episodeActionListMap.value(QLatin1String("actions"));
    if (!s.canConvert(QVariant::List))
    	return false;

    QVariantList varList = s.toList();
    QVariantList episodeActionList;
    foreach ( QVariant var,varList )
    {
        QVariant v;
        v.setValue<mygpo::EpisodeActionPtr> ( mygpo::EpisodeActionPtr (new EpisodeAction ( var ) ) );
        episodeActionList.append ( v );
    }
    m_episodeActions = QVariant ( episodeActionList );
    return true;
}


bool EpisodeActionListPrivate::parse ( const QByteArray& data )
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

void EpisodeActionListPrivate::parseData()
{
	if (m_reply->error() == QNetworkReply::NoError) {
		if ( parse ( m_reply->readAll() ) )
		{
			emit q->finished();
		}
		else
		{
			emit q->parseError();
		}
	}
}

qulonglong EpisodeActionListPrivate::timestamp() const {
	return m_timestamp;
}

void EpisodeActionListPrivate::error ( QNetworkReply::NetworkError error )
{
    this->m_error = error;
    emit q->requestError ( error );
}

// ### End of EpisodeActionListPrivate

EpisodeActionList::EpisodeActionList ( QNetworkReply* reply, QObject* parent ) : QObject ( parent ), d(new EpisodeActionListPrivate(this, reply))
{

}

QVariant EpisodeActionList::episodeActions() const
{
  return d->episodeActions();
}


QList< EpisodeActionPtr > EpisodeActionList::list() const
{
  return d->list();
}

qulonglong EpisodeActionList::timestamp() const
{
	return d->timestamp();
}

EpisodeActionList::~EpisodeActionList()
{
  delete d;
}

#include "EpisodeActionList.moc"


}
