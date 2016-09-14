#pragma once

#include <QObject>
#include <QtNetwork/QNetworkReply>


// Forward declarations
class QFile;
class QNetworkAccessManager;


class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = 0);

    Q_PROPERTY(int value READ getValue NOTIFY valueChanged)
    Q_PROPERTY(int maximumValue READ getMaximumValue NOTIFY maximumValueChanged)

    Q_INVOKABLE void download(QString url);
    Q_INVOKABLE bool getDownloadStatus() const { return startDownload; }


public:  // Properties support
    int getValue() const { return m_value; }
    int getMaximumValue() const { return m_maximumValue; }


signals:
    void valueChanged();
    void maximumValueChanged();

private slots:
    void onReplyFinished();
    void onDownloadProgress(qint64, qint64);
    void onReadyRead();
    void onError(QNetworkReply::NetworkError code);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    qint64 m_value;
    qint64 m_maximumValue;
    bool startDownload = false;
    QFile *file;
};

