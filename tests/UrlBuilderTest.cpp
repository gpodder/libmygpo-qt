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

#include "UrlBuilderTest.h"

using namespace mygpo;

UrlBuilderTest::UrlBuilderTest() : _server(QLatin1String("gpodder.net")),
        _api2(QLatin1String( "/api/2" )), _api1(QLatin1String("/api/1")) {

}

UrlBuilderTest::~UrlBuilderTest() {

}

void UrlBuilderTest::initTestCase() {

}

void UrlBuilderTest::cleanupTestCase() {

}

void UrlBuilderTest::init() {

}

void UrlBuilderTest::cleanup() {

}

/**
 * Tests for getToplistUrl()
 */
void UrlBuilderTest::testGetToplistUrl() {
    QCOMPARE(UrlBuilder::getToplistUrl(2, UrlBuilder::JSON),
             _server + QLatin1String("/toplist/2.json"));
    QCOMPARE(UrlBuilder::getToplistUrl(2, UrlBuilder::OPML),
             _server + QLatin1String("/toplist/2.opml"));
}

void UrlBuilderTest::testGetToplistUrlHigh() {
    QCOMPARE(UrlBuilder::getToplistUrl(99999999, UrlBuilder::JSON),
             _server + QLatin1String("/toplist/99999999.json"));
    QCOMPARE(UrlBuilder::getToplistUrl(99999999, UrlBuilder::OPML),
             _server + QLatin1String("/toplist/99999999.opml"));
}

void UrlBuilderTest::testGetToplistUrlNegative() {
    QCOMPARE(UrlBuilder::getToplistUrl(-534, UrlBuilder::JSON),
             _server + QLatin1String("/toplist/4294966762.json"));
    QCOMPARE(UrlBuilder::getToplistUrl(-534, UrlBuilder::OPML),
             _server + QLatin1String("/toplist/4294966762.opml"));
}

void UrlBuilderTest::testGetToplistUrlZero() {
    QCOMPARE(UrlBuilder::getToplistUrl(0, UrlBuilder::JSON),
             _server + QLatin1String("/toplist/1.json"));
    QCOMPARE(UrlBuilder::getToplistUrl(0, UrlBuilder::OPML),
             _server + QLatin1String("/toplist/1.opml"));
}

/**
 * Tests for getSuggestionsUrl()
 */
void UrlBuilderTest::testGetSuggestionsUrl() {
    QCOMPARE(UrlBuilder::getSuggestionsUrl(2, UrlBuilder::JSON),
             _server + QLatin1String("/suggestions/2.json"));
    QCOMPARE(UrlBuilder::getSuggestionsUrl(2, UrlBuilder::OPML),
             _server + QLatin1String("/suggestions/2.opml"));
}

void UrlBuilderTest::testGetSuggestionsUrlHigh() {
    QCOMPARE(UrlBuilder::getSuggestionsUrl(99999999, UrlBuilder::JSON),
             _server + QLatin1String("/suggestions/99999999.json"));
    QCOMPARE(UrlBuilder::getSuggestionsUrl(99999999, UrlBuilder::OPML),
             _server + QLatin1String("/suggestions/99999999.opml"));
}

void UrlBuilderTest::testGetSuggestionsUrlNegative() {
    QCOMPARE(UrlBuilder::getSuggestionsUrl(-534, UrlBuilder::JSON),
             _server + QLatin1String("/suggestions/4294966762.json"));
    QCOMPARE(UrlBuilder::getSuggestionsUrl(-534, UrlBuilder::OPML),
             _server + QLatin1String("/suggestions/4294966762.opml"));
}

void UrlBuilderTest::testGetSuggestionsUrlZero() {
    QCOMPARE(UrlBuilder::getSuggestionsUrl(0, UrlBuilder::JSON),
             _server + QLatin1String("/suggestions/1.json"));
    QCOMPARE(UrlBuilder::getSuggestionsUrl(0, UrlBuilder::OPML),
             _server + QLatin1String("/suggestions/1.opml"));
}

/**
 * Tests for getPodcastSearchUrl()
 */
void UrlBuilderTest::testGetPodcastSearchUrl() {
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux"), UrlBuilder::JSON),
             _server + QLatin1String("/search.json?q=linux"));
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux lastfm"), UrlBuilder::JSON),
             _server + QLatin1String("/search.json?q=linux lastfm"));
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux"), UrlBuilder::OPML),
             _server + QLatin1String("/search.opml?q=linux"));
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux lastfm"), UrlBuilder::OPML),
             _server + QLatin1String("/search.opml?q=linux lastfm"));
}

void UrlBuilderTest::testGetPodcastSearchUrlEmpty() {
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String(""), UrlBuilder::JSON),
             _server + QLatin1String("/search.json?q="));
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String(""), UrlBuilder::OPML),
             _server + QLatin1String("/search.opml?q="));
}

void UrlBuilderTest::testGetPodcastSearchUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
             _server + QLatin1String("/search.json?q=!\"§$%$&/()=?ß{}Ä"));
    QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
             _server + QLatin1String("/search.opml?q=!\"§$%$&/()=?ß{}Ä"));
}

