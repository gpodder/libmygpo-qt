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

#include <QApplication>
#include <iostream>
#include <QTimer>
#include <QtGui>
#include <QEventLoop>


#include <PodcastList.h>
#include <EpisodeList.h>
#include <TagList.h>
#include <ApiRequest.h>

using namespace mygpo;

void printTitle(const QString& title) {
    QString fillLine(80, QLatin1Char('#'));

	qDebug() << fillLine;
    qDebug() << title;
    qDebug() << fillLine;
}

void printPodcastList(const PodcastList& podcastList) {
	QList<Podcast> list;
    QList<Podcast>::const_iterator iterator;

    list = podcastList.list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
    	qDebug() << "title:\t" << iterator->title();
    	qDebug() << "url:\t" << iterator->url();
    	qDebug() << "";
    }
    qDebug() << "";
}

void printPodcast(const Podcast& podcast) {
	qDebug() << "title:\t" << podcast.title();
	qDebug() << "url:\t" << podcast.url();
	qDebug() << "description:\t" << podcast.description();
	qDebug() << "";
}

void printEpisode(const Episode& episode) {
	qDebug() << "title:\t" << episode.title();
	qDebug() << "url:\t" << episode.url();
	qDebug() << "";
}

void printEpisodeList(const EpisodeList& episodeList) {
	QList<Episode> list;
    QList<Episode>::const_iterator iterator;

    list = episodeList.list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
    	qDebug() << "title:\t" << iterator->title();
    	qDebug() << "url:\t" << iterator->url();
    	qDebug() << "";
    }
    qDebug() << "";
}

void printTagList(const TagList& tagList) {
	QList<Tag> list;
    QList<Tag>::const_iterator iterator;

    list = tagList.list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
    	qDebug() << iterator->tag();
    }
    qDebug() << "";
}

void printAddRemoveResult(const AddRemoveResult& addRemoveResult) {
	qDebug() << "timestamp:\t" << addRemoveResult.timestamp();

	QList< QPair<QUrl, QUrl> > pairlist = addRemoveResult.updateUrlsList();

    for (int i=0; i<pairlist.size(); i++)
    {
        QPair<QUrl, QUrl> pair = pairlist.at(i);
        qDebug() << pair.first;
        qDebug() << pair.second;
    }

    qDebug() << "";
}


/**
 * A simple example application which calls all methods provided by the ApiRequest class
 */
