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

#include <QVariant>
#include <QList>
#include <QUrl>
#include <QString>

#include <serializer.h>
#include <parser.h>

#include "JsonParser.h"

using namespace mygpo;

QByteArray JsonParser::addRemoveSubsToJSON(const QList< QUrl >& add, const QList< QUrl >& remove)
{
    QJson::Serializer serializer;
    QVariantMap jsonData;
    QVariant addVar(urlListToQVariantList(add));
    QVariant removeVar(urlListToQVariantList(remove));
    jsonData.insert(QString(QLatin1String("add")),addVar);
    jsonData.insert(QString(QLatin1String("remove")),removeVar);
    QByteArray jsonByteArray = serializer.serialize(QVariant(jsonData));
    return jsonByteArray;
}

QByteArray JsonParser::saveSettingsToJSON(const QMap< QString, QString >& set, const QList< QString >& remove)
{
    QJson::Serializer serializer;
    QVariantMap jsonData;
    QVariant setVar(stringMapToQVariantMap(set));
    QVariant removeVar(stringListToQVariantList(remove));
    jsonData.insert(QString(QLatin1String("set")),setVar);
    jsonData.insert(QString(QLatin1String("remove")),removeVar);
    QByteArray jsonByteArray = serializer.serialize(QVariant(jsonData));
    return jsonByteArray;
}

QVariantList JsonParser::urlListToQVariantList(const QList< QUrl >& urls)
{
    QVariantList list;
    foreach (const QUrl& url,urls) {
        QVariant var(url.toString());
        list.append(var);
    }
    return list;
}

QVariantList JsonParser::stringListToQVariantList(const QList< QString >& strings)
{
    QVariantList list;
    foreach (const QString& str,strings) {
        QVariant var(str);
        list.append(var);
    }
    return list;
}

QVariantMap mygpo::JsonParser::stringMapToQVariantMap(const QMap< QString, QString >& stringmap)
{
    QVariantMap map;
    foreach(const QString& str,stringmap.keys() ) {
        map.insert(str,QVariant(stringmap.value(str)));
    }
    return map;
}

QByteArray mygpo::JsonParser::renameDeviceStringToJSON(const QString& caption, const QString& type ) 
{
  QJson::Serializer serializer;
  QVariantMap jsonData;
  QVariant captionVar(caption);
  QVariant typeVar(type);
  jsonData.insert(QString(QLatin1String("caption")),captionVar);
  jsonData.insert(QString(QLatin1String("type")),typeVar);
  QByteArray jsonByteArray = serializer.serialize(QVariant(jsonData));
  return jsonByteArray;   
}
