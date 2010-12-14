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

#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QNetworkReply>

#include "mygpo_export.h"

namespace mygpo {
class TagPrivate;
class MYGPO_EXPORT Tag : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString tag READ tag CONSTANT)
    Q_PROPERTY(uint usage READ usage CONSTANT)

public:
    Tag(QString tag, uint usage, QObject* parent = 0);
    Tag(const QVariant& variant, QObject* parent = 0);
    Tag(const Tag& other);
    Tag();
    virtual ~Tag();
    Tag operator=(const Tag& other);
    const QString tag() const;
    uint usage() const;
private:
    TagPrivate* const d;
    friend class TagPrivate;
};

}

Q_DECLARE_METATYPE(mygpo::Tag);

#endif // TAG_H