int main(int argc, char **argv)
{
	QApplication app(argc, argv, true);
	ApiRequest req("ase23", "csf-sepm");
    QEventLoop loop;
    QNetworkReply *reply;

    //
    // QNetworkReply* toplistOpml(uint count);
    //
    reply = req.toplistOpml(1);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast toplists (OPML) [toplistOpml(1)]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // QNetworkReply* searchOpml(const QString& query);
    //
    reply = req.searchOpml(QLatin1String("linux outlaws"));

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Searching for podcasts (OPML) [searchOpml(\"linux outlaws\")]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // QNetworkReply* suggestionsOpml(uint count);
    //
    reply = req.suggestionsOpml(2);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast suggestions (OPML) [suggestionsOpml(2)]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // PodcastList toplist(uint count);
    //
    PodcastList topList(req.toplist(1));

    loop.connect(&topList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast toplists [toplist(1)]"));
    printPodcastList(topList);

    //
    // PodcastList search(const QString& query);
    //
    PodcastList searchList(req.search(QLatin1String("linux outlaws")));

    loop.connect(&searchList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Searching for podcasts [search(\"linux outlaws\")]"));
    printPodcastList(searchList);

    //
    // PodcastList suggestions(uint count);
    //
    PodcastList suggestionsList(req.suggestions(2));

    loop.connect(&suggestionsList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast suggestions [suggestions(2)]"));
    printPodcastList(suggestionsList);

    //
    // PodcastList podcastsOfTag(uint count, const QString& tag);
    //
    PodcastList podcastsOfTagList(req.podcastsOfTag(1,QLatin1String("linux")));

    loop.connect(&podcastsOfTagList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Podcasts of a Tag [podcastsOfTag(1,\"linux\")]"));
    printPodcastList(podcastsOfTagList);

    //
    // Podcast podcastData (const QUrl& podcasturl);
    //
    Podcast podcast(req.podcastData(QUrl(QLatin1String("http://surl.dk/7k5"))));

    loop.connect(&podcast, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Podcast Data [podcastData(\"http://surl.dk/7k5\")]"));
    printPodcast(podcast);

    //
    // Episode episodeData(const QUrl& podcasturl, const QUrl& episodeurl);
    //
    Episode episode(req.episodeData(QUrl(QLatin1String("http://surl.dk/7k5")), QUrl(QLatin1String("http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3"))));

    loop.connect(&episode, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Episode Data [episodeData(\"http://surl.dk/7k5\",\"http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3\")]"));
    printEpisode(episode);

    //
    // EpisodeList favoriteEpisodes(const QString& username);
    //
    EpisodeList episodeList(req.favoriteEpisodes(QLatin1String("ase23")));

    loop.connect(&episodeList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Listing Favorite Episodes [favoriteEpisodes(\"ase23\")]"));
    printEpisodeList(episodeList);

    //
    // TagList topTags(uint count);
    //
    TagList tagList(req.topTags(3));

    loop.connect(&tagList, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Top Tags [topTags(3)]"));
    printTagList(tagList);

    //
    // AddRemoveResult addRemoveSubscriptions(const QString& username, const QString& device, const QList<QUrl>& add, const QList<QUrl>& remove);
    //
    QList<QUrl> add;
    QList<QUrl> remove;
    add << QUrl(QLatin1String("http://feeds.rucast.net/radio-t"));
    remove << QUrl(QLatin1String("http://hackermedley.org/feed/podcast/"));

    AddRemoveResult addRemoveResult(req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), add, remove));

    loop.connect(&addRemoveResult, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Add/remove subscriptions [addRemoveSubscriptions(\"ase23\", \"dev0\", {\"http://feeds.rucast.net/radio-t\"}, {http://hackermedley.org/feed/podcast/}]"));
    printAddRemoveResult(addRemoveResult);

    AddRemoveResult addRemoveResult2(req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), remove, add));

    loop.connect(&addRemoveResult2, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Add/remove subscriptions2 [addRemoveSubscriptions(\"ase23\", \"dev0\", {http://hackermedley.org/feed/podcast/}, {\"http://feeds.rucast.net/radio-t\"}]"));
    printAddRemoveResult(addRemoveResult2);


    //
    // Copy objects and reicieve signals
    //
    printTitle(QLatin1String("Copy objects, and reicieve signals:"));

    qDebug() << "EpisodeList";
    EpisodeList ret1 = req.favoriteEpisodes(QLatin1String("ase23"));
        EpisodeList ret = ret1;
        loop.connect(&ret,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&ret,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "List1 size: " << ret.list().size();
        qDebug() << "List2 size: " << ret1.list().size();
    qDebug() << "";

    qDebug() << "Episode";
    Episode episode1 = req.episodeData(QUrl(QLatin1String("http://surl.dk/7k5")), QUrl(QLatin1String("http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3")));
        Episode episode2 = episode1;
        loop.connect(&episode2,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&episode2,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&episode2,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "Episode1: " << episode1.title();
        qDebug() << "Episode2: " << episode2.title();
    qDebug() << "";

    qDebug() << "PodcastList";
    PodcastList podcastList1 = req.toplist(1);
        PodcastList podcastList2 = podcastList1;
        loop.connect(&podcastList1,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&podcastList1,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&podcastList1,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "PodcastList1 size: " << podcastList1.list().size();
        qDebug() << "PodcastList2 size: " << podcastList1.list().size();
    qDebug() << "";

    qDebug() << "Podcast";
    Podcast podcast1 = req.podcastData(QUrl(QLatin1String("http://surl.dk/7k5")));
    	Podcast podcast2 = podcast1;
        loop.connect(&podcast2,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&podcast2,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&podcast2,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "Podcast1: " << podcast1.title();
        qDebug() << "Podcast2: " << podcast2.title();
    qDebug() << "";

    qDebug() << "TagList";
    TagList tagList1 = req.topTags(3);
    TagList tagList2 = tagList1;
        loop.connect(&tagList2,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&tagList2,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&tagList2,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "TagList1 size: " << tagList1.list().size();
        qDebug() << "TagList2 size: " << tagList2.list().size();
    qDebug() << "";

    qDebug() << "AddRemoveResult";
    /*QList<QUrl> add2;
    QList<QUrl> remove2;
    ad << QUrl(QLatin1String(""));
    rem << QUrl(QLatin1String(""));*/
    AddRemoveResult addRemove1 = req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), remove, add);
    AddRemoveResult addRemove2 = addRemove1;
        loop.connect(&addRemove2,SIGNAL(finished()),SLOT(quit()));
        loop.connect(&addRemove2,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
        loop.connect(&addRemove2,SIGNAL(parseError()),SLOT(quit()));
        loop.exec();
        qDebug() << "AddRemoveResult1: " << addRemove1.timestamp();
        qDebug() << "AddRemoveResult2: " << addRemove2.timestamp();
    qDebug() << "";

    return 0;
}
