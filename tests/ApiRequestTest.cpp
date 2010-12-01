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

#include "ApiRequestTest.h"

using namespace mygpo;

ApiRequestTest::ApiRequestTest() : m_req( QLatin1String("ase23"),QLatin1String("csf-sepm") )
{
  
}

ApiRequestTest::~ApiRequestTest()
{

}

void ApiRequestTest::init()
{
  m_ok = true;
}

void ApiRequestTest::initTestCase()
{

}

void ApiRequestTest::cleanup()
{

}

void ApiRequestTest::cleanupTestCase()
{

}



void ApiRequestTest::testToplist()
{
  QEventLoop loop;
  PodcastList ret = m_req.toplist(10);
  QObject::connect(&ret,SIGNAL(parseError()), this, SLOT(error()));
  QObject::connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
  loop.connect(&ret,SIGNAL(finished()),SLOT(quit()));
  loop.connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
  loop.connect(&ret,SIGNAL(parseError()),SLOT(quit()));
  loop.exec();
  QCOMPARE(ret.list().size(),10);
}

void ApiRequestTest::testSuggestions()
{
  QEventLoop loop;
  PodcastList ret = m_req.toplist(5);
  QObject::connect(&ret,SIGNAL(parseError()), this, SLOT(error()));
  QObject::connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
  loop.connect(&ret,SIGNAL(finished()),SLOT(quit()));
  loop.connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
  loop.connect(&ret,SIGNAL(parseError()),SLOT(quit()));
  loop.exec();
  QVERIFY(ret.list().size() <= 5);
  QVERIFY(m_ok);
}

void ApiRequestTest::testPodcastsOfTag()
{
  QEventLoop loop;
  PodcastList ret = m_req.podcastsOfTag(3,QLatin1String("fm4"));
  QObject::connect(&ret,SIGNAL(parseError()), this, SLOT(error()));
  QObject::connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
  loop.connect(&ret,SIGNAL(finished()),SLOT(quit()));
  loop.connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
  loop.connect(&ret,SIGNAL(parseError()),SLOT(quit()));
  loop.exec();
  QVERIFY(ret.list().size() <= 3);
  QVERIFY(m_ok);
}


void ApiRequestTest::error()
{
  m_ok = false;
}

void ApiRequestTest::error(QNetworkReply::NetworkError error)
{
  m_ok = false;
}





QTEST_MAIN(ApiRequestTest)
