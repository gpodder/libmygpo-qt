/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2012 Stefan Derkits <stefan@derkits.at>                    *
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

#include "JsonCreatorTest.h"

using namespace mygpo;

JsonCreatorTest::JsonCreatorTest() {
    
}

JsonCreatorTest::~JsonCreatorTest()
{

}

void JsonCreatorTest::initTestCase()
{

}

void JsonCreatorTest::cleanupTestCase()
{

}

void JsonCreatorTest::init()
{

}

void JsonCreatorTest::cleanup()
{

}

void JsonCreatorTest::testDeviceSynchronizationListsToJSON()
{
    QList<QStringList> sync;
    QList<QString> stopSync;
    stopSync.append(QLatin1String("stop1"));
    stopSync.append(QLatin1String("stop2"));
    stopSync.append(QLatin1String("stop3"));
    QStringList sync1;
    sync1.append(QLatin1String("foo"));
    sync1.append(QLatin1String("bar"));
    QStringList sync2;
    sync2.append(QLatin1String("foobar"));
    sync2.append(QLatin1String("barfoo"));
    sync2.append(QLatin1String("foobarfoo"));
    sync2.append(QLatin1String("foobar4"));
    QStringList sync3;
    sync3.append(QLatin1String("alone"));
    QByteArray output = JsonCreator::deviceSynchronizationListsToJSON(sync,stopSync);
    qDebug() << output;
}

QTEST_MAIN(JsonCreatorTest)
