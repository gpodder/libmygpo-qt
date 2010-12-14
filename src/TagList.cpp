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
#include <QSharedPointer>

#include "TagList.h"

namespace mygpo {

class TagListPrivate : public QObject
{
    Q_OBJECT
public:
    TagListPrivate ( TagList* qq, QNetworkReply* reply, QObject* parent = 0 );
    TagListPrivate ( TagList* qq, TagListPrivate* pp, QObject* parent = 0);

    QList<Tag> list() const;
    QVariant tags() const;
private:
    TagList* const q;
    QSharedPointer<QNetworkReply> m_reply;
    QVariant m_tags;

    QNetworkReply::NetworkError m_error;

    bool parse ( const QVariant& data );
    bool parse ( const QByteArray& data );
private slots:
    void parseData();
    void error(QNetworkReply::NetworkError error);
};

TagListPrivate::TagListPrivate ( TagList* qq, QNetworkReply* reply, QObject* parent ) : QObject ( parent ), q(qq), m_reply ( reply )
{
    QObject::connect ( &(*m_reply),SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( &(*m_reply),SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

TagListPrivate::TagListPrivate ( TagList* qq, TagListPrivate* pp, QObject* parent) : QObject (parent), q(qq), m_reply(pp->m_reply),
	     m_tags(pp->m_tags), m_error(pp->m_error)
{
    QObject::connect ( &(*m_reply),SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( &(*m_reply),SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

QList<Tag> TagListPrivate::list() const
{
    QList<Tag> list;
    QVariantList varList = m_tags.toList();
    foreach ( QVariant var,varList )
    {
        list.append ( var.value<mygpo::Tag>() );
    }
    return list;
}

QVariant TagListPrivate::tags() const
{
    return m_tags;
}

bool TagListPrivate::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::List))
        return false;
    QVariantList varList = data.toList();
    QVariantList tagList;
    foreach (QVariant var,varList)
    {
        QVariant v;
        v.setValue<mygpo::Tag>(Tag(var));
        tagList.append(v);
    }
    m_tags = QVariant( tagList);
    return true;
}

bool TagListPrivate::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      ok = (parse( variant ));
    }
    return ok;
}


void TagListPrivate::parseData()
{
    QJson::Parser parser;
    if (parse( m_reply->peek( m_reply->bytesAvailable() ) ) ) {
      emit q->finished();
    } else {
      emit q->parseError();
    }
}

void TagListPrivate::error(QNetworkReply::NetworkError error)
{
    this->m_error = error;
    emit q->requestError(error);
}




TagList::TagList ( QNetworkReply* reply, QObject* parent) : d(new TagListPrivate(this,reply))
{

}
TagList::TagList ( const TagList& other ) : QObject(other.parent()), d(new TagListPrivate(this,other.d))
{

}
TagList::~TagList()
{
	delete d;
}

QList<Tag> TagList::list() const
{
	return d->list();
}
QVariant TagList::tags() const
{
	return d->tags();
}


}

#include "../build/src/TagList.moc"
