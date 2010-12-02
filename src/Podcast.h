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

#ifndef PODCAST_H
#define PODCAST_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QNetworkReply>

#include "mygpo_export.h"

namespace mygpo {
class PodcastPrivate;
class MYGPO_EXPORT Podcast : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(uint subscribers READ subscribers CONSTANT)
    //Subscribers last Week not yet used because of a Bug in the gpodder.net API
    //Q_PROPERTY(uint subscribersLastWeek READ subscriberstLastWeek CONSTANT)
    Q_PROPERTY(QUrl logoUrl READ logoUrl CONSTANT)
    Q_PROPERTY(QUrl website READ website CONSTANT)
    Q_PROPERTY(QUrl mygpoUrl READ mygpoUrl CONSTANT)
    
public:
    Podcast(QNetworkReply* reply,QObject* parent = 0);
    Podcast(const QUrl& url, const QString& title, const QString& description, int subscribers, const QUrl& logoUrl, const QUrl& website, const QUrl& mygpolink, QObject* parent = NULL);
    Podcast(const QVariant& variant, QObject* parent = 0);
    Podcast(const mygpo::Podcast& other);
    Podcast();
    virtual ~Podcast();
    Podcast operator=(const mygpo::Podcast& other);
    //Getters
    QUrl url() const;
    QString title() const;
    QString description() const;
    uint subscribers() const;
    //const uint subscriberstLastWeek();
    QUrl logoUrl() const;
    QUrl website() const;
    QUrl mygpoUrl() const;

private:
    PodcastPrivate* const d;
    friend class PodcastPrivate;
    bool m_copy;		//true if this object was created by the copy-ctor
signals:
    /**Gets emitted when the data is ready to read*/
    void finished();
    /**Gets emitted when an parse error ocurred*/
    void parseError();
    /**Gets emitted when an request error ocurred*/
    void requestError(QNetworkReply::NetworkError error);
    
private slots:
  void sendFinished();
  void sendParsError();
  void sendRequestError(QNetworkReply::NetworkError error);  
};

}

Q_DECLARE_METATYPE(mygpo::Podcast);

#endif // PODCAST_H
