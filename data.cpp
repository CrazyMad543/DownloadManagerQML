#include "data.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QFileInfo>
#include <QByteArray>


Data::Data(QObject *parent)
    : QObject(parent)
{
    m_value = 0;
    m_maximumValue = 0;
}

void Data::onReplyFinished() {
    startDownload = false;
    file->close();
    reply->deleteLater();
}

void Data::onReadyRead() {
    QByteArray content = reply->read(reply->bytesAvailable());
    file->write(content);
}

void Data::onError(QNetworkReply::NetworkError code) {
    qWarning() << "Error:" << code;
    startDownload = false;
    file->close();
    reply->deleteLater();
}

void Data::download(QString url) {
    startDownload = true;

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    file = new QFile( QFileInfo(url).fileName() );
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);

    manager = new QNetworkAccessManager(this);
    reply = manager->get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &Data::onDownloadProgress);
    connect(reply, &QNetworkReply::finished, this, &Data::onReplyFinished);
    connect(reply, &QNetworkReply::readyRead, this, &Data::onReadyRead);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &Data::onError);
}

void Data::onDownloadProgress(qint64 readBytes, qint64 totalBytes) {
    if (m_maximumValue != totalBytes) {
        m_maximumValue = totalBytes;
        emit maximumValueChanged();
    }

    if (m_value != readBytes) {
        m_value = readBytes;
        emit valueChanged();
    }
}
