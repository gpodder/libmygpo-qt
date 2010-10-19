#include "Example.h"
#include <iostream>

Example::Example() {
  connect(&man, SIGNAL(finished(QNetworkReply*)),this, SLOT(result(QNetworkReply*)));
}


void Example::startDownload(const QUrl& url) {
  man.get(QNetworkRequest(url));
}

void Example::result(QNetworkReply* reply) {
    std::cout << reply->readAll().data() << std::endl;
    reply->deleteLater();	
}