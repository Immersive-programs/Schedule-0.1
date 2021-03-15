#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::DowloadData(QString url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager->get(request);
}

QByteArray Downloader::getData()
{
    return _Bytes;
}

QString Downloader::getError()
{
    return _Error;
}

void Downloader::onResult(QNetworkReply *reply)
{
    if(reply->error()){
        _Error = reply->errorString();
        emit onError();
    }
    else
    {
        _Bytes = reply->readAll();
        emit onReady();
    }
}
