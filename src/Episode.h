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

#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QUrl>
#include <QString>
#include <QNetworkReply>

#include "mygpo_export.h"

namespace mygpo {

class MYGPO_EXPORT Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QUrl podcastUrl READ url CONSTANT)
    Q_PROPERTY(QString podcastTitle READ title CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QUrl website READ website CONSTANT)
    Q_PROPERTY(QUrl mygpoUrl READ mygpoUrl CONSTANT)
    
public:
    Episode();
    Episode(QNetworkReply* reply, QObject* parent = 0);
    Episode(const QUrl& url, const QString& title, const QUrl& podcastUrl, const QString& podcastTitle, const QString& description, const QUrl& website, const QUrl& mygpoUrl, QObject* parent = 0);
    virtual ~Episode();
    Episode(const mygpo::Episode& other);
    Episode operator=(const mygpo::Episode& other);
    QUrl url() const;
    QString title() const;
    QUrl podcastUrl() const;
    QString podcastTitle() const;
    QString description() const;
    QUrl website() const;
    QUrl mygpoUrl() const;
private:
    QUrl m_url;
    QString m_title;
    QUrl m_podcastUrl;
    QString m_podcastTitle;
    QString m_description;
    QUrl m_website;
    QUrl m_mygpoUrl;
    QNetworkReply* m_reply;
    QNetworkReply::NetworkError m_error;
    bool parse(const QVariant& data);
    bool parse(const QByteArray& data);
	
public slots:
    void parseData();
    void error(QNetworkReply::NetworkError error);

signals:
    /**Gets emitted when the data is ready to read*/
    void finished();
    /**Gets emitted when an parse error ocurred*/
    void parseError();
    /**Gets emitted when an request error ocurred*/
    void requestError(QNetworkReply::NetworkError error);
};

}

Q_DECLARE_METATYPE(mygpo::Episode);

#endif // EPISODE_H
