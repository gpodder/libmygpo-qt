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

UrlBuilderTest::UrlBuilderTest() : _server(QLatin1String("http://gpodder.net")),
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
			QUrl(_server + QLatin1String("/toplist/2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getToplistUrl(2, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/toplist/2.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetToplistUrlHigh() {
	QCOMPARE(UrlBuilder::getToplistUrl(99999999, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/toplist/99999999.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getToplistUrl(99999999, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/toplist/99999999.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetToplistUrlNegative() {
	QCOMPARE(UrlBuilder::getToplistUrl(-534, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/toplist/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getToplistUrl(-534, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/toplist/1.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetToplistUrlZero() {
	QCOMPARE(UrlBuilder::getToplistUrl(0, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/toplist/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getToplistUrl(0, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/toplist/1.opml"), QUrl::TolerantMode));
}

/**
 * Tests for getSuggestionsUrl()
 */
void UrlBuilderTest::testGetSuggestionsUrl() {
	QCOMPARE(UrlBuilder::getSuggestionsUrl(2, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/suggestion/2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getSuggestionsUrl(2, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/suggestion/2.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetSuggestionsUrlHigh() {
	QCOMPARE(UrlBuilder::getSuggestionsUrl(99999999, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/suggestion/99999999.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getSuggestionsUrl(99999999, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/suggestion/99999999.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetSuggestionsUrlNegative() {
	QCOMPARE(UrlBuilder::getSuggestionsUrl(-534, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/suggestion/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getSuggestionsUrl(-534, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/suggestion/1.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetSuggestionsUrlZero() {
	QCOMPARE(UrlBuilder::getSuggestionsUrl(0, UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/suggestion/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getSuggestionsUrl(0, UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/suggestion/1.opml"), QUrl::TolerantMode));
}

/**
 * Tests for getPodcastSearchUrl()
 */
void UrlBuilderTest::testGetPodcastSearchUrl() {
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux"), UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/search.json?q=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux lastfm"), UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/search.json?q=linux lastfm"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux"), UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/search.opml?q=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("linux lastfm"), UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/search.opml?q=linux lastfm"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastSearchUrlEmpty() {
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String(""), UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/search.json?q="), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String(""), UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/search.opml?q="), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastSearchUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
			QUrl(_server + QLatin1String("/search.json?q=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastSearchUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
			QUrl(_server + QLatin1String("/search.opml?q=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
}

/**
 * Tests for getTopTagsUrl()
 */
void UrlBuilderTest::testGetTopTagsUrl() {
	QCOMPARE(UrlBuilder::getTopTagsUrl(2, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tags/2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getTopTagsUrl(2, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tags/2.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetTopTagsUrlHigh() {
	QCOMPARE(UrlBuilder::getTopTagsUrl(99999999, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tags/99999999.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getTopTagsUrl(99999999, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tags/99999999.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetTopTagsUrlNegative() {
	QCOMPARE(UrlBuilder::getTopTagsUrl(-534, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tags/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getTopTagsUrl(-534, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tags/1.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetTopTagsUrlZero() {
	QCOMPARE(UrlBuilder::getTopTagsUrl(0, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tags/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getTopTagsUrl(0, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tags/1.opml"), QUrl::TolerantMode));
}

/**
 * Tests for getPodcastsOfTagUrl()
 */
void UrlBuilderTest::testGetPodcastsOfTagUrl() {
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux"), 2, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tag/linux/2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux lastfm"), -534, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tag/linux lastfm/1.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux"), 999999, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tag/linux/999999.opml"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("linux lastfm"), 0, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tag/linux lastfm/1.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastsOfTagUrlEmpty() {
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String(""), 2, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tag//2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String(""), 0, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tag//1.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastsOfTagUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), 2, UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/tag/!\"§$%$&/()=?ß{}Ä/2.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastsOfTagUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), 0, UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/tag/!\"§$%$&/()=?ß{}Ä/1.opml"), QUrl::TolerantMode));
}

/**
 * Tests for getPodcastsDataUrl()
 */
void UrlBuilderTest::testGetPodcastDataUrl() {
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.json?url=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux lastfm"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.json?url=linux lastfm"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.opml?url=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("linux lastfm"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.opml?url=linux lastfm"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastDataUrlEmpty() {
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String(""), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.json?url="), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String(""), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.opml?url="), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetPodcastDataUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.json?url=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getPodcastDataUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/podcast.opml?url=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
}

/**
 * Tests for getEpisodeDataUrl()
 */
void UrlBuilderTest::testGetEpisodeDataUrl() {
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast1"), QLatin1String("linux"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/episode.json?podcast=podcast1&url=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/episode.json?podcast=podcast2&url=linux lastfm"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast1"), QLatin1String("linux"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/episode.opml?podcast=podcast1&url=linux"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/episode.opml?podcast=podcast2&url=linux lastfm"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetEpisodeDataUrlEmpty() {
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String(""), QLatin1String(""), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/episode.json?podcast=&url="), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String(""), QLatin1String(""), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/episode.opml?podcast=&url="), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetEpisodeDataUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/data/episode.json?podcast=ÖÄÜ&url=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getEpisodeDataUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/data/episode.opml?podcast=ÖÄÜ&url=!\"§$%$&/()=?ß{}Ä"), QUrl::TolerantMode));
}

/**
 * Tests for getFavEpisodesUrl()
 */
void UrlBuilderTest::testGetFavEpisodesUrl() {
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/favorites/linux.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux lastfm"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/favorites/linux lastfm.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/favorites/linux.opml"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("linux lastfm"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/favorites/linux lastfm.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetFavEpisodesUrlEmpty() {
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String(""), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/favorites/.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String(""), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/favorites/.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetFavEpisodesUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
			QUrl(_server + _api2 + QLatin1String("/favorites/!\"§$%$&/()=?ß{}Ä.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getFavEpisodesUrl(QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
			QUrl(_server + _api2 + QLatin1String("/favorites/!\"§$%$&/()=?ß{}Ä.opml"), QUrl::TolerantMode));
}

/**
 * Test for getAddRemoveSubUrl()
 */
void UrlBuilderTest::testGetAddRemoveSubUrl() {
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast1"), QLatin1String("linux"), UrlBuilder::JSON),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/podcast1/linux.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm"), UrlBuilder::JSON),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/podcast2/linux lastfm.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast1"), QLatin1String("linux"), UrlBuilder::OPML),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/podcast1/linux.opml"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("podcast2"), QLatin1String("linux lastfm"), UrlBuilder::OPML),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/podcast2/linux lastfm.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetAddRemoveSubUrlEmpty() {
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String(""), QLatin1String(""), UrlBuilder::JSON),
			QUrl(_server + _api1 + QLatin1String("/subscriptions//.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String(""), QLatin1String(""), UrlBuilder::OPML),
			QUrl(_server + _api1 + QLatin1String("/subscriptions//.opml"), QUrl::TolerantMode));
}

void UrlBuilderTest::testGetAddRemoveSubUrlSpecialCharacters() {
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::JSON),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/ÖÄÜ/!\"§$%$&/()=?ß{}Ä.json"), QUrl::TolerantMode));
	QCOMPARE(UrlBuilder::getAddRemoveSubUrl(QLatin1String("ÖÄÜ"), QLatin1String("!\"§$%$&/()=?ß{}Ä"), UrlBuilder::OPML),
			QUrl(_server + _api1 + QLatin1String("/subscriptions/ÖÄÜ/!\"§$%$&/()=?ß{}Ä.opml"), QUrl::TolerantMode));
}

QTEST_MAIN(UrlBuilderTest)
#include "moc_UrlBuilderTest.cpp"
