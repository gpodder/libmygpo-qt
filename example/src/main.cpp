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

#include "ApiRequest.h"

//#include "Example.h"

int main(int argc, char **argv) {
  
  QApplication app(argc,argv,true);
  
  mygpo::ApiRequest req;
  QByteArray result;
  result = req.toplistOpml(10);
  std::cout << result.data() << std::endl;
  
  
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


