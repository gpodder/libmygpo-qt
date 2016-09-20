/***************************************************************************
 * This file is part of libmygpo-qt                                         *
 * Copyright (c) 2012 Stefan Derkits <stefan@derkits.at>                    *
 * Copyright (c) 2012 Felix Winter <ixos01@gmail.com>                       *
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

void JsonCreatorTest::testAddRemoveSubsToJSON()
{
  QList<QUrl> add;
  QList<QUrl> remove;
  QByteArray output;

  // test with empty lists
  output = JsonCreator::addRemoveSubsToJSON(add, remove);
  QString outString1 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected1( QLatin1String( "{\"add\":[],\"remove\":[]}" ) );
  QCOMPARE(outString1, expected1 );

  // test with full lists
  add.append(QUrl(QLatin1String("http://example.com/feed.rss")));
  add.append(QUrl(QLatin1String("http://example.org/podcast.php")));

  remove.append(QUrl(QLatin1String("http://example.org/podcast.php")));

  output = JsonCreator::addRemoveSubsToJSON(add, remove);
  QString outString2 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected2( QLatin1String("{\"add\":[\"http://example.com/feed.rss\",\"http://example.org/podcast.php\"],\"remove\":[\"http://example.org/podcast.php\"]}"));
  QCOMPARE(outString2, expected2 );
}

void JsonCreatorTest::testSaveSettingsToJSON()
{
  QMap<QString, QVariant> set;
  QList<QString> remove;
  QByteArray output;

  // test with empty map/list
  output = JsonCreator::saveSettingsToJSON(set, remove);
  QString outString1 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected1( QLatin1String( "{\"remove\":[],\"set\":{}}" ) );

  QCOMPARE( outString1, expected1 );

  // test with different settings (String, DateTime, Integer)
  set.insert(QLatin1String("setting4"), QLatin1String("stringvalue"));
  set.insert(QLatin1String("setting5"), QDateTime::fromString(QLatin1String("M1d1y9800:01:02"),
							      QLatin1String("'M'M'd'd'y'yyhh:mm:ss")));
  set.insert(QLatin1String("setting6"), 4);

  remove.append(QLatin1String("setting1"));
  remove.append(QLatin1String("setting2"));

  output = JsonCreator::saveSettingsToJSON(set, remove);
  QString outString2 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected2( QLatin1String( "{\"remove\":[\"setting1\",\"setting2\"],\"set\":{\"setting4\":\"stringvalue\",\"setting5\":\"1998-01-01T00:01:02\",\"setting6\":4}}" ) );

  QCOMPARE( outString2, expected2 );

}

void JsonCreatorTest::testEpisodeActionListToJSON()
{
  QList<EpisodeActionPtr> episodeActions;
  QByteArray output;

  // test with empty list
  output = JsonCreator::episodeActionListToJSON(episodeActions);
  QString outString1 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected1( QLatin1String( "[]" ) );
  QCOMPARE( outString1, expected1 );


  // test with some values
  qulonglong date1 = QDateTime::fromString(QLatin1String("M1d1y9800:01:02"),QLatin1String("'M'M'd'd'y'yyhh:mm:ss")).toMSecsSinceEpoch();
  qulonglong date2 =  QDateTime::fromString(QLatin1String("M1d1y2012:01:02"),QLatin1String("'M'M'd'd'y'yyhh:mm:ss")).toMSecsSinceEpoch();
  
  EpisodeActionPtr episode(new EpisodeAction(QUrl(QLatin1String("http://podcast.url")), QUrl(QLatin1String("http://episode.url")), QLatin1String("device1"), EpisodeAction::Download, date1));
  EpisodeActionPtr episode2(new EpisodeAction(QUrl(QLatin1String("http://podcast2.url")), QUrl(QLatin1String("http://episode2.url")), QLatin1String("device3"), EpisodeAction::Delete, date2, 400000, 40000, 40000));
  EpisodeActionPtr episode3 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am")), QUrl(QLatin1String("http://www.podtrac.com")), QLatin1String("foodev"), EpisodeAction::New, date1, 1, 2, 3));
  EpisodeActionPtr episode4 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am")), QUrl(QLatin1String("http://www.podtrac.com")), QLatin1String("foodev"), EpisodeAction::Play, date2));
  EpisodeActionPtr episode5 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am")), QUrl(QLatin1String("http://www.podtrac.com")), QLatin1String("foodev"), EpisodeAction::Play, date1, 10, 123, 321));
  EpisodeActionPtr episode6 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am")), QUrl(QLatin1String("http://www.podtrac.com")), QLatin1String("foodev"), EpisodeAction::Play, date1, 10 ));

  episodeActions << episode << episode2 << episode3 << episode4 << episode5 << episode6;

  output = JsonCreator::episodeActionListToJSON(episodeActions);
  QString outString2 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected2( QLatin1String( "[{\"action\":\"download\",\"device\":\"device1\",\"episode\":\"http://episode.url\",\"podcast\":\"http://podcast.url\",\"timestamp\":\"1998-01-01T00:01:02\"},{\"action\":\"delete\",\"device\":\"device3\",\"episode\":\"http://episode2.url\",\"podcast\":\"http://podcast2.url\",\"timestamp\":\"1920-01-01T12:01:02\"},{\"action\":\"new\",\"device\":\"foodev\",\"episode\":\"http://www.podtrac.com\",\"podcast\":\"http://leo.am\",\"timestamp\":\"1998-01-01T00:01:02\"},{\"action\":\"play\",\"device\":\"foodev\",\"episode\":\"http://www.podtrac.com\",\"podcast\":\"http://leo.am\",\"timestamp\":\"1920-01-01T12:01:02\"},{\"action\":\"play\",\"device\":\"foodev\",\"episode\":\"http://www.podtrac.com\",\"podcast\":\"http://leo.am\",\"position\":123,\"started\":10,\"timestamp\":\"1998-01-01T00:01:02\",\"total\":321},{\"action\":\"play\",\"device\":\"foodev\",\"episode\":\"http://www.podtrac.com\",\"podcast\":\"http://leo.am\",\"position\":10,\"timestamp\":\"1998-01-01T00:01:02\"}]" ) );

  QCOMPARE(outString2, expected2 );
}

void JsonCreatorTest::testRenameDeviceStringToJSON()
{
  QString caption;
  QString type;
  QByteArray output;
  
  // test with empty values
  output = JsonCreator::renameDeviceStringToJSON(caption, type);
  QString outString1 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected1( QLatin1String( "{\"caption\":\"\",\"type\":\"\"}" ) );

  QCOMPARE(outString1, expected1 );

  // test with some values
  caption = QLatin1String("caption1");
  type = QLatin1String("type1");

  output = JsonCreator::renameDeviceStringToJSON(caption, type);
  QString outString2 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected2( QLatin1String( "{\"caption\":\"caption1\",\"type\":\"type1\"}" ) );

  QCOMPARE( outString2, expected2 );

}

void JsonCreatorTest::testDeviceSynchronizationListsToJSON()
{
  QList<QStringList> sync;
  QList<QString> sync1;
  QList<QString> sync2;
  QList<QString> sync3;

  QList<QString> stopSync;

  QByteArray output;

  // test with empty lists
  output = JsonCreator::deviceSynchronizationListsToJSON(sync, stopSync);
  QString outString1 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected1( QLatin1String( "{\"synchronize\":[],\"stop-synchronize\":[]}" ) );
  QCOMPARE( outString1, expected1 );

  // test with full lists
  sync1.append(QLatin1String("foo"));
  sync1.append(QLatin1String("bar"));

  sync2.append(QLatin1String("foobar"));
  sync2.append(QLatin1String("barfoo"));
  sync2.append(QLatin1String("foobarfoo"));
  sync2.append(QLatin1String("foobar4"));

  sync.append(sync1);
  sync.append(sync2);
  sync.append(sync3);
  
  stopSync.append(QLatin1String("stop1"));
  stopSync.append(QLatin1String("stop2"));
  stopSync.append(QLatin1String("stop3"));

  output = JsonCreator::deviceSynchronizationListsToJSON(sync, stopSync);
  QString outString2 = QString::fromLatin1( output ).replace( QLatin1String(" "), QLatin1String("") );
  QString expected2( QLatin1String( "{\"synchronize\":[[\"foo\",\"bar\"],[\"foobar\",\"barfoo\",\"foobarfoo\",\"foobar4\"],[]],\"stop-synchronize\":[\"stop1\",\"stop2\",\"stop3\"]}" ) );
  QCOMPARE( outString2, expected2 );
}

QTEST_MAIN(JsonCreatorTest)
