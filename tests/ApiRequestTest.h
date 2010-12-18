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
#ifndef APIREQUESTTEST_H_
#define APIREQUESTTEST_H_

#include <QtTest/QtTest>
#include "ApiRequest.h"

namespace mygpo {

class ApiRequestTest : public QObject {
	Q_OBJECT
public:
  ApiRequestTest();
  virtual ~ApiRequestTest();

private:
    ApiRequest m_req;
    bool m_ok;
  
private slots:
  void initTestCase();
  void cleanupTestCase();
  void init();
  void cleanup();
  
  void testToplist();
  void testSuggestions();
  void testPodcastsOfTag();
  void testPodcastData();
  void testEpisodeData();
  void testFavoriteEpisodes();
  void testTopTags();
  //void testAddRemoveSubscriptionsAdd();
  //void testAddRemoveSubscriptionsRemove();
  
public slots:
  void error();
  void error(QNetworkReply::NetworkError error);
};

}

#endif /* APIREQUESTTEST_H_ */
