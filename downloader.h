#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);

signals:
    void onReady();
    void onError();

public slots:
    QByteArray getData();
    QString getError();
    void DowloadData(QString url);
    void onResult(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QByteArray _Bytes;
    QString _Error;
};

#endif // DOWNLOADER_H
