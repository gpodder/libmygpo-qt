#include "DeviceList.h"
#include <parser.h>

namespace mygpo
{
    
class DeviceListPrivate : public QObject
{
    Q_OBJECT
public:
    DeviceListPrivate(DeviceList* qq, QNetworkReply* reply);
    ~DeviceListPrivate();
    QVariant devices() const;
    QList< QMap<QString,QString> > devicesList() const;
    
private:
    DeviceList* q;
    QNetworkReply* m_reply;
    QVariant m_devices;
    QNetworkReply::NetworkError m_error;
    
    bool parse ( const QVariant& data );
    bool parse ( const QByteArray& data );
    
private slots:
    void parseData();
    void error ( QNetworkReply::NetworkError error );
};

}


using namespace mygpo;

DeviceListPrivate::DeviceListPrivate(DeviceList* qq, QNetworkReply* reply) : q(qq), m_reply(reply)
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

DeviceListPrivate::~DeviceListPrivate()
{
    delete m_reply;
}

QVariant DeviceListPrivate::devices() const
{
    return m_devices;
}

QList< QMap< QString, QString > > DeviceListPrivate::devicesList() const
{
    QVariantList varList = m_devices.toList();
    QList< QMap< QString, QString > > ret;
    foreach( const QVariant& var, varList)
    {
        if(var.canConvert(QVariant::Map)) 
        {
            QMap<QString,QVariant> varMap;
            QMap<QString,QString> tmp;
            
            varMap = var.toMap();
            if(varMap.value(QLatin1String("id")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("id"),varMap.value(QLatin1String("id")).toString());
            if(varMap.value(QLatin1String("caption")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("caption"),varMap.value(QLatin1String("caption")).toString());
            if(varMap.value(QLatin1String("type")).canConvert(QVariant::String))
                tmp.insert(QLatin1String("type"),varMap.value(QLatin1String("type")).toString());
            if(varMap.value(QLatin1String("subscription")).canConvert(QVariant::Int))
                tmp.insert(QLatin1String("subscription"),QString::number(varMap.value(QLatin1String("subscription")).toInt()));
            ret.append(tmp);
        }
    }
    return ret;
}

void DeviceListPrivate::error(QNetworkReply::NetworkError error)
{
    m_error = error;
    emit q->requestError(error);
}

bool DeviceListPrivate::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::List))
        return false;
    m_devices = data.toList();
    return true;
}

bool DeviceListPrivate::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      ok = (parse( variant ));
    }
    return ok;
}


void DeviceListPrivate::parseData()
{
    if ( parse( m_reply->readAll() ) ) {
      emit q->finished();
    } else {
      emit q->parseError();
    }
}

DeviceList::DeviceList(QNetworkReply* reply, QObject* parent) : QObject(parent), d(new DeviceListPrivate(this, reply))
{

}

DeviceList::~DeviceList()
{
    delete d;
}

QVariant mygpo::DeviceList::devices() const
{
    return d->devices();
}

QList< QMap< QString, QString > > mygpo::DeviceList::devicesList() const
{
    return d->devicesList();
}


#include "DeviceList.moc"