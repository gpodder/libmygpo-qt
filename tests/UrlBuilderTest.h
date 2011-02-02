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

#ifndef URLBUILDERTEST_H_
#define URLBUILDERTEST_H_

#include <QtTest/QtTest>
#include "UrlBuilder.h"

namespace mygpo {

/**
 * This class tests all public methods of the UrlBuilder class
 */
class UrlBuilderTest : public QObject {
	Q_OBJECT
public:
  UrlBuilderTest();
  virtual ~UrlBuilderTest();
private slots:
  void initTestCase();
  void cleanupTestCase();
  void init();
  void cleanup();

  /**
   * Tests for getToplistUrl()
   */
  void testGetToplistUrl();
  void testGetToplistUrlHigh();
  void testGetToplistUrlNegative();
  void testGetToplistUrlZero();


  /**
   * Tests for getSuggestionsUrl()
   */
  void testGetSuggestionsUrl();
  void testGetSuggestionsUrlHigh();
  void testGetSuggestionsUrlNegative();
  void testGetSuggestionsUrlZero();

  /**
   * Tests for getPodcastSearchUrl()
   */
  void testGetPodcastSearchUrl();
  void testGetPodcastSearchUrlEmpty();
  void testGetPodcastSearchUrlSpecialCharacters();

  /**
   * Tests for getTopTagsUrl()
   */
  void testGetTopTagsUrl();
  void testGetTopTagsUrlHigh();
  void testGetTopTagsUrlNegative();
  void testGetTopTagsUrlZero();

  /**
   * Tests for getPodcastsOfTagUrl()
   */
  void testGetPodcastsOfTagUrl();
  void testGetPodcastsOfTagUrlEmpty();
  void testGetPodcastsOfTagUrlSpecialCharacters();

  /**
   * Tests for getPodcastDataUrl()
   */
  void testGetPodcastDataUrl();
  void testGetPodcastDataUrlEmpty();
  void testGetPodcastDataUrlSpecialCharacters();

  /**
   * Tests for getEpisodeDataUrl()
   */
  void testGetEpisodeDataUrl();
  void testGetEpisodeDataUrlEmpty();
  void testGetEpisodeDataUrlSpecialCharacters();

  /**
   * Tests for getFavEpisodesUrl()
   */
  void testGetFavEpisodesUrl();
  void testGetFavEpisodesUrlEmpty();
  void testGetFavEpisodesUrlSpecialCharacters();

  /**
   * Test for getAddRemoveSubUrl()
   */
  void testGetAddRemoveSubUrl();
  void testGetAddRemoveSubUrlEmpty();
  void testGetAddRemoveSubUrlSpecialCharacters();

  /** These constans must be equal to the constants defined for UrlBuilder */
private:
  const QString m_server;
  const QString m_api2;
};

}

#endif /* URLBUILDERTEST_H_ */
