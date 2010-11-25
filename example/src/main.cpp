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

#include <Podcast.h>
#include <ApiRequest.h>

using namespace mygpo;
//#include "Example.h"

int main(int argc, char **argv) {
  
  QApplication app(argc,argv,true);
  QList<Podcast> list;
  
  ApiRequest req("ase23","csf-sepm");
//  QByteArray result;
  //result = req.toplistOpml(10);
  //std::cout << result.data() << std::endl;
//
//  list = req.toplist(10);
//  std::cout << list.size() << std::endl;
//  foreach (const Podcast& podcast,list) {
//	qDebug() << podcast.title();
//	qDebug() << podcast.subscribers();
//  }
  QEventLoop loop;
  
  Podcast podcast = req.podcastData(QUrl(QLatin1String("http://feeds.feedburner.com/linuxoutlaws")));
  loop.connect(&podcast, SIGNAL(finished()), SLOT(quit()));
  loop.exec();

  qDebug() << podcast.title();
  qDebug() << podcast.description();
  qDebug() << podcast.url();


  /*Example ex;


  std::cout << "Downloading podcast toplists as text and json:" << std::endl;
  ex.startDownload(QUrl("http://gpodder.net/toplist/10.txt"));
  
  ex.startDownload(QUrl("http://gpodder.net/toplist/10.json"));
  
  std::cout << "Downloading subscription lists for user ase23:" << std::endl;

  ex.startDownload(QUrl("http://gpodder.net/subscriptions/ase23/dev0.txt"));

  ex.startDownload(QUrl("http://gpodder.net/subscriptions/ase23/dev0.json"));
  */

  /* These two lines are no longer needed, RequestHandler waits itself
   * for messages
  QTimer::singleShot(5000, &app, SLOT(quit()));
  return app.exec();
  */

  return 0;
}