/**
 * Tests for getTopTagsUrl()
 */
void UrlBuilderTest::testGetTopTagsUrl() {
    QCOMPARE(UrlBuilder::getTopTagsUrl(2),
             _server + _api2 + QLatin1String("/tags/2.json"));
}

void UrlBuilderTest::testGetTopTagsUrlHigh() {
    QCOMPARE(UrlBuilder::getTopTagsUrl(99999999),
             _server + _api2 + QLatin1String("/tags/99999999.json"));
}

void UrlBuilderTest::testGetTopTagsUrlNegative() {
    QCOMPARE(UrlBuilder::getTopTagsUrl(-534),
             _server + _api2 + QLatin1String("/tags/4294966762.json"));
}

void UrlBuilderTest::testGetTopTagsUrlZero() {
    QCOMPARE(UrlBuilder::getTopTagsUrl(0),
             _server + _api2 + QLatin1String("/tags/1.json"));
}

/**
 * Tests for getPodcastsOfTagUrl()
 */
void UrlBuilderTest::testGetPodcastsOfTagUrl() {
    QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux"), 2),
             _server + _api2 + QLatin1String("/tag/linux/2.json"));
    QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux lastfm"), -534),
             _server + _api2 + QLatin1String("/tag/linux lastfm/4294966762.json"));
}

void UrlBuilderTest::testGetPodcastsOfTagUrlEmpty() {
    QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String(""), 2),
             _server + _api2 + QLatin1String("/tag//2.json"));
}

void UrlBuilderTest::testGetPodcastsOfTagUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), 2),
             _server + _api2 + QLatin1String("/tag/!\"§$%$&/()=?ß{}Ä/2.json"));
}

/**
 * Tests for getPodcastsDataUrl()
 */
void UrlBuilderTest::testGetPodcastDataUrl() {
    QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux")),
             _server + _api2 + QLatin1String("/data/podcast.json?url=linux"));
    QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux lastfm")),
             _server + _api2 + QLatin1String("/data/podcast.json?url=linux lastfm"));
}

void UrlBuilderTest::testGetPodcastDataUrlEmpty() {
    QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("")),
             _server + _api2 + QLatin1String("/data/podcast.json?url="));
}

void UrlBuilderTest::testGetPodcastDataUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä")),
             _server + _api2 + QLatin1String("/data/podcast.json?url=!\"§$%$&/()=?ß{}Ä"));
}

/**
 * Tests for getEpisodeDataUrl()
 */
void UrlBuilderTest::testGetEpisodeDataUrl() {
    QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast1"), QLatin1String("linux")),
             _server + _api2 + QLatin1String("/data/episode.json?podcast=podcast1&url=linux"));
    QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm")),
             _server + _api2 + QLatin1String("/data/episode.json?podcast=podcast2&url=linux lastfm"));
}

void UrlBuilderTest::testGetEpisodeDataUrlEmpty() {
    QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String(""), QLatin1String("")),
             _server + _api2 + QLatin1String("/data/episode.json?podcast=&url="));
}

void UrlBuilderTest::testGetEpisodeDataUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä")),
             _server + _api2 + QLatin1String("/data/episode.json?podcast=ÖÄÜ&url=!\"§$%$&/()=?ß{}Ä"));
}

/**
 * Tests for getFavEpisodesUrl()
 */
void UrlBuilderTest::testGetFavEpisodesUrl() {
    QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux")),
             _server + _api2 + QLatin1String("/favorites/linux.json"));
    QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux lastfm")),
             _server + _api2 + QLatin1String("/favorites/linux lastfm.json"));
}

void UrlBuilderTest::testGetFavEpisodesUrlEmpty() {
    QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("")),
             _server + _api2 + QLatin1String("/favorites/.json"));
}

void UrlBuilderTest::testGetFavEpisodesUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä")),
             _server + _api2 + QLatin1String("/favorites/!\"§$%$&/()=?ß{}Ä.json"));
}

/**
 * Test for getAddRemoveSubUrl()
 */
void UrlBuilderTest::testGetAddRemoveSubUrl() {
    QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast1"), QLatin1String("linux")),
             _server + _api1 + QLatin1String("/subscriptions/podcast1/linux.json"));
    QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm")),
             _server + _api1 + QLatin1String("/subscriptions/podcast2/linux lastfm.json"));
}

void UrlBuilderTest::testGetAddRemoveSubUrlEmpty() {
    QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String(""), QLatin1String("")),
             _server + _api1 + QLatin1String("/subscriptions//.json"));
}

void UrlBuilderTest::testGetAddRemoveSubUrlSpecialCharacters() {
    QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä")),
             _server + _api1 + QLatin1String("/subscriptions/ÖÄÜ/!\"§$%$&/()=?ß{}Ä.json"));
}

QTEST_MAIN(UrlBuilderTest)
