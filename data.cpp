#include "data.h"

Data::Data(QObject *parent) : QObject(parent) {
    m_value = 0;
    m_maximumValue = 0;
}

void Data::replyFinished() {
    startDownload = false;
    file->close();
    delete reply;
}

void Data::onReadyRead() {
    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << reply->errorString();
    }
    else {
        QByteArray content = reply->read(reply->bytesAvailable());
        file->write(content);
        file->flush();
    }
}

void Data::download(QString url) {
    startDownload = true;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QFileInfo fileInfo(url);
    fileName = fileInfo.fileName();
    file = new QFile(fileName);
    file->open(QIODevice::WriteOnly | QIODevice::Append);

    manager = new QNetworkAccessManager(this);
    reply = manager->get(request);
    connect(reply, &QNetworkReply::downloadProgress,
                           this, &Data::onDownloadProgress);
    connect(reply, &QNetworkReply::finished,
                           this, &Data::replyFinished);
    connect(reply, &QNetworkReply::readyRead,
                           this, &Data::onReadyRead);
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


