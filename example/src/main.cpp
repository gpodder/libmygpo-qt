/***************************************************************************
 * This file is part of libmygpo-qt                                         *
 * Copyright (c) 2010 - 2011 Stefan Derkits <stefan@derkits.at>             *
 * Copyright (c) 2010 - 2011 Christian Wagner <christian.wagner86@gmx.at>   *
 * Copyright (c) 2010 - 2011 Felix Winter <ixos01@gmail.com>                *
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

#include <QCoreApplication>
#include <QtGui>
#include <QEventLoop>

#include <PodcastList.h>
#include <EpisodeList.h>
#include <EpisodeActionList.h>
#include <EpisodeAction.h>
#include <TagList.h>
#include <ApiRequest.h>
#include <Settings.h>
#include <DeviceUpdates.h>
#include <QDateTime>
#include <DeviceList.h>
#include <Device.h>
#include <DeviceSyncResult.h>

#include <QList>
#include <QString>

using namespace mygpo;

void printTitle(const QString& title) {
    QString fillLine(80, QLatin1Char('#'));

    qDebug() << fillLine;
    qDebug() << title;
    qDebug() << fillLine;
}

void printPodcast(const Podcast* podcast) {
    qDebug() << "title:\t" << podcast->title();
    qDebug() << "url:\t" << podcast->url();
    qDebug() << "description:\t" << podcast->description();
    qDebug() << "subscribers:\t" << podcast->subscribers();
    qDebug() << "subscribers last week:\t" << podcast->subscribersLastWeek();
    qDebug() << "";
}

void printPodcastList(const PodcastListPtr podcastList) {
    QList<PodcastPtr> list;
    QList<PodcastPtr>::const_iterator iterator;

    list = podcastList->list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
        printPodcast(iterator->data());
    }
    qDebug() << "";
}

void printEpisode(const EpisodePtr episode) {
    qDebug() << "title:\t" << episode->title();
    qDebug() << "url:\t" << episode->url();
    qDebug() << "status:\t" << episode->status();
    qDebug() << "released:\t" << episode->released().toString();
    qDebug() << "";
}


void printEpisodeList(const EpisodeListPtr episodeList) {
    QList<EpisodePtr> list;
    QList<EpisodePtr>::const_iterator iterator;

    list = episodeList->list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
        qDebug() << "title:\t" << iterator->data()->title();
        qDebug() << "url:\t" << iterator->data()->url();
        qDebug() << "status:\t" << iterator->data()->status();
        qDebug() << "released:\t" << iterator->data()->released().toString();
        qDebug() << "";
    }
    qDebug() << "";
}


void printTagList(const TagListPtr tagList) {
    QList<TagPtr> list;
    QList<TagPtr>::const_iterator iterator;

    list = tagList->list();
    for (iterator = list.constBegin(); iterator != list.constEnd(); ++iterator) {
        qDebug() << iterator->data()->tag();
    }
    qDebug() << "";
}

void printAddRemoveResult(const AddRemoveResultPtr addRemoveResult) {
    qDebug() << "timestamp:\t" << addRemoveResult->timestamp();

    QList< QPair<QUrl, QUrl> > pairlist = addRemoveResult->updateUrlsList();

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
    QCoreApplication app(argc, argv);
    QNetworkAccessManager* nam = new QNetworkAccessManager(qApp);
    ApiRequest req("ase23", "csf-sepm", nam);
    QEventLoop loop;
    
    QNetworkReply* reply;
    
    DeviceSyncResultPtr syncPtr = req.deviceSynchronizationStatus( "ase23" );
    
    loop.connect(syncPtr.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(syncPtr.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();
    
    qDebug() << "synced: ";
    QVariant synced = syncPtr->synchronized();
    foreach (QVariant list, synced.toList() ) {
        qDebug() << "syncgroup: " << list.toList();
    }
    qDebug() << "non-synced: " << syncPtr->notSynchronized();
    
    qDebug() << "synced (parsed):";
    QList<QStringList> parsed = syncPtr->synchronizedList();
    foreach (QStringList innerList, parsed) {
        qDebug() << "syncgroup (parsed): " << innerList;
    }
    qDebug() << "parsed: " << parsed;
    
    qDebug() << "non-synced (parsed): " << syncPtr->notSynchronizedList();

    reply = req.toplistXml(23);
    
    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();
    
    qDebug() << reply->readAll();
    
    reply = req.searchXml("linux");
    
    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();
    
    qDebug() << reply->readAll();
    //
    // QNetworkReply* toplistOpml(uint count);
    //
    reply = req.toplistOpml(1);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast toplists (OPML) [toplistOpml(1)]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    reply = req.downloadSubscriptionsTxt( "ase23", "dev0" );
    
    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast subscriptions (Txt) [subscriptionsTxt(\"ase23\",\"dev0\"]"));
    qDebug() << reply->readAll();
    qDebug() << "";
    
    reply = req.downloadSubscriptionsOpml( "ase23", "dev0" );
    
    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast subscriptions (OPML) [subscriptionsOpml(\"ase23\",\"dev0\"]"));
    qDebug() << reply->readAll();
    qDebug() << "";
    //
    // QNetworkReply* searchOpml(const QString& query);
    //
    reply = req.searchOpml(QLatin1String("linux outlaws"));

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Searching for podcasts (OPML) [searchOpml(\"linux outlaws\")]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // QNetworkReply* suggestionsOpml(uint count);
    //
    reply = req.suggestionsOpml(2);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast suggestions (OPML) [suggestionsOpml(2)]"));
    qDebug() << reply->readAll();
    qDebug() << "";

	//
    // QNetworkReply* toplistO(uint count);
    //
    reply = req.toplistTxt(10);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast toplists (TXT) [toplistOpml(10)]"));
    qDebug() << reply->readAll();
	qDebug() << "";


    //
    // QNetworkReply* suggestionsOpml(uint count);
    //

    reply = req.searchTxt(QLatin1String("coverville"));

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Searching for podcasts (TXT) [searchTxt(\"coverville\")]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // QNetworkReply* suggestionsTxt(uint count);
    //
    reply = req.suggestionsTxt(4);

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast suggestions (TXT) [suggestionsTxt(4)]"));
    qDebug() << reply->readAll();
    qDebug() << "";

    //
    // PodcastListPtr toplist(uint count);
    //
    PodcastListPtr topList(req.toplist(1));

    loop.connect(topList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(topList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast toplists [toplist(1)]"));
    printPodcastList(topList);

    reply = req.downloadSubscriptionsJson( "ase23", "dev0" );

    loop.connect(reply, SIGNAL(finished()), SLOT(quit()));
    loop.connect(reply, SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading subscriptions (JSON) [subscriptionsJson(\"ase23\",\"dev0\")]"));
    qDebug() << reply->readAll();
    qDebug();
    //
    // PodcastListPtr search(const QString& query);
    //
    PodcastListPtr searchList(req.search(QLatin1String("linux outlaws")));

    loop.connect(searchList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(searchList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Searching for podcasts [search(\"linux outlaws\")]"));
    printPodcastList(searchList);

    //
    // PodcastListPtr suggestions(uint count);
    //
    PodcastListPtr suggestionsList(req.suggestions(2));

    loop.connect(suggestionsList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(suggestionsList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Downloading podcast suggestions [suggestions(2)]"));
    printPodcastList(suggestionsList);

    //
    // PodcastListPtr podcastsOfTag(uint count, const QString& tag);
    //
    PodcastListPtr podcastsOfTagList(req.podcastsOfTag(1,QLatin1String("linux")));

    loop.connect(podcastsOfTagList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(podcastsOfTagList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Podcasts of a Tag [podcastsOfTag(1,\"linux\")]"));
    printPodcastList(podcastsOfTagList);

    //
    // PodcastPtr podcastData (const QUrl& podcasturl);
    //
    PodcastPtr podcast(req.podcastData(QUrl(QLatin1String("http://surl.dk/7k5"))));

    loop.connect(podcast.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(podcast.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Podcast Data [podcastData(\"http://surl.dk/7k5\")]"));
    printPodcast(podcast.data());

    //
    // EpisodePtr episodeData(const QUrl& podcasturl, const QUrl& episodeurl);
    //
    EpisodePtr episode(req.episodeData(QUrl(QLatin1String("http://surl.dk/7k5")), QUrl(QLatin1String("http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3"))));

    loop.connect(episode.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(episode.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Episode Data [episodeData(\"http://surl.dk/7k5\",\"http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3\")]"));
    printEpisode(episode);

    //
    // EpisodeListPtr favoriteEpisodes(const QString& username);
    //
    EpisodeListPtr episodeList(req.favoriteEpisodes(QLatin1String("ase23")));

    loop.connect(episodeList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(episodeList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Listing Favorite Episodes [favoriteEpisodes(\"ase23\")]"));
    printEpisodeList(episodeList);

    //
    // TagListPtr topTags(uint count);
    //
    TagListPtr tagList(req.topTags(3));

    loop.connect(tagList.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(tagList.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Retrieving Top Tags [topTags(3)]"));
    printTagList(tagList);

    //
    // AddRemoveResultPtr addRemoveSubscriptions(const QString& username, const QString& device, const QList<QUrl>& add, const QList<QUrl>& remove);
    //
    QList<QUrl> add;
    QList<QUrl> remove;
    add << QUrl(QLatin1String("http://feeds.rucast.net/radio-t"));
    remove << QUrl(QLatin1String("http://hackermedley.org/feed/podcast/"));

    AddRemoveResultPtr addRemoveResult(req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), add, remove));

    loop.connect(addRemoveResult.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(addRemoveResult.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Add/remove subscriptions [addRemoveSubscriptions(\"ase23\", \"dev0\", {\"http://feeds.rucast.net/radio-t\"}, {http://hackermedley.org/feed/podcast/}]"));
    printAddRemoveResult(addRemoveResult);

    AddRemoveResultPtr addRemoveResult2(req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), remove, add));

    loop.connect(addRemoveResult2.data(), SIGNAL(finished()), SLOT(quit()));
    loop.connect(addRemoveResult2.data(), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    printTitle(QLatin1String("Add/remove subscriptions2 [addRemoveSubscriptions(\"ase23\", \"dev0\", {http://hackermedley.org/feed/podcast/}, {\"http://feeds.rucast.net/radio-t\"}]"));
    printAddRemoveResult(addRemoveResult2);


    //
    // Copy objects and reicieve signals
    //
    printTitle(QLatin1String("Copy objects, and receive signals:"));

    qDebug() << "EpisodeList";
    EpisodeListPtr ret1 = req.favoriteEpisodes(QLatin1String("ase23"));
    EpisodeListPtr ret = ret1;
    loop.connect(ret.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ret.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "List1 size: " << ret->list().size();
    qDebug() << "List2 size: " << ret1->list().size();
    qDebug() << "";

    qDebug() << "Episode";
    EpisodePtr episode1 = req.episodeData(QUrl(QLatin1String("http://surl.dk/7k5")), QUrl(QLatin1String("http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws165.mp3")));
    EpisodePtr episode2 = episode1;
    loop.connect(episode2.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(episode2.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(episode2.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "Episode1: " << episode1->title();
    qDebug() << "Episode2: " << episode2->title();
    qDebug() << "";

    qDebug() << "PodcastList";
    PodcastListPtr podcastList1 = req.toplist(1);
    PodcastListPtr podcastList2 = podcastList1;
    loop.connect(podcastList1.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(podcastList1.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(podcastList1.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "PodcastList1 size: " << podcastList1->list().size();
    qDebug() << "PodcastList2 size: " << podcastList1->list().size();
    qDebug() << "";

    qDebug() << "Podcast";
    PodcastPtr podcast1 = req.podcastData(QUrl(QLatin1String("http://surl.dk/7k5")));
    PodcastPtr podcast2 = podcast1;
    loop.connect(podcast2.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(podcast2.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(podcast2.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "Podcast1: " << podcast1->title();
    qDebug() << "Podcast2: " << podcast2->title();
    qDebug() << "";

    qDebug() << "TagList";
    TagListPtr tagList1 = req.topTags(3);
    TagListPtr tagList2 = tagList1;
    loop.connect(tagList2.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(tagList2.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(tagList2.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "TagList1 size: " << tagList1->list().size();
    qDebug() << "TagList2 size: " << tagList2->list().size();
    qDebug() << "";

    qDebug() << "AddRemoveResult";

    /*QList<QUrl> add2;
    QList<QUrl> remove2;
    ad << QUrl(QLatin1String(""));
    rem << QUrl(QLatin1String(""));*/
    /*
    AddRemoveResultPtr addRemove1 = req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"), remove, add);
    AddRemoveResultPtr addRemove2 = addRemove1;
    loop.connect(addRemove2.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(addRemove2.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(addRemove2.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "AddRemoveResult1: " << addRemove1->timestamp();
    qDebug() << "AddRemoveResult2: " << addRemove2->timestamp();
    qDebug() << "";
    */



    /*QList<QUrl> add;
    QList<QUrl> remove;
    add << QUrl(QLatin1String("http://feeds.rucast.net/radio-t"));
    remove << QUrl(QLatin1String("http://hackermedley.org/feed/podcast/"));*/
    /*
    AddRemoveResultPtr result = req.addRemoveSubscriptions(QLatin1String("ase23"), QLatin1String("dev0"),add,remove);

    loop.connect(result.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(result.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(result.data(),SIGNAL(parseError()),SLOT(quit()));

    loop.exec();

    qDebug() << result->timestamp();
    */

    //
    // Test QSharedPointers
    //
    /*printTitle("Test QSharedPointers");
    qDebug() << "EpisodePtr";
    EpisodePtr episodePtr = req.episodeData(QUrl(QLatin1String("http://leo.am/podcasts/twit")),QUrl(QLatin1String("http://www.podtrac.com/pts/redirect.mp3/aolradio.podcast.aol.com/twit/twit0245.mp3")));
    loop.connect( &(*episodePtr), SIGNAL(finished()), SLOT(quit()));
    loop.connect( &(*episodePtr), SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect( &(*episodePtr), SIGNAL(parseError()), SLOT(quit()));
    loop.exec();
    qDebug() << episodePtr->title();

    qDebug() << "TagListPtr";
    TagListPtr tagListPtr =  req.topTags(10);
    loop.connect(tagListPtr.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(tagListPtr.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(tagListPtr.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();

    qDebug() << tagListPtr->list().size();
    foreach (TagPtr tag, tagListPtr->list()) {
        qDebug() << tag->tag();
    }

    //
    // Test new requests
    //
    printTitle("Test new requests");
    qDebug() << "Settings";
    SettingsPtr settingsPtr = req.accountSettings( "ase23" );

    loop.connect(settingsPtr.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(settingsPtr.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    qDebug() << settingsPtr->settings().toMap();

    qDebug() << "Set Public Profile false & some other Account Settings";

    QVariantMap set;
    QStringList remSettings;

    set.insert("public_profile",QVariant(false));
    set.insert("leet",QVariant(1337));
    set.insert("1337",QVariant("leet"));

    SettingsPtr settingsPtr2 = req.setAccountSettings( "ase23", set, remSettings);

    loop.connect(settingsPtr2.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(settingsPtr2.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    qDebug() << settingsPtr2->settings().toMap();

    qDebug() << "Remove Setting leet";

    QVariantMap set2;
    remSettings.append("leet");

    SettingsPtr settingsPtr3 = req.setAccountSettings( "ase23", set, remSettings);

    loop.connect(settingsPtr3.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(settingsPtr3.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    qDebug() << settingsPtr3->settings().toMap();

    qDebug() << "Test Device Settings";

    SettingsPtr settingsPtr4 = req.deviceSettings("ase23","dev0");

    loop.connect(settingsPtr4.data(),SIGNAL(finished()),SLOT(quit()));
    //loop.connect(settingsPtr4.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.exec();

    qDebug() << settingsPtr4->settings().toMap();

    qDebug();
    qDebug() << "EpisodeActions";
    QList<EpisodeActionPtr> episodeActions1, episodeActions2;
    EpisodeActionPtr episodeAction1 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am/podcasts/twit")), QUrl(QLatin1String("http://www.podtrac.com/pts/redirect.mp3/aolradio.podcast.aol.com/twit/twit0245.mp3")), QLatin1String(""), EpisodeAction::New, 0, 0, 0, 0));
    EpisodeActionPtr episodeAction2 = QSharedPointer<EpisodeAction>(new EpisodeAction(QUrl(QLatin1String("http://leo.am/podcasts/twit")), QUrl(QLatin1String("http://www.podtrac.com/pts/redirect.mp3/aolradio.podcast.aol.com/twit/twit0245.mp3")), QLatin1String(""), EpisodeAction::Delete, 0, 0, 0, 0));
    episodeActions1.append(episodeAction1);
    episodeActions2.append(episodeAction2);

    qDebug() << "UploadEpisodeActions";
    AddRemoveResultPtr addRemoveResult1 = req.uploadEpisodeActions("ase23", episodeActions1);
    loop.connect(addRemoveResult1.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(addRemoveResult1.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(addRemoveResult1.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();

    qDebug() << "timestamp: " << addRemoveResult1->timestamp();
    qDebug() << "";

    AddRemoveResultPtr addRemoveResult3 = req.uploadEpisodeActions("ase23", episodeActions2);
    loop.connect(addRemoveResult3.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(addRemoveResult3.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(addRemoveResult3.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();

    EpisodeActionListPtr episodeActions3 = req.episodeActions("ase23");
    loop.connect(episodeActions3.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(episodeActions3.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(episodeActions3.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "EpisodeActions";
    qDebug() << "timestamp: " << episodeActions3->timestamp();
    foreach(const EpisodeActionPtr& episodeAction, episodeActions3->list()) {
        qDebug() << episodeAction->podcastUrl() << episodeAction->action();
    }

    qDebug() << "Devices";
    DeviceUpdatesPtr ptr = req.deviceUpdates("ase23","dev0",QDateTime::fromString(QLatin1String("7.12.2010"), QLatin1String("dd.MM.yyyy")).toMSecsSinceEpoch()/1000);
    loop.connect(ptr.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(ptr.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(ptr.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    qDebug() << "AddList:";
    foreach(const PodcastPtr& p, ptr->addList()) {
        qDebug() << p->url();
    }
    qDebug() << "RemoveList:";
    foreach(const QUrl& url, ptr->removeList()) {
        qDebug() << url;
    }
    qDebug() << "UpdateList:";
    foreach(const EpisodePtr& e, ptr->updateList()) {
        printEpisode(e);
    }

    qDebug() << "Timestamp:";
    qDebug() << ptr->timestamp();
    qDebug() << QDateTime::fromTime_t(ptr->timestamp()).toString();

    qDebug() << "Rename Device:";
    QNetworkReply* r = req.renameDevice("ase23","dev0","dev0Device",Device::OTHER);
    loop.connect(r, SIGNAL(finished()), SLOT(quit()));
    loop.exec();
    qDebug() << r->readAll();

    DeviceListPtr deviceListPtr = req.listDevices("ase23");
    loop.connect(deviceListPtr.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(deviceListPtr.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(deviceListPtr.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();

    qDebug() << "Device list:";
    foreach(const DevicePtr& dev, deviceListPtr->devicesList()) {
        qDebug() << dev->id();
        qDebug() << dev->type();
        qDebug() << dev->caption();
        qDebug() << dev->subscriptions();
    }

    qDebug() << "Test Anonymous Requests";

    mygpo::ApiRequest anonym(nam);
    PodcastListPtr top = anonym.toplist(10);
    loop.connect(top.data(),SIGNAL(finished()),SLOT(quit()));
    loop.connect(top.data(),SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(top.data(),SIGNAL(parseError()),SLOT(quit()));
    loop.exec();

    printPodcastList(top);*/

    //reply->deleteLater();
    nam->deleteLater();

    return 0;
}

