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
#include <PodcastList.h>

using namespace mygpo;
//#include "Example.h"

int main ( int argc, char **argv )
{

    QApplication app ( argc,argv,true );
    //QList<Podcast> list;

    ApiRequest req ( "ase23","csf-sepm" );
    
    
    QEventLoop loop;
    PodcastList ret1 = req.toplist(10);
    PodcastList ret = ret1;
    loop.connect(&ret,SIGNAL(finished()),SLOT(quit()));
    loop.connect(&ret,SIGNAL(requestError(QNetworkReply::NetworkError)), SLOT(quit()));
    loop.connect(&ret,SIGNAL(parseError()),SLOT(quit()));
    loop.exec();
    
    qDebug() << "example: "<< ret.list().size();
    
    
    
//  QByteArray result;
    //result = req.toplistOpml(10);
    //std::cout << result.data() << std::endl;
//
//  list = req.toplist(10);
//  std::cout << list.size() << std::endl;
//  foreach (const Podcast& podcast,list) {
//  qDebug() << podcast.title();
//  qDebug() << podcast.subscribers();
//  }

/*    QList<QUrl> add;
    QList<QUrl> remove;

    add.append ( QUrl ( QLatin1String ( "http://feeds.feedburner.com/coverville" ) ) );
    remove.append( QUrl ( QLatin1String( "http://feeds.feedburner.com/Bsdtalk" ) ) );
    
    AddRemoveResult result = req.addRemoveSubscriptions ( QLatin1String ( "ase23" ),QLatin1String ( "dev0" ),add,remove );

    QEventLoop loop;
    loop.connect ( &result,SIGNAL ( finished() ),SLOT ( quit() ) );
    loop.exec();

    qDebug() << result.timestamp();

    QList< QPair< QUrl, QUrl > > pairlist = result.updateUrlsList();

    for ( int i=0;i<pairlist.size();i++ )
    {
        QPair< QUrl, QUrl > pair = pairlist.at ( i );
        qDebug() << pair.first;
        qDebug() << pair.second;
    }
    */
    /*
    TagList taglist = req.topTags(15);

    QEventLoop loop;
    loop.connect(&taglist,SIGNAL(finished()),SLOT(quit()));
    loop.exec();

    QList<mygpo::Tag> tags = taglist.list();

    foreach(mygpo::Tag tag, tags)
    {
        qDebug() << tag.usage();
        qDebug() << tag.tag();
    }

    QVariantList variantlist = taglist.tags().toList();

    foreach(QVariant variant, variantlist)
    {
        qDebug() << variant.value<mygpo::Tag>().usage();
        qDebug() << variant.value<mygpo::Tag>().tag();
    }
    */

    /*
    EpisodeList eplist = req.favoriteEpisode(QString(QLatin1String("ase23")));

    QEventLoop loop;
    loop.connect(&eplist,SIGNAL(finished()),SLOT(quit()));
    loop.connect(&eplist,SIGNAL(parseError()),SLOT(quit()));
    loop.connect(&eplist,SIGNAL(requestError(QNetworkReply::NetworkError)),SLOT(quit()));
    qDebug() << QLatin1String("signals connected");
    loop.exec();

    qDebug() << QLatin1String("Loop finished");
    QList<mygpo::Episode> episodes = eplist.list();

    foreach (Episode episode, episodes)
    {
        qDebug() << QLatin1String("Iteration over Episodes");
        qDebug() << episode.title();
        qDebug() << episode.url();
        qDebug() << episode.podcastTitle();
        qDebug() << episode.podcastUrl();

    }
    QVariantList varlist = eplist.episodes().toList();

    foreach (QVariant variant, varlist)
    {
        qDebug() << QLatin1String("Iteration over Variants");
        qDebug() << variant.type();
        qDebug() << variant.value<mygpo::Episode>().title();
    }*/

    /*
    Episode ep = req.episodeData(QUrl(QLatin1String("http://feeds.feedburner.com/linuxoutlaws")),QUrl(QLatin1String("http://traffic.libsyn.com/linuxoutlaws/linuxoutlaws177.mp3")));

    QEventLoop loop;
    loop.connect(&ep,SIGNAL(finished()),SLOT(quit()));
    loop.exec();
    qDebug() << ep.description();
    qDebug() << ep.title();
    qDebug() << ep.mygpoUrl();
    */
    /*
    PodcastList plist = req.toplist(10);
    QEventLoop loop;
    loop.connect(&plist,SIGNAL(finished()),SLOT(quit()));
    loop.exec();
    QList<Podcast> liste = plist.list();
    qDebug() << liste.size();
    foreach(Podcast pcast,liste)
    {
        qDebug() << pcast.title();
        qDebug() << pcast.description();
        qDebug() << pcast.url();
    }

    QVariant variant = plist.podcasts();
    qDebug() << variant.type();
    QVariantList list = variant.toList();
    qDebug() << list.at(0).type();
    Podcast pc = list.at(0).value<mygpo::Podcast>();
    qDebug() << pc.url();
    //put a Podcast Object into a QVariant
    QVariant varPodcast;
    varPodcast.setValue<mygpo::Podcast>(pc);
    qDebug() << varPodcast.type();
    //get the Podcast from the QVariant
    Podcast pcFromVariant = varPodcast.value<mygpo::Podcast>();
    qDebug() << pcFromVariant.title();
    */


    return 0;
}


