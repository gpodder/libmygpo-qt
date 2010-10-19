#include <QApplication>
#include <iostream>
#include <QTimer>
#include "Example.h"

int main(int argc, char **argv) {
  QApplication app(argc,argv,false);
  Example ex;
  
  std::cout << "Downloading podcast toplists as text and json:" << std::endl;
  ex.startDownload(QUrl("http://gpodder.net/toplist/10.txt"));
  
  ex.startDownload(QUrl("http://gpodder.net/toplist/10.json"));
  
  QTimer::singleShot(5000, &app, SLOT(quit()));

  return app.exec();
}


