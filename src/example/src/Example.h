#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Example : public QObject {
  Q_OBJECT;
  
  public:
    Example();
    void startDownload(const QUrl& url);
    
  private:
    QNetworkAccessManager man;
    
    
  public slots:
    void result(QNetworkReply* reply);
  
};


#endif